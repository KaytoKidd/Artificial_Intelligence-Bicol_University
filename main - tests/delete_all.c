#include <stdio.h>
#include <stdlib.h>

struct LL {

    int data;
    struct LL *next;

};

struct LL *ll_head = NULL;

void insert(int val);
void printer();
void delete_LL();

void insert(int val) {

    struct LL *new_node = (struct LL *)malloc(sizeof(struct LL));
    struct LL *iterator = ll_head;

    if(ll_head == NULL) {
        ll_head = new_node;
    } else {
        iterator = ll_head;
        while(iterator -> next != NULL) {
            iterator = iterator -> next;
        }
        iterator -> next = new_node;
    }

    new_node -> data = val;
    new_node -> next = NULL;

}

void printer() {

    printf("LL = ");
    struct LL *printer = ll_head;

    while(printer != NULL) {
        printf("%d ", printer -> data);
        printer = printer -> next;
    }
    printf("\n");

}

void delete_LL() {

    struct LL *freer = ll_head;

    while(ll_head != NULL) {
        freer = ll_head;
        ll_head = ll_head -> next;
        free(freer);
    }

    ll_head = NULL; // Not mandatory, redundant. But good practice.

}

void main() {

    int val1 = 1;
    int val2 = 2;
    int val3 = 3;
    int val4 = 4;

    insert(val1);
    insert(val2);
    insert(val3);
    insert(val4);
    
    printer();
    delete_LL();
    printer();

    insert(55);
    insert(44);
    insert(33);
    insert(22);
    insert(11);
    insert(12);

    printer();
    delete_LL();
    printer();

}