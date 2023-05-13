#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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