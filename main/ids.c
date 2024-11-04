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

// User Input - Declaration
void board_guide();
void get_user_input();
void print_userInput_in_boardGuide(int user_input[16]);

// Fringe - Declaration
void insert_to_FringeLL(int to_insert_level, int to_insert_arr[16]);
void print_the_FringeLL();

// User Input - Definition
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

    printf("-------------------------------------------------\n");
    printf("\t      Enter \'-1\' for BLANK\n");
    printf("-------------------------------------------------\n");

}

void get_user_input() {

    char board_guide_label[] = {
        'a', 'b', 'c', 'd',
        'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l',
        'm', 'n', 'o', 'p'
    };
    int user_input_arr[16];
    int i = 0;

    for(i = 0; i < 16; i++) {

        printf("[%c] = ", board_guide_label[i]);
        scanf("%d", &user_input_arr[i]);

    }

    print_userInput_in_boardGuide(user_input_arr);
    insert_to_FringeLL(0, user_input_arr);  // 0 = Level 0, ROOT.

}

void print_userInput_in_boardGuide(int user_input[16]) {

    printf("-------------------------------------------------\n");
    printf("\t\t  CREATED TABLE\n");
    printf("-------------------------------------------------\n");
    int i = 0;

    printf("\t+-------+-------+-------+-------+\n");
    printf("\t|       |       |       |       |\n\t|");
    for (i = 0; i <= 3; i++) {
        if (user_input[i] >= 10) {printf("   %d  |", user_input[i]);}
        else if (user_input[i] == -1){printf("       |");}
        else {printf("   %d   |", user_input[i]);}
    }
    printf("\n\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");
    printf("\t|       |       |       |       |\n\t|");
    for (i = 4; i <= 7; i++) {
        if (user_input[i] >= 10) {printf("   %d  |", user_input[i]);}
        else if (user_input[i] == -1){printf("       |");}
        else {printf("   %d   |", user_input[i]);}
    }
    printf("\n\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");
    printf("\t|       |       |       |       |\n\t|");
    for (i = 8; i <= 11; i++) {
        if (user_input[i] >= 10) {printf("   %d  |", user_input[i]);}
        else if (user_input[i] == -1){printf("       |");}
        else {printf("   %d   |", user_input[i]);}
    }
    printf("\n\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");
    printf("\t|       |       |       |       |\n\t|");
    for (i = 12; i <= 15; i++) {
        if (user_input[i] >= 10) {printf("   %d  |", user_input[i]);}
        else if (user_input[i] == -1){printf("       |");}
        else {printf("   %d   |", user_input[i]);}
    }
    printf("\n\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");

}

// Fringe - Definition
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
    
    print_the_FringeLL();

}

void print_the_FringeLL() {

    printf("\n[THE FRINGE :D]\n");
    struct FringeLL *printer = fringeLL_head;
    int i = 0;

    while(printer != NULL) {

        printf("Level [%d] = ", printer -> level);
        for(i = 0; i < 16; i++) {
            printf("%d ", printer -> fringeLL_arr[i]);
        }
        printf("\n");
        printer = printer -> next;

    }

}

void main() {

    board_guide();      // Show Guide Table
    get_user_input();   // Get User Input
    
}