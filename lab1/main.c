#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char ch;
    struct Node* next;
} Node;

int main() {
    FILE *fp = fopen("main.c", "r"); 
    if (fp == NULL) {
        printf("Error: File not found.\n");
        return 1;
    }

    Node *head = NULL;
    Node *tail = NULL;

    int c;
    while ((c = fgetc(fp)) != EOF) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL) break;
        
        newNode->ch = (char)c;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    fclose(fp);

    Node *current = head;
    while (current != NULL) {
        unsigned char uc = (unsigned char)current->ch;

        if (uc == '\n') {
            printf("'\\n' ");
        } else if (uc == '\t') {
            printf("'\\t' ");
        } else if (uc == ' ') {
            printf("' ' ");
        } else if (uc == '\r') {
        } else {
            printf("'%c' ", uc);
        }
        current = current->next;
    }
    printf("\n");

    current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
