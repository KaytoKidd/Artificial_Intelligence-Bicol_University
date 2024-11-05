#include <stdio.h>
#include <stdlib.h>

struct SolutionPathLL {

    int movement;
    struct SolutionPathLL *next;

};

struct SolutionPathLL *solutionPathLL_head[4];

void insert_to_solutionPathLL(int what_movement, int which_index_head_of_solutionPathLL);
void insert_to_solutionPathLL(int what_movement, int which_index_head_of_solutionPathLL) {

    struct SolutionPathLL *new_node = (struct SolutionPathLL *)malloc(sizeof(struct SolutionPathLL));
    struct SolutionPathLL *iterator;

    if(solutionPathLL_head[which_index_head_of_solutionPathLL] == NULL) {
        solutionPathLL_head[which_index_head_of_solutionPathLL] = new_node;
    } else {
        iterator = solutionPathLL_head[which_index_head_of_solutionPathLL];
        while(iterator -> next != NULL) {
            iterator = iterator -> next;
        }
        iterator -> next = new_node;
    }

    new_node -> movement = what_movement;
    new_node -> next = NULL;

}

void print_the_solutionPathLL() {

    struct SolutionPathLL *printer;
    int i = 0;

    for(i = 0; i < 4; i++) {
        printer = solutionPathLL_head[i];
        while(printer != NULL) {
            printf("%d ", printer -> movement);
            printer = printer -> next;
        }
        printf("\n");
    }

}

void main() {

    insert_to_solutionPathLL(4, 2);
    insert_to_solutionPathLL(55, 3);
    insert_to_solutionPathLL(1, 3);
    insert_to_solutionPathLL(4, 0);
    insert_to_solutionPathLL(9, 2);
    insert_to_solutionPathLL(6, 3);

    print_the_solutionPathLL();

}