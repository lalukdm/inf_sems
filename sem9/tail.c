#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    str[size-1] = '\0';

    return str;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file> [N]\n", argv[0]);
        return 1;
    }

    char *file_path = argv[1];
    int n = argc > 2 ? atoi(argv[2]) : 5;

    FILE *file = fopen(file_path, "r");

    char* buffer = NULL;
    char* lines[n];
    int num_lines = 0;

    for (int i = 0; i < n; i++)
        lines[i] = NULL;

    while ((buffer = read_string(file)) != NULL) {
        lines[num_lines] = malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(lines[num_lines], buffer);
        num_lines++;

        if (num_lines == n + 1) {
            for(int i = 0; i < n; i++)
                strcpy(lines[i], lines[i + 1]);

            num_lines--;
            free(lines[num_lines]);
        }
        buffer = NULL;
    }

    for (int i = 0; i < n; i++)
        printf("\t%s\n", lines[i]);

    fclose(file);

    for (int i = 0; i < n; i++)
        free(lines[i]);

    return 0;
}