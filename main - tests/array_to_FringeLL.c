#include <stdio.h>
#include <stdlib.h>

struct ExpandedLL {

    int expanded_arr[16];
    struct ExpandedLL *next;

};

struct FringeLL {

    int level;
    int fringe_arr[16];
    struct FringeLL *next;

};

struct ExpandedLL *expandedLL_head = NULL;
struct FringeLL *fringeLL_head = NULL;

void append_to_LL(int the_level, int the_arr[16]);
void print_the_LL();

void append_to_LL(int the_level, int the_arr[16]) {

    struct FringeLL *new_node = (struct FringeLL *)malloc(sizeof(struct FringeLL));
    struct FringeLL *iterator = fringeLL_head;
    int i = 0;

    if (fringeLL_head == NULL) {
        fringeLL_head = new_node;
    } else {
        iterator = fringeLL_head;
        while (iterator -> next != NULL) {
            iterator = iterator -> next;
        }
        iterator -> next = new_node;
    }

    new_node -> level = the_level;
    for (i = 0; i < 16; i++) {
        new_node -> fringe_arr[i] = the_arr[i];
    }
    new_node -> next = NULL;

}

void print_the_LL() {

    struct FringeLL *printer = fringeLL_head;
    int i = 0;

    while (printer != NULL) {
        printf("Level = %d\n", printer -> level);
        for (i = 0; i < 16; i++) {
            printf("%d ", printer -> fringe_arr[i]);
        }
        printf("\n");
        printer = printer -> next;
    }

}

void main() {

    int arr1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int arr2[] = {16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    int arr3[] = {1,2,3,4,5,6,7,8,9,10,9,8,7,6,5,4};
    int arr4[] = {10,9,8,7,6,5,4,3,2,1,2,3,4,5,6,7};

    int level1 = 3;
    int level2 = 1;
    int level3 = 4;
    int level4 = 2;

    append_to_LL(level1, arr1);
    append_to_LL(level2, arr2);
    append_to_LL(level3, arr3);
    append_to_LL(level4, arr4);

    print_the_LL();

}