#include <stdio.h>   
#include <stdlib.h> 
#include <string.h> 

typedef struct Node {
    char ch;                
    int count;              
    struct Node* next;      
} Node;

int main() {
    FILE *fp = fopen(__FILE__, "r");
    if (fp == NULL) {
        return 1;
    }

    Node *head = NULL;     
    Node *tail = NULL;     
    
    Node *lookup[256] = {NULL};

    int c;
    while ((c = fgetc(fp)) != EOF) {
        unsigned char uc = (unsigned char)c;

        if (lookup[uc] == NULL) {
            Node *newNode = (Node *)malloc(sizeof(Node));
            if (newNode == NULL) break;
            
            newNode->ch = (char)uc;
            newNode->count = 1;      
            newNode->next = NULL;

            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            
            lookup[uc] = newNode;
        } else {
            lookup[uc]->count++;
        }
    }
    fclose(fp);
    Node *current = head;
    while (current != NULL) {
        if (current->ch >= 32) { 
            printf("%c:%d\n", current->ch, current->count);
        } else if (current->ch == '\n') {
            printf("\\n:%d\n", current->count);
        }
        current = current->next;
    }
    current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    return 0;
}
