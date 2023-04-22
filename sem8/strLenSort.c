#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void ShellSort(char** arr, int n, int max_len) {
    int gap = n / 2;
    while (gap > 0) {      
        for (int i = gap; i < n; i++) {
            char temp[max_len];
            strcpy(temp, arr[i]);               
            int j;
            for (j = i; j >= gap && strlen(arr[j - gap]) > strlen(temp); j -= gap) {
                strcpy(arr[j], arr[j - gap]);     
            }
            strcpy(arr[j], temp);
        }
        gap /= 2;
    }
}

char* read_string() {
    char* str = NULL;
    
    int size = 0;
    int c;

    while (c = getchar(), c != '\n') {
        str = realloc(str, ++size * sizeof(char));

        if (str == NULL) 
            return str;

        str[size-1] = c;
    }

    str = realloc(str, ++size * sizeof(char));
    str[size-1] = '\0';

    return str;
}

int main(){
    int num_strings;
    puts("enter number of strings");
    scanf("%d", &num_strings);

    char* str;
    int max_len;

    puts("enter strings with 'Enter'");
    char ** strings = (char **)malloc(num_strings * sizeof(char *));
    for (int i = 0; i <= num_strings; i++){
        str = read_string();
        int current_len = strlen(str);
        max_len = current_len > max_len ? current_len : max_len;
        strings[i] = (char *)malloc((current_len + 1) * sizeof(char));
        strcpy(strings[i], str);
    }

    free(str);

    ShellSort(strings, num_strings, max_len);

    puts("\n\n\nsorted string:");
    for (int i = 0; i <= num_strings; i++) {
        printf("%s\n", strings[i]);
    }

    for (int i = 0; i <= num_strings; i++)
        free(strings[i]);
    free(strings);



    return 0;
}