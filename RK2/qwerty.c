#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml2\include\libxml\parser.h>

#include <libxml\tree.h>

#define MAX_DATA_SIZE 1024
#define MAX_LINES_DB 1024

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

char** read_import(char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: could not open file %s\n", filename);
        exit(1);
    }

    char** data = malloc(MAX_DATA_SIZE * sizeof(char*));
    char* buffer = NULL;

    int index = 0;
    while ((buffer = read_string(file)) != NULL) {
        data[index] = strdup(buffer);
        index++;
    }

    data[index] = NULL;

    fclose(file);

    return data;
}

char** read_xml(char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: could not open file %s\n", filename);
        exit(1);
    }

    char** data = malloc(MAX_DATA_SIZE * sizeof(char*));
    char* buffer = NULL;

    int index = 0;
    while ((buffer = read_string(file)) != NULL) {
        data[index] = strdup(buffer);
        index++;
    }

    data[index] = NULL;

    fclose(file);

    return data;
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

void json_to_csv (char** json_data, char* filename) {
    FILE* file = fopen(filename, "a");

    if (file == NULL) {
        printf("Error: could not open file %s\n", filename);
        exit(1);
    }
    
    for (int i = 0; json_data[i] != NULL; i++) {
        char field[100];
        
        for (int j = 0; json_data[i][j] != '}';){
            while (json_data[i][j++] != ':');
            int k = 0;
            while (json_data[i][j] != ',' && json_data[i][j] != '}')
                field[k++] = json_data[i][j++];
            
            field[k] = '\0';
            fprintf(file, "%s;", field);
        }
        fputc('\n', file);
    }
    fclose(file);
    delete_double_str(filename);
}

void xml_to_csv (char** xml_data, char* filename) {
    FILE* file = fopen(filename, "a");

    if (file == NULL) {
        printf("Error: could not open file %s\n", filename);
        exit(1);
    }
    
    
    fclose(file);
    delete_double_str(filename);
}

int main (int argc, char** argv) {
    char* input_filename = argv[1];
    char* output_filename = argv[2];

    //char** json_data = read_import(input_filename);
    //json_to_csv(json_data, output_filename);

    char** xml_data = read_import(input_filename);
    xml_to_csv(xml_data, output_filename);
    

    // for (int i = 0; json_data[i] != NULL; i++) {
    //     free(json_data[i]);
    // }
    // free(json_data);

    for (int i = 0; xml_data[i] != NULL; i++) {
        free(xml_data[i]);
    }
    free(xml_data);

    return 0;
}