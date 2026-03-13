#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("test.txt", "r"); 
    
    if (fp == NULL) {
        printf("Error: File not found.\n");
        return 1;
    }

    int c;
    while ((c = fgetc(fp)) != EOF) {
        unsigned char uc = (unsigned char)c;

        if (uc == '\n') {
            printf("'\\n' ");
        } else if (uc == '\t') {
            printf("'\\t' ");
        } else if (uc == ' ') {
            printf("' ' ");
        } else if (uc == '\r') {
            continue; 
        } else {
            printf("'%c' ", uc);
        }
    }

    fclose(fp);
    printf("\n"); 
    return 0;
}
