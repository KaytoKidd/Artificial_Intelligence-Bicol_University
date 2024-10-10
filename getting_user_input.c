/*
    Purpose:
    - Get User Input
    
    Approach:
    1. Get User Input
    2. All User Input is inserted to an Array.
    3. After User Input is finished, the Array can be used for other LinkedList.
        3.1. User_Input Array -> IDS LinkedList
        3.2. User_Input Array -> A* LinkedList

    UserInput -> Array -> LinkedList
*/

#include <stdio.h>
#include <stdlib.h>

void guideTable();
void input_based_15PuzzleTable(char user_input[]);
void getUserInput();
void printUserInput(char user_input[]);
void print15PuzzleTable();

struct IDS_List {
    int data;
    struct IDS_List *next;
};

struct AStar_List {
    int data;
    struct AStar_List *next;
};

struct IDS_List *ids_head = NULL;
struct AStar_List *astar_head = NULL;

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

void input_based_15PuzzleTable(char user_input[]) {

    printf("+-------+-------+-------+-------+\n");
    printf("|       |       |       |       |\n");
    printf("|   %c   |   %c   |   %c   |   %c   |\n", user_input[0], user_input[1], user_input[2], user_input[3]);
    printf("|       |       |       |       |\n");
    printf("+-------+-------+-------+-------+\n");
    printf("|       |       |       |       |\n");
    printf("|   %c   |   %c   |   %c   |   %c   |\n", user_input[4], user_input[5], user_input[6], user_input[7]);
    printf("|       |       |       |       |\n");
    printf("+-------+-------+-------+-------+\n");
    printf("|       |       |       |       |\n");
    printf("|   %c   |   %c   |   %c   |   %c   |\n", user_input[8], user_input[9], user_input[10], user_input[11]);
    printf("|       |       |       |       |\n");
    printf("+-------+-------+-------+-------+\n");
    printf("|       |       |       |       |\n");
    printf("|   %c   |   %c   |   %c   |   %c   |\n", user_input[12], user_input[13], user_input[14], user_input[15]);
    printf("|       |       |       |       |\n");
    printf("+-------+-------+-------+-------+\n");
    
}

void getUserInput() {

    /*
        rowcol_guide[] = {}
        - Only a guide for the user
        - To lessen print statements.
        - Please create a new design for this one, e.g. typing exactly at the boxes (if possible)

        user_input[16]
        - Is set to "char" since we have an " " (empty) character to input.
        - When passed to LinkedList, will cast nalang to int.
    */

    char rowcol_guide[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'};
    char user_input[16];
    int i = 0;

    /*
        - Sample prompt, please create a new design.
        - Needs to add restriction that once a blank is inserted, no more blank should be accepted.
        - 15 non-blank inputs
        - 1 blank input
    */
    printf("[] Type \"B\" if the table will be blank.\n");
    
    // Loop for getting User Input, passed to user_input[16] array.
    for(i = 0; i < 16; i++) {

        char input;

        printf("%c = ", rowcol_guide[i]);
        scanf(" %c", &input);

        if (input == 'B')
            user_input[i] = ' ';
        else
            user_input[i] = input;

    }
    printf("\n[] Input, !inside table.\n");
    printUserInput(user_input);
    printf("\n[] Input, inside the table.\n");
    input_based_15PuzzleTable(user_input);

}

void printUserInput(char user_input[]) {

    int i = 0;
    // int arr_size = sizeof(user_input) / sizeof(user_input[0]);
    // if yung code above mag work, ganito sana: for(i = 0; i < arr_size; i++)

    for(i = 0; i < 16; i++) {
        printf("%c\t", user_input[i]);
        if ((i + 1) % 4 == 0)
            printf("\n");
    }

}

void main() {

    guideTable();
    getUserInput();
    
}

/*
    TODO:
    [1] Transfer Array -> LinkedList
    [2] Optimize Code
    [3] Add Comments/Documentation
*/