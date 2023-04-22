#include "calc.h"

int main(){

    int type;
    double op2;
    char s[MAXOP];

    puts("Input the expression to calculate:");

    while ((type = getop(s)) != EOF) {
        switch (type) {

            case '0':
                push(atof(s));
                break;

            case '+':
                push(pop() + pop());
                break;

            case '*':
                push(pop() * pop());
                break;

            case '-':
                op2 = pop();
                push(pop() - op2);
                break;

            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else {
                    printf("error: zero divisor\n");
                    return -1;
                }
                break;

            case '^':
                op2 = pop();
                push(pow(pop(), op2));
                break;

            case '%' :
                op2 = pop();
                if (op2 != 0.0)
                    push((int) (pop() / op2));
                else {
                    printf("error: zero divisor\n");
                    return -1;
                }
                break;

            case 's':
                push(sin(pop()));
                break;

            case 'c':
                push(cos(pop()));
                break;

            case '\n' :
                printf("\t%.8g\n", pop());
                puts("Input the expression to calculate:");
                break;

            default:
                printf("error: unknown command %s\n", s);
                return -1;

        }
    }

    return 0;
}

