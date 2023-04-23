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

int main() {

    FILE *file1 = fopen("file1.txt", "r");
    FILE *file2 = fopen("file2.txt", "r");

    char* buffer1 = NULL;
    char* buffer2 = NULL;

    while (1) {
        if ((buffer1 = read_string(file1)) != NULL && (buffer2 = read_string(file2)) != NULL) {
            printf("\t%s\n", buffer1);
            printf("\t%s\n", buffer2);
        } else if (buffer1 != NULL) {
            do {
                printf("\t%s\n", buffer1);
            } while((buffer1 = read_string(file1)) != NULL);     
        } else if (buffer2 != NULL) {
            do {
                printf("\t%s\n", buffer2);
            } while((buffer2 = read_string(file2)) != NULL);
        } else break;

    }


    fclose(file1);
    fclose(file2);

    return 0;
}