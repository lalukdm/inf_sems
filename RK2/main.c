#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libxml2\include\libxml\parser.h>

#include <libxml\tree.h>
#include "cJSON.h"

#define MAX_DATA_SIZE 1024
#define MAX_LINES_DB 1024

char* read_string(FILE *file) {
    char* str = NULL;
    
    int size = 0;
    int c;

    while ((c = fgetc(file)) != '\n') {
        if (c == EOF) return NULL;
        str = realloc(str, ++size * sizeof(char));

        if (str == NULL) 
            return str;

        str[size-1] = c;
    }

    str = realloc(str, ++size * sizeof(char));
    str[size-1] = '\n';

    str = realloc(str, ++size * sizeof(char));
    str[size-1] = '\0';

    return str;
}

void delete_double_str(char* filename) {
    FILE* file = fopen(filename, "r");
    char *lines[MAX_LINES_DB];
    char buffer[256];
    int num_lines = 0;
    int i, j;

    while (fgets(buffer, sizeof(buffer), file) != NULL && num_lines < MAX_LINES_DB) {
        lines[num_lines] = strdup(buffer); 
        num_lines++;
    }
    fclose(file);

    for (i = 0; i < num_lines; i++) {
        for (j = i + 1; j < num_lines;) {
            if (strcmp(lines[i], lines[j]) == 0) {
                free(lines[j]); 
                num_lines--;
                lines[j] = lines[num_lines]; 
            } else j++;
        }
    }
    
    FILE* fp = fopen(filename, "w");
    for (i = 0; i < num_lines; i++) {
        fputs(lines[i], fp);
        free(lines[i]);
    }
    fclose(fp);
}

void json_to_csv(const char* json_file, const char* csv_file) {
 FILE* input_file = fopen(json_file, "r");
    if (input_file == NULL) {
        printf("Error: could not open input file: %s\n", json_file);
        return;
    }
    
    // Create output file
    FILE* output_file = fopen(csv_file, "a");
    if (output_file == NULL) {
        printf("Error: could not create output file: %s\n", csv_file);
        fclose(input_file);
        return;
    }
    
    // Parse JSON data
    cJSON* json_data = cJSON_CreateArray();
    char buffer[2048];
    while (fgets(buffer, sizeof(buffer), input_file)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        cJSON* item = cJSON_Parse(buffer);
        if (item == NULL) {
            printf("Error: could not parse JSON data\n");
            cJSON_Delete(json_data);
            fclose(input_file);
            fclose(output_file);
            return;
        }
        cJSON_AddItemToArray(json_data, item);
    }
    
    // Write CSV data
    cJSON* first_item = cJSON_GetArrayItem(json_data, 0);
    cJSON* current_item;
    cJSON_ArrayForEach(current_item, first_item) {
        fprintf(output_file, "%s;", current_item->string);
    }
    fprintf(output_file, "\n");
    cJSON_ArrayForEach(current_item, json_data) {
        cJSON* value;
        cJSON_ArrayForEach(value, current_item) {
            fprintf(output_file, "%s;", cJSON_GetStringValue(value));
        }
        fprintf(output_file, "\n");
    }
    
    // Clean up
    cJSON_Delete(json_data);
    fclose(input_file);
    fclose(output_file);
    delete_double_str(csv_file);
}

void csv_to_json(const char* csv_file, const char* json_file) {

    FILE *inputFile = fopen(csv_file, "r");
    if (inputFile == NULL) {
        printf("Error: Unable to open input file \"%s\"\n", csv_file);
        return;
    }

    FILE *outputFile = fopen(json_file, "a");
    if (outputFile == NULL) {
        printf("Error: Unable to open output file \"%s\"\n", json_file);
        fclose(inputFile);
        return;
    }

    // Get keys
    char keys_line[MAX_DATA_SIZE];
    if (fgets(keys_line, MAX_DATA_SIZE, inputFile) == NULL) {
        printf("Error: Unable to read keys from input file \"%s\"\n", csv_file);
        fclose(inputFile);
        fclose(outputFile);
        return;
    }
    
    

    // parse CSV data
    int lineCount = 0;
    char line[MAX_DATA_SIZE];
    char *token; 
    const char *delimiter = ";";
    char *keys[100];
    int keyCount = 0;
    
    // separate to keys list
    token = strtok(keys_line, delimiter);
    while (token != NULL) {
        keys[keyCount] = strdup(token);
        keyCount++;
        token = strtok(NULL, delimiter);
    }
    

    // fprintf(outputFile, "[");

    while (fgets(line, MAX_DATA_SIZE, inputFile) != NULL) {
        if (lineCount > 0 ) {
            fprintf(outputFile, ",\n");
        }
        
        fprintf(outputFile, "{");

        token = strtok(line, delimiter);
        for (int i = 0; token != NULL && i < (keyCount -1); i++) {
            fprintf(outputFile, "\"%s\":\"%s\"", keys[i], token);
            token = strtok(NULL, delimiter);
            
            if (i < (keyCount - 2)) {
                fprintf(outputFile, ",");
            }
        }

        fprintf(outputFile, "}");
        lineCount++;
    }

    // fprintf(outputFile, "]");
    fprintf(outputFile, ",\n");

    for (int i = 0; i < keyCount; i++) {
        free(keys[i]);
    }

    fclose(inputFile);
    fclose(outputFile);
    delete_double_str(json_file);
}

