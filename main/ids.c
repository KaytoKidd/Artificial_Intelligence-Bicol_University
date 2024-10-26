#include <stdio.h>
#include <stdlib.h>

void board_guide();
void get_user_input(char board_guide_label[]);
void print_user_input(int user_input[]);

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
        if (user_input[i] >= 10 || user_input[i] == -1) {printf("   %d  |", user_input[i]);} else {printf("   %d   |", user_input[i]);}
    }
    printf("\n\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");
    printf("\t|       |       |       |       |\n\t|");
    for (i = 4; i <= 7; i++) {
        if (user_input[i] >= 10 || user_input[i] == -1) {printf("   %d  |", user_input[i]);} else {printf("   %d   |", user_input[i]);}
    }
    printf("\n\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");
    printf("\t|       |       |       |       |\n\t|");
    for (i = 8; i <= 11; i++) {
        if (user_input[i] >= 10 || user_input[i] == -1) {printf("   %d  |", user_input[i]);} else {printf("   %d   |", user_input[i]);}
    }
    printf("\n\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");
    printf("\t|       |       |       |       |\n\t|");
    for (i = 12; i <= 15; i++) {
        if (user_input[i] >= 10 || user_input[i] == -1) {printf("   %d  |", user_input[i]);} else {printf("   %d   |", user_input[i]);}
    }
    printf("\n\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");

}

void main() {
    board_guide();
}

/*

temporary
printf("\t+---------------+---------------+---------------+---------------+\n");
    printf("\t|\t\t|\t\t|\t\t|\t\t|\n"); printf("\t|\t\t|\t\t|\t\t|\t\t|\n");
    printf("\t|\ta\t|\tb\t|\tc\t|\td\t|\n");
    printf("\t|\t\t|\t\t|\t\t|\t\t|\n"); printf("\t|\t\t|\t\t|\t\t|\t\t|\n");
    printf("\t+---------------+---------------+---------------+---------------+\n");
    printf("\t|\t\t|\t\t|\t\t|\t\t|\n"); printf("\t|\t\t|\t\t|\t\t|\t\t|\n");
    printf("\t|\te\t|\tf\t|\tg\t|\th\t|\n");
    printf("\t|\t\t|\t\t|\t\t|\t\t|\n"); printf("\t|\t\t|\t\t|\t\t|\t\t|\n");
    printf("\t+---------------+---------------+---------------+---------------+\n");
    printf("\t|\t\t|\t\t|\t\t|\t\t|\n"); printf("\t|\t\t|\t\t|\t\t|\t\t|\n");
    printf("\t|\ti\t|\tj\t|\tk\t|\tl\t|\n");
    printf("\t|\t\t|\t\t|\t\t|\t\t|\n"); printf("\t|\t\t|\t\t|\t\t|\t\t|\n");
    printf("\t+---------------+---------------+---------------+---------------+\n");
    printf("\t|\t\t|\t\t|\t\t|\t\t|\n"); printf("\t|\t\t|\t\t|\t\t|\t\t|\n");
    printf("\t|\tm\t|\tn\t|\to\t|\tp\t|\n");
    printf("\t|\t\t|\t\t|\t\t|\t\t|\n"); printf("\t|\t\t|\t\t|\t\t|\t\t|\n");
    printf("\t+---------------+---------------+---------------+---------------+\n");

printf("\t+-------+-------+-------+-------+\n");
    printf("\t|       |       |       |       |\n");
    for (i = 0; i <= 3; i++) {
        if (user_input[i] >= 10) {printf("   %d  |", user_input[i]);} else {printf("   %d   |", user_input[i]);}
    }
    printf("\t|   %d   |   %d   |   %d   |   %d   |\n", user_input[0], user_input[1], user_input[2], user_input[3]);
    printf("\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");
    printf("\t|       |       |       |       |\n");
    printf("\t|   %d   |   %d   |   %d   |   %d   |\n", user_input[4], user_input[5], user_input[6], user_input[7]);
    printf("\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");
    printf("\t|       |       |       |       |\n");
    printf("\t|   %d   |   %d   |   %d   |   %d   |\n", user_input[8], user_input[9], user_input[10], user_input[11]);
    printf("\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");
    printf("\t|       |       |       |       |\n");
    printf("\t|   %d   |   %d   |   %d   |   %d   |\n", user_input[12], user_input[13], user_input[14], user_input[15]);
    printf("\t|       |       |       |       |\n");
    printf("\t+-------+-------+-------+-------+\n");
*/