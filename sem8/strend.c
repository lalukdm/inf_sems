#include <stdio.h>
#include <string.h>

int strend(char *s, char *t) {
    int len_s = strlen(s);
    int len_t = strlen(t);

    if (len_t > len_s)
        return 0;

    s += len_s - len_t;

    while (*t != '\0') {
        if (*s != *t)
            return 0;
        s++;
        t++;
    }

    return 1;
}


int main (){
    char str[20] = "";
    char str2[20] = "";
    
    while(1){
        puts("enter string to search for:");
        scanf("%s", &str);
        puts("enter string to look for at the end:");
        scanf("%s", &str2);

        printf("%s\n\n\n", (strend(str, str2) ? "True" : "False"));
    }

    return 0;
}