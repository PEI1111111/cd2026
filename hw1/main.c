#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_space(char c) { return (c == ' ' || c == '\t' || c == '\n' || c == '\r'); }
int is_alpha(char c) { return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'); }
int is_digit(char c) { return (c >= '0' && c <= '9'); }
int is_alnum(char c) { return (is_alpha(c) || is_digit(c)); }

void print_token(char *str) {
    if (strcmp(str, "int") == 0) printf("%s: TYPE_TOKEN\n", str);
    else if (strcmp(str, "main") == 0) printf("%s: MAIN_TOKEN\n", str);
    else if (strcmp(str, "if") == 0) printf("%s: IF_TOKEN\n", str);
    else if (strcmp(str, "else") == 0) printf("%s: ELSE_TOKEN\n", str);
    else if (strcmp(str, "while") == 0) printf("%s: WHILE_TOKEN\n", str);
    else printf("%s: ID_TOKEN\n", str);
}

int main() {
    int c;
    char buffer[256];
    int i;

    while ((c = getchar()) != EOF) {
        if (is_space(c)) continue;

        if (is_alpha(c)) {
            i = 0;
            buffer[i++] = (char)c;
            while (is_alnum(c = getchar())) {
                buffer[i++] = (char)c;
            }
            ungetc(c, stdin); 
            buffer[i] = '\0';
            print_token(buffer);
        }
        
        else if (is_digit(c)) {
            i = 0;
            buffer[i++] = (char)c;
            while (is_digit(c = getchar())) {
                buffer[i++] = (char)c;
            }
            ungetc(c, stdin);
            buffer[i] = '\0';
            printf("%s: LITERAL_TOKEN\n", buffer);
        }

        else {
            int next;
            switch (c) {
                case '=':
                    next = getchar();
                    if (next == '=') printf("==: EQUAL_TOKEN\n");
                    else { ungetc(next, stdin); printf("=: ASSIGN_TOKEN\n"); }
                    break;
                case '>':
                    next = getchar();
                    if (next == '=') printf(">=: GREATEREQUAL_TOKEN\n");
                    else { ungetc(next, stdin); printf(">: GREATER_TOKEN\n"); }
                    break;
                case '<':
                    next = getchar();
                    if (next == '=') printf("<=: LESSEQUAL_TOKEN\n");
                    else { ungetc(next, stdin); printf("<: LESS_TOKEN\n"); }
                    break;
                case '+': printf("+: PLUS_TOKEN\n"); break;
                case '-': printf("-: MINUS_TOKEN\n"); break;
                case '(': printf("(: LEFTPAREN_TOKEN\n"); break;
                case ')': printf("): REFTPAREN_TOKEN\n"); break;
                case '{': printf("{: LEFTBRACE_TOKEN\n"); break;
                case '}': printf("}: REFTBRACE_TOKEN\n"); break; 
                case ';': printf(";: SEMICOLON_TOKEN\n"); break;
                default: break; 
            }
        }
    }

    return 0;
}
