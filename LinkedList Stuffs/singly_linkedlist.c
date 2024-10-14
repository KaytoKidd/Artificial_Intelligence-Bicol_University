#include <stdio.h>
#include <stdlib.h>

struct node {

    int data;
    struct node *next;

};

struct node *head = NULL;

void main() {

    int i = 0;
    for(i = 0; i < 5; i++) {

        struct node *inputData = malloc(sizeof(struct node *));
        if (head == NULL) {
            head = inputData;
        } else {
            struct node *iterator = head;
            while (iterator -> next != NULL) {
                iterator = iterator -> next;
            }
            iterator -> next = inputData;
        }
        inputData -> data = i;
        inputData -> next = NULL;

    }

    struct node *letsgooo = head;
    while (letsgooo != NULL) {
        printf("%d\n", letsgooo -> data);
        letsgooo = letsgooo -> next;
    }

}