void xml_to_csv(char* xml_file_path, char* csv_file_path) {
    xmlDocPtr doc;
    xmlNodePtr cur;
    FILE* fptr = fopen(csv_file_path, "w");
    fprintf(fptr, "category,isbn,author,title,total,available\n");
    doc = xmlParseFile(xml_file_path);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse XML\n");
        return;
    }
    cur = xmlDocGetRootElement(doc);
    if (cur == NULL) {
        fprintf(stderr, "Empty XML document\n");
        xmlFreeDoc(doc);
        return;
    }
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        if(!xmlStrcmp(cur->name, (const xmlChar *)"book")) {
            char category[100], isbn[100], author[100], title[100], total[100], available[100];
            memset(category, 0, sizeof category);
            memset(isbn, 0, sizeof isbn);
            memset(author, 0, sizeof author);
            memset(title, 0, sizeof title);
            memset(total, 0, sizeof total);
            memset(available, 0, sizeof available);

            xmlChar* category_value = xmlGetProp(cur, (const xmlChar *)"category");
            if (category_value != NULL) {
                strcpy(category, (const char*)category_value);
            }

            xmlNodePtr book_node = cur->xmlChildrenNode;
            while (book_node != NULL) {
                if(!xmlStrcmp(book_node->name, (const xmlChar *)"isbn")) {
                    xmlChar* isbn_value = xmlNodeListGetString(doc, book_node->xmlChildrenNode, 1);
                    if (isbn_value != NULL) {
                        strcpy(isbn, (const char*)isbn_value);
                        xmlFree(isbn_value);
                    }
                }
                if(!xmlStrcmp(book_node->name, (const xmlChar *)"author")) {
                    xmlChar* author_value = xmlNodeListGetString(doc, book_node->xmlChildrenNode, 1);
                    if (author_value != NULL) {
                        strcpy(author, (const char*)author_value);
                        xmlFree(author_value);
                    }
                }
                if(!xmlStrcmp(book_node->name, (const xmlChar *)"title")) {
                    xmlChar* title_value = xmlNodeListGetString(doc, book_node->xmlChildrenNode, 1);
                    if (title_value != NULL) {
                        strcpy(title, (const char*)title_value);
                        xmlFree(title_value);
                    }
                }
                if(!xmlStrcmp(book_node->name, (const xmlChar *)"total")) {
                    xmlChar* total_value = xmlNodeListGetString(doc, book_node->xmlChildrenNode, 1);
                    if (total_value != NULL) {
                        strcpy(total, (const char*)total_value);
                        xmlFree(total_value);
                    }
                }
                if(!xmlStrcmp(book_node->name, (const xmlChar *)"available")) {
                    xmlChar* available_value = xmlNodeListGetString(doc, book_node->xmlChildrenNode, 1);
                    if (available_value != NULL) {
                        strcpy(available, (const char*)available_value);
                        xmlFree(available_value);
                    }
                }
                book_node = book_node->next;
            }
            fprintf(fptr, "%s,%s,%s,%s,%s,%s\n", category, isbn, author, title, total, available);
        }
        cur = cur->next;
    }
    fclose(fptr);
    xmlFreeDoc(doc);
}


int main () {

    // json_to_csv("db.json", "db.csv");
    // csv_to_json("db.csv", "db.json");
    xml_to_csv("db.xml", "db.csv");


    return 0;
}