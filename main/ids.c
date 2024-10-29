#include <stdio.h>
#include <stdlib.h>

// board_guide(), get_user_input(), and print_user_input() are all for user interaction only.
// However, user_input[] will be used for the entire program.

// User Interaction Functions - Declaration
void board_guide();
void get_user_input(char board_guide_label[]);
void print_user_input(int user_input[]);

// Calculation Functions - Declaration
void heirarchy_of_movements();

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

    get_user_input(board_guide_label);

}

void get_user_input(char board_guide_label[]) {

    int user_input[16];
    int i = 0;

    printf("-------------------------------------------------\n");
    printf("\t      Enter \'-1\' for BLANK\n");
    printf("-------------------------------------------------\n");

    for (i = 0; i < 16; i++) {

        printf("[%c] = ", board_guide_label[i]);
        scanf("%d", &user_input[i]);

    }

    print_user_input(user_input);

}

void print_user_input(int user_input[]) {

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

void heirarchy_of_movements() {

    // Hierarchy of Priority: UP -> DOWN -> LEFT -> RIGHT
    // UP       - 96
    // DOWN     - 97
    // LEFT     - 98
    // RIGHT    - 99

    int movements[16][3][4] = {
        {{1}, {5, 2}, {96, 99}},
        {{2}, {6, 1, 3}, {97, 98, 99}},
        {{3}, {7, 2, 40}, {97, 98, 99}},
        {{4}, {8, 3}, {97, 98}},
        {{5}, {1, 9, 6}, {96, 97, 99}},
        {{6}, {2, 10, 5, 7}, {96, 97, 98, 99}},
        {{7}, {3, 11, 6, 8}, {96, 97, 98, 99}},
        {{8}, {4, 12, 7}, {96, 97, 98}},
        {{9}, {5, 13, 10}, {96, 97, 99}},
        {{10}, {6, 14, 9, 11}, {96, 97, 98, 99}},
        {{11}, {7, 15, 10, 12}, {96, 97, 98, 99}},
        {{12}, {8, 16, 11}, {96, 97, 98}},
        {{13}, {9, 14}, {96, 99}},
        {{14}, {10, 13, 15}, {96, 98, 99}},
        {{15}, {11, 14, 16}, {96, 98, 99}},
        {{16}, {12, 15}, {96, 98}}
    };

}

void main() {
    board_guide();
}