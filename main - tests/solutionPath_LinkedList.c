/*
-   The purpose of this file is to show how the *myStruct_head[4] is inserted the addresses
    of each possible movements (myArr[], different name from what we have in ids.c)
-   Just a demonstration how it works.

HOW DOES IT WORK?
-   From the very beginning, we have a function whose purpose is only to insert the head
    for the myStruct_head[] (different name from ids.c).
-   Next, to insert values to each of the head from the myStruct_head[], we have another
    function. 
-   WHY SEPARATE FUNCTION?
        - To ensure that the head is set first.
        - To ensure that whatever to be added next, will already have a head to start with.
        - Makes it readable, reliable to debug in the future.
*/

#include <stdio.h>
#include <stdlib.h>

struct MyStruct {

    int data;
    struct MyStruct *next;

};

struct MyStruct *myStruct_head[4];

void printer();
void add_newStuff();

void printer() {

    int i = 0;

    for(i = 0; i < 4; i++) {

        struct MyStruct *iterator = myStruct_head[i];
        while(iterator != NULL) {
            printf("%d ", iterator -> data);
            iterator = iterator -> next;
        }
        printf("\n");

    }

}

void add_newStuff() {

    int which_head = 0;
    int insert_val = 0;

    printf("\nWhich head to insert?: ");
    scanf("%d", &which_head);
    printf("Enter value to insert: ");
    scanf("%d", &insert_val);
    printf("\n");

    struct MyStruct *new_node = (struct MyStruct *)malloc(sizeof(struct MyStruct));
    struct MyStruct *inserter = myStruct_head[which_head];

    while(inserter -> next != NULL) {
        inserter = inserter -> next;
    }
    inserter -> next = new_node;
    new_node -> data = insert_val;
    new_node -> next = NULL;


}

void main() {
    
    int myArr[] = {2, 1, 4, 3};
    int i = 0;
    int j = 0;
    
    while(i != 4) {

        struct MyStruct *new_node = (struct MyStruct *)malloc(sizeof(struct MyStruct));
        myStruct_head[i] = new_node;
        new_node -> data = myArr[i];
        new_node -> next = NULL;

        i++;
    }

    printer();
    add_newStuff();
    printer();
    add_newStuff();
    printer();
    add_newStuff();
    printer();

}