#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFSIZE 100

static char buf[BUFSIZE];
static int bufp = 0;

int getop(char s[]) {

    int i = 0, c;
    
    while ((s[0] = c = (bufp > 0) ? buf[--bufp] : getchar()) == ' ' || c == '\t');
    
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;
    
    if (isdigit(c))
        while (isdigit(s[++i] = c = (bufp > 0) ? buf[--bufp] : getchar()));

    if (c == '.')
        while (isdigit(s[++i] = c = (bufp > 0) ? buf[--bufp] : getchar()));

    s[i] = '\0';
    if (c != EOF){
        if (bufp >= BUFSIZE) {
            printf("ungetch: too many characters\n");
            exit(333);
        }
        else
            buf[bufp++] = c;
    }
    return '0';
}