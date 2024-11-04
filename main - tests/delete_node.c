#include <stdio.h>
#include <stdlib.h>

struct FringeLL {

    int fringeLL_arr[16];
    struct FringeLL *next;

};

struct FringeLL *fringeLL_head = NULL;

void insert(int to_insert_arr[16]) {

    struct FringeLL *new_node = (struct FringeLL *)malloc(sizeof(struct FringeLL));
    struct FringeLL *iterator = fringeLL_head;

    if(fringeLL_head == NULL) {
        fringeLL_head = new_node;
    } else {
        iterator = fringeLL_head;
        while(iterator -> next != NULL) {
            iterator = iterator -> next;
        }
        iterator -> next = new_node;
    }

    int i = 0;
    for(i = 0; i < 16; i++) {
        new_node -> fringeLL_arr[i] = to_insert_arr[i];
    }
    new_node -> next = NULL;

}

void remove_from_FringeLL(int to_remove_arr[16]) {

    struct FringeLL *connector = fringeLL_head;
    struct FringeLL *deleter = fringeLL_head;
    int in_the_beginning = 0;

    while(deleter != NULL) {

        int all_the_same = 0;
        int i = 0;

        for(i = 0; i < 16; i++) {
            if(deleter -> fringeLL_arr[i] == to_remove_arr[i])
                all_the_same++; // If all_the_same == 16, means array is same as to_remove_arr[16].
            else
                break;          // Current array is not the same with to_remove_arr[16]
        }

        if(all_the_same == 16)  // We want to end, so that 'deleter' will have the address of what to delete.
            break;

        in_the_beginning++;
        connector = deleter;
        deleter = deleter -> next;

    }

    if(in_the_beginning == 0)
        fringeLL_head = fringeLL_head -> next;
    else
        connector -> next = deleter -> next;

    free(deleter);

}

void printer() {

    struct FringeLL *printer = fringeLL_head;

    while(printer != NULL) {
        int i = 0;
        for(i = 0; i < 16; i++) {
            printf("%d ", printer -> fringeLL_arr[i]);
        }
        printf("\n");
        printer = printer -> next;
    }

}

void main() {

    int arr1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int arr2[] = {1,2,3,4,5,6,7,8,9,10,10,9,8,7,6,5};
    int arr3[] = {16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};

    int toDelete[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

    printf("[BEFORE]\n");
    insert(arr1);
    insert(arr2);
    insert(arr3);
    printer();

    printf("\n[AFTER]\n");
    remove_from_FringeLL(toDelete);
    printer();

}