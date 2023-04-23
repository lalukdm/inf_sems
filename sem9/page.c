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

int main(int argc, char **argv) {
    if (argc < 5) {
        printf("Usage: %s -s [num of str] -l [lenth of str]\n", argv[0]);
        return 1;
    }

    int str_on_page = atof(argv[2]);
    int len_str = atof(argv[4]);

    FILE *file = fopen("file3.txt", "r");

    char* buffer = NULL;
    char partbuf[len_str];

    int current_str = 1;
    int current_page = 1;
    
    while ((buffer = read_string(file)) != NULL) {
        
        
        int current_len = strlen(buffer);
        if (current_len > len_str) {
            for (int i = 0; i < ((current_len + len_str - 1) / len_str); i++) {
                strncpy(partbuf, buffer + (i * len_str), len_str);
                partbuf[len_str] = '\0';
                printf("\t%d: %s\n", current_str++, partbuf);
                         
                if (current_str == str_on_page + 1) {
                    printf("\t- Page %d -\n\n\n",  current_page++);
                    current_str = 1;
                }
            }

        } else
            printf("\t%d: %s\n", current_str++, buffer);
        

        if (current_str == str_on_page + 1) {
            printf("\t- Page %d -\n\n\n",  current_page++);
            current_str = 1;
        }
    }
    printf("\t- Page %d -\n\n\n",  current_page++);

    fclose(file);

    return 0;
}