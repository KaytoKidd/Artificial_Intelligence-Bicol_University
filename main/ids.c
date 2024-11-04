#include <stdio.h>
#include <stdlib.h>

struct ExpandedLL {

    int expandedLL_arr[16];
    struct ExpandedLL *next;

};

struct FringeLL {

    int level;
    int fringeLL_arr[16];
    struct FringeLL *next;

};

struct ExpandedLL *expandedLL_head = NULL;
struct FringeLL *fringeLL_head = NULL;

// User Input
void board_guide();
void get_user_input(char board_guide_label[16]);

// Fringe
void insert_to_FringeLL(int to_insert_level, int to_insert_arr[16]);

void board_guide() {

    printf("-------------------------------------------------\n");
    printf("\t\t   BOARD GUIDE\n");
    printf("-------------------------------------------------\n");

    printf("\t+-------+-------+-------+-------+\n");
    printf("\t|       |       |       |       |\n");
    printf("\t|   a   |   b   |   c   |   d   |\n");
    printf("\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");
    printf("\t|       |       |       |       |\n");
    printf("\t|   e   |   f   |   g   |   h   |\n");
    printf("\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");
    printf("\t|       |       |       |       |\n");
    printf("\t|   i   |   j   |   k   |   l   |\n");
    printf("\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");
    printf("\t|       |       |       |       |\n");
    printf("\t|   m   |   n   |   o   |   p   |\n");
    printf("\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");

    char board_guide_label[] = {
        'a', 'b', 'c', 'd',
        'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l',
        'm', 'n', 'o', 'p'
    };

    printf("-------------------------------------------------\n");
    printf("\t      Enter \'-1\' for BLANK\n");
    printf("-------------------------------------------------\n");
    get_user_input(board_guide_label);

}

void get_user_input(char board_guide_label[16]) {

    int user_input_arr[16];
    int i = 0;

    for(i = 0; i < 16; i++) {

        printf("[%c] = ", board_guide_label[i]);
        scanf("%d", &user_input_arr[i]);

    }

}

void insert_to_FringeLL(int to_insert_level, int to_insert_arr[16]) {

    struct FringeLL *new_node = (struct FringeLL *)malloc(sizeof(struct FringeLL));
    struct FringeLL *iterator = fringeLL_head;
    int i = 0;

    if(fringeLL_head == NULL) {
        fringeLL_head = new_node;
    } else{
        iterator = fringeLL_head;
        while(iterator -> next != NULL) {
            iterator = iterator -> next;
        }
        iterator -> next = new_node;
    }

    new_node -> level = to_insert_level;
    for(i = 0; i < 16; i++) {
        new_node -> fringeLL_arr[i] = to_insert_arr[i];
    }
    new_node -> next = NULL;

}

void main() {

    board_guide();
    
}