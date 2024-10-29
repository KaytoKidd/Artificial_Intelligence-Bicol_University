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

struct SolutionPathLL {
    int movement;
    struct SolutionPathLL *next;
};

struct ExpandedLL *expandedLL_head = NULL;
struct FringeLL *fringeLL_head = NULL;
struct SolutionPathLL *solutionPathLL_head = NULL;

// GLOBAL DECLARATIONS (Array, Variables, etc.)
struct SolutionPathLL *solutionPath_arr[4];    // Where the solution path will be inserted.
/*  DOCUMENTATION FOR solutionPath_arr[4]
    How will it work?
        - Each index of the solutionPath_arr will contain the head of the LinkedList.
        - Example: 
            solutionPath_arr[0] = #00001 (the address of the first node in the LinkedList)
            solutionPath_arr[0] = #00002 (the address of the second node in the LinkedList)
            and so on.
    What are these four(4)?
        - These are the CHILD of the ROOT.
        - Meaning, they are the nodes found after expanding LEVEL 0.
        - Hence, they are the nodes found at LEVEL 1.
    Will it work?
        - Yes, because the only parent node will always be the four(4) even if drawn in a paper.
        - The ULTIMATE PARENT is the ROOT (LEVEL 0), but the second ULTIMATE PARENT is LEVEL 1.
    How will it work? (Cont.)
        - The hierarchy of the nodes is set to UP -> DOWN -> LEFT -> RIGHT.
        - Where: Node1 = UP, Node2 = DOWN, Node3 = LEFT, node4 = RIGHT
        - If ULTIMATE PARENT (LEVEL 0) is expanded and found CHILDREN is only 2-3, then empty node will have value of 0.
*/

// board_guide(), get_user_input(), and print_user_input() are all for user interaction only.
// However, user_input[] will be used for the entire program.

// User Interaction Functions - Declaration
void board_guide();
void get_user_input(char board_guide_label[]);
void print_user_input(int user_input[]);

// Calculation Functions - Declaration
void heirarchy_of_movements();

// Inserting Array to LinkedList
void insert_to_FringeLL(int the_level, int the_arr[16]);
void print_FringeLL(); // Debugging purposes, DELETE LATER.
void find_which_to_expand();
void expand_this(int deepestNode_index);
void start_expanding(int the_arr[16]);

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
    insert_to_FringeLL(0, user_input); // First/Initial value of Fringe. Level = 0 (ROOT)

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

// COMPUTATION START - IDS
void insert_to_FringeLL(int the_level, int the_arr[16]) {

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

    print_FringeLL(); // Debugging purposes, DELETE LATER.

}

void print_FringeLL() { // Debugging purposes, DELETE LATER.

    struct FringeLL *printer = fringeLL_head;
    int i = 0;

    while (printer != NULL) {
        printf("Level [%d] = ", printer -> level);
        for (i = 0; i < 16; i++) {
            printf("%d ", printer -> fringe_arr[i]);
        }
        printf("\n");
        printer = printer -> next;
    }

}

void find_which_to_expand() {

    struct FringeLL *finder = fringeLL_head;
    int deepestNode_index = 0;
    
    if (finder -> next == NULL) {   // The FringeLL contains only one(1) node. Level 0, the ROOT.
        deepestNode_index = 0;
    } else {                        // The FringeLL contains more than one(1) node(s). Level 1, 2, 3, ...
        finder = fringeLL_head;
        while(finder != NULL) {
            if (deepestNode_index < finder -> level) {
                deepestNode_index = finder -> level;
            }
            finder = finder -> next;
        }
    }

    expand_this(deepestNode_index);

}

void expand_this(int deepestNode_index) {

    struct FringeLL *finder = fringeLL_head;
    int index_of_negativeOne = 0;
    int i = 0;
    int to_expand_arr[16];
    int movements_index_arr[4]; // There are 4 maximum possible movements (UP, DOWN, LEFT, RIGHT).
                                // Empty values will be set to 0 if there is only 1-3 movements found.

    while(finder != NULL) {
        if (finder -> level == deepestNode_index)   // finder has now the address of the node to expand.
            break;
        finder = finder -> next;
    }

    for (i = 0; i < 16; i++) {              // Get the index of -1 in the array of the node to be expanded.
        if (finder -> fringe_arr[i] == -1) {
            index_of_negativeOne = i;       // We found the index of -1 in the array of the node to be expanded.
            break;
        }
    }

    for (i = 0; i < 16; i++) {              // Much easier to expand an ARRAY than a LINKEDLIST.
        to_expand_arr[i] = finder -> fringe_arr[i];
    }

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

    int x = index_of_negativeOne - 1;   // depth/level  - Will be used once.  (FORMULA: x = index_of_negativeOne - 1)
    int y = 1;                          // row          - Will be used once.  (VALUE = FIXED)
    int z = 0;                          // column       - One to be iterated. (VALUE = Changing)

    for(z = 0; z < 4; z++){ 
        movements_index_arr[z] = movements[z];
        // solutionPath_arr[z] = movements[z];     // Level 1 nodes are created. HEPL
    }

}

void start_expanding(int the_arr[16]) {

}

void main() {
    board_guide();
}