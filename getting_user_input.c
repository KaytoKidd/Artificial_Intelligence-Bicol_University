#include <stdio.h>
#include <stdlib.h>

void guideTable();
void getUserInput();

struct Puzzle15 {
    int data;
    struct Puzzle15 *next;
};

struct Puzzle15 *head = NULL;

void guideTable() {

    printf("+-------+-------+-------+-------+\n");
    printf("|       |       |       |       |\n");
    printf("|   a   |   b   |   c   |   d   |\n");
    printf("|       |       |       |       |\n");
    printf("+-------+-------+-------+-------+\n");
    printf("|       |       |       |       |\n");
    printf("|   e   |   f   |   g   |   h   |\n");
    printf("|       |       |       |       |\n");
    printf("+-------+-------+-------+-------+\n");
    printf("|       |       |       |       |\n");
    printf("|   i   |   j   |   k   |   l   |\n");
    printf("|       |       |       |       |\n");
    printf("+-------+-------+-------+-------+\n");
    printf("|       |       |       |       |\n");
    printf("|   m   |   n   |   o   |   p   |\n");
    printf("|       |       |       |       |\n");
    printf("+-------+-------+-------+-------+\n");

}

void getUserInput() {

    char getTable[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'};
    int theTable[16];
    int i = 0;

    printf("[] Type \"BLANK\" if the table will be blank.\n");
    
    for(i = 0; i < 16; i++) {

        printf("%c = ", getTable[i]);
        scanf("%d", &theTable[i]);

    }

}

void main() {

    guideTable();
    getUserInput();
    
}