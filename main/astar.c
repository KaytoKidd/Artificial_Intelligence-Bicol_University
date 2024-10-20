#include <stdio.h>
#include <stdlib.h>

struct ids_LL {

    char data;
    struct ids_LL *next;

};
struct astar_LL {

    char data;
    struct astar_LL *next;

};

struct ids_LL *ids_LL_HEAD = NULL;
struct astar_LL *astar_LL_HEAD = NULL;

void fixed_user_input();
void pass_to_ids_LL(int which_table[], int length);
void pass_to_astar_LL(int which_table[], int length);
void print_astar_LL();
void delete_astar_LL();

void fixed_user_input() {

    int easy_table[] = {
                            4, 2, 3, -1,
                            5, 1, 6, 7,
                            8, 9, 10, 11,
                            12, 13, 14, 15
                       };
    int medium_table[] = {
                            5, 6, 2, 3,
                            1, -1, 10, 7,
                            4, 13, 9, 15,
                            8, 12, 11, 14
                          };
    int hard_table[] = {
                            1, 2, 3, 4,
                            5, 6, 7, 8,
                            9, 10, 11, 15,
                            13, 14, 12, -1
                       };
    int worst_table[] = {
                            1, 6, 2, 3,
                            5, 10, 7, 4,
                            9, -1, 11, 8,
                            13, 14, 15, 12
                        };

    pass_to_astar_LL(easy_table, 16);
    pass_to_astar_LL(medium_table, 16);
    pass_to_astar_LL(hard_table, 16);
    pass_to_astar_LL(worst_table, 16);

}

void pass_to_astar_LL(int which_table[], int length) {

    int i = 0;
    for(i = 0; i < length; i++) {

        struct astar_LL *new_node = malloc(sizeof(struct astar_LL *));
        struct astar_LL *iterator = astar_LL_HEAD;
        
        if(astar_LL_HEAD == NULL) {
            astar_LL_HEAD = new_node;
        } else {
            while(iterator -> next != NULL) {
                iterator = iterator -> next;
            }
            iterator -> next = new_node;
        }

        new_node -> data = which_table[i];
        new_node -> next = NULL;

    }
    
    print_astar_LL();

}

// Temporary, just to see that array is inserted successfully in linkedlist.
// Including the counter for 4 digits per row.
// Used \t to make spaces equal, forming a 4x4 square pattern.
void print_astar_LL() {

    struct astar_LL *printer = astar_LL_HEAD;
    int counter = 1;

    while(printer != NULL) {

        if(printer -> data == -1)
            printf(" \t");
        else
            printf("%d\t", printer -> data);

        printer = printer -> next;
        if(counter % 4 == 0)
            printf("\n");
        counter += 1;
    }

    printf("\n");
    delete_astar_LL();

}

void delete_astar_LL() {

    struct astar_LL *deleter = astar_LL_HEAD;
    struct astar_LL *iterator = astar_LL_HEAD;

    while(iterator != NULL) {
        deleter = iterator;
        iterator = iterator -> next;
        free(deleter);
    }

    astar_LL_HEAD = NULL;

}

void main() {

    fixed_user_input();

}