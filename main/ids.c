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

// GLOBAL DECLARATIONS (Array, Variables, etc.) [START]
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
int what_level = 0;

int goal_state[16] = {
    -1, 1, 2, 3,
    4, 5, 6, 7,
    8, 9, 10, 11,
    12, 13, 14, 15
};
// GLOBAL DECLARATIONS (Array, Variables, etc.) [END]

// board_guide(), get_user_input(), and print_user_input() are all for user interaction only.
// However, user_input[] will be used for the entire program.

// User Interaction Functions - Declaration
void board_guide();
void get_user_input(char board_guide_label[]);
void print_user_input(int user_input[]);

// Inserting Array to LinkedList
void insert_to_FringeLL(int the_level, int the_arr[16]);
void print_FringeLL(); // Debugging purposes, DELETE LATER.
void find_which_to_expand();
void expand_this(int deepestNode_index);
void start_expanding(int the_arr[16], int the_movements[4], int the_movements_label[4], int index_of_negativeOne);
int check_ifAlready_inExpandedLL(int the_arr[16]);
int find_deepestNode_inFringe();
int check_if_goalState(int the_arr[16], int the_goal_state[16]);

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
    insert_to_FringeLL(what_level, user_input); // First/Initial value of Fringe. Level = 0 (ROOT)

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

// COMPUTATION START - IDS
// This is only used once. That is, from the very start when the program is run.
// Might be useful if this is the function for inserting to fringe, and not in start_expanding().

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
    int deepestNode_level = 0;
    
    if (finder -> next == NULL) {   // The FringeLL contains only one(1) node. Level 0, the ROOT.
        deepestNode_level = 0;
    } else {                        // The FringeLL contains more than one(1) node(s). Level 1, 2, 3, ...
        finder = fringeLL_head;
        while(finder != NULL) {
            if (deepestNode_level < finder -> level) {  // Finding the deepest level.
                deepestNode_level = finder -> level;    // Found the deepest level.
            }
            finder = finder -> next;
        }
    }

    expand_this(deepestNode_level);

}

void expand_this(int deepestNode_level) {

    struct FringeLL *finder = fringeLL_head;
    int index_of_negativeOne = 0;
    int i = 0;
    int to_expand_arr[16];
    int movements_index_arr[4]; // There are 4 maximum possible movements (UP, DOWN, LEFT, RIGHT).
                                // Empty values will be set to 0 if there is only 1-3 movements found.
                                // VALUE = FOUND at the second row, y = 1
    int movements_label_arr[4]; // Label of what movement it will be.
                                // VALUE = FOUND at the third row, y = 2

    while(finder != NULL) {
        if (finder -> level == deepestNode_level)   // finder has now the address of the node to expand.
            break;                                  // The very first node found to have that level is to be expanded.
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

    // Hierarchy of Priority: UP -> DOWN -> LEFT -> RIGHT
    // UP       - 96
    // DOWN     - 97
    // LEFT     - 98
    // RIGHT    - 99

    int movements[16][3][4] = {
        {{1}, {5, 2}, {96, 99}},                    // 0
        {{2}, {6, 1, 3}, {97, 98, 99}},             // 1
        {{3}, {7, 2, 40}, {97, 98, 99}},            // 2
        {{4}, {8, 3}, {97, 98}},                    // 3
        {{5}, {1, 9, 6}, {96, 97, 99}},             // 4
        {{6}, {2, 10, 5, 7}, {96, 97, 98, 99}},     // 5
        {{7}, {3, 11, 6, 8}, {96, 97, 98, 99}},     // 6
        {{8}, {4, 12, 7}, {96, 97, 98}},            // 7
        {{9}, {5, 13, 10}, {96, 97, 99}},           // 8
        {{10}, {6, 14, 9, 11}, {96, 97, 98, 99}},   // 9
        {{11}, {7, 15, 10, 12}, {96, 97, 98, 99}},  // 10
        {{12}, {8, 16, 11}, {96, 97, 98}},          // 11
        {{13}, {9, 14}, {96, 99}},                  // 12
        {{14}, {10, 13, 15}, {96, 98, 99}},         // 13
        {{15}, {11, 14, 16}, {96, 98, 99}},         // 14
        {{16}, {12, 15}, {96, 98}}                  // 15
    };

    int x = index_of_negativeOne - 1;   // depth/level  - Will be used once.  (FORMULA: x = index_of_negativeOne - 1)
    int y = 1;                          // row          - Will be used once.  (VALUE = FIXED)
    int z = 0;                          // column       - One to be iterated. (VALUE = Changing)

    for(z = 0; z < 4; z++){ 
        movements_index_arr[z] = movements[x][y][z];        // Example: 3,11,6,8
        movements_label_arr[z] = movements[x][y + 1][z];    // Example: 96,97,98,99
    }

    start_expanding(to_expand_arr, movements_index_arr, movements_label_arr, index_of_negativeOne);

}

void start_expanding(int the_arr[16], int the_movements[4], int the_movements_label[4], int index_of_negativeOne) {

    /*
        NOTE:   There are two(2) times where we have to check whether to process the following
                algorithms/code.
                - Add to EXPANDED LinkedList.
                - Delete from FRINGE LinkedList the array to be expanded.
                - Insert to FRINGE LinkedList the children of the_arr[16] (passed in this function).

        TO CHECK:
                1. Check the array passed exactly at this function, that is 'the_arr[16]'.
                    - That is, check before starting this function, whether the_arr[16] that
                    is passed within thin function already exists in the 'ExpandedLL'.
                2. Check the arrays (child) when the_arr[16] is modified and expanded.
                    - This means that the function passed within this function start_expanding
                    was not found in the 'ExpandedLL' and is continued to be expanded.
                    - Hence, it will produce its children.
                    - Its children should be checked one by one, whether each already exists
                    in the 'ExpandedLL'.
                    - If the child already exists, then DO NOT ADD.
                    - If the child does not exist, then ADD.
    */

    if (check_ifAlready_inExpandedLL(the_arr) == 1) {   // Continue to add.

        // ADDING - Add to EXPANDED LinkedList. [START]
        struct ExpandedLL *expanded_new_node = (struct ExpandedLL *)malloc(sizeof(struct ExpandedLL));
        struct ExpandedLL *expanded_iterator = expandedLL_head;
        int z = 0;
        what_level = what_level + 1;

        if(expandedLL_head == NULL) {
            expandedLL_head = expanded_new_node;
        } else {
            expanded_iterator = expandedLL_head;
            while(expanded_iterator -> next != NULL) {
                expanded_iterator = expanded_iterator -> next;
            }
            expanded_iterator -> next = expanded_new_node;
        }

        for(z = 0; z < 16; z++) {
            expanded_new_node -> expanded_arr[z] = the_arr[z];
        }
        expanded_new_node -> next = NULL;
        // ADDING - Add to EXPANDED LinkedList. [END]

        // DELETING - Free the node from the FRINGE LinkedList. [START]
        struct FringeLL *fringe_iterator = fringeLL_head;
        struct FringeLL *fringe_addressBefore_free = fringeLL_head;
        struct FringeLL *fringe_adddressTo_free;

        if(fringeLL_head -> next == NULL) { // Means there is only one node, the ROOT (LEVEL 0).

            fringe_adddressTo_free = fringeLL_head;
            fringeLL_head = NULL;
            free(fringe_adddressTo_free);

        } else {                            // We need to search first where is the node to be deleted.

            fringe_iterator = fringeLL_head;
            while(fringe_iterator != NULL) {
                    
                int x = 0;
                int total = 0;
                for(x = 0; x < 16; x++) {   // Loop will automatically end in 16 iterations.
                    if(fringe_iterator -> fringe_arr[x] == the_arr[x])
                        total++;            // Will have a maximum value of 16.
                    else
                        break;  // Means that the current array of the current node in the fringe is not what we want.
                if(total == 16) // Means that all value of the array from this address equals the one to be expanded.
                    break;      // [1] Hence, we have found the address of the node in the fringe to delete.
                }

                fringe_addressBefore_free = fringe_iterator;    // If [1] is processed, this will not anymore run.
                fringe_iterator = fringe_iterator -> next;      // If [1] is processed, this will not anymore run.
            }

            fringe_addressBefore_free -> next = fringe_iterator -> next;
            fringe_adddressTo_free = fringe_iterator;
            free(fringe_adddressTo_free);
            // DELETING - Free the node from the FRINGE LinkedList. [END]

        }

        if(check_if_goalState(the_arr, goal_state) == 1) { // Check whether already the goal state.
            // end program.
            // return solution path and requirements needed by madam.
        } else {
            // EXPANSION/ADDING - Add to FRINGE LinkedList. [START]
            int the_movement = 1;
            int i = 0;

            // Get first total of non zero values in the_movements[4].
            int a = 0;
            int total_of_nonzero = 0;
            int total_of_nonzero_checker = 0;

            for(a = 0; a < 4; a++) {
                if (the_movements[a] != 0) {
                    total_of_nonzero++;
                }
            }

            while(the_movement != 0 || i != 4) {    // i == 3 to stop the loop if movements total is 4.

                /*
                - Since we already know the index of negative one using index_of_negativeOne, we can use
                this to exchange with the values of the_movement per iteration 'i' found at the_movements[i].

                LOGIC:
                - Per iteration, we can exchange the index of index_of_negativeOne with the_movement (which has value of
                the_movements[i]) and a new array is formed.
                - Note that the_arr[16] which is passed on the argument should not be changed value as it will be used
                throughout this function.
                - TODO:
                    1. Create a new array (new_arr[16]), where this array is passed the value of the_arr[16].
                    2. new_arr[16] will then be the one manipulated (exchange of index of -1 with the_movement).
                    3. Once index is exchanged, pass new_arr[16] to FRINGE using struct malloc.
                    4. LOOP '1.' until the_movement != 0 or i == 3 is true.
                */

                struct FringeLL *fringe_new_node = (struct FringeLL *)malloc(sizeof(struct FringeLL));
                struct FringeLL *fringe_new_iterator = fringeLL_head;
                int new_arr[16];
                int p = 0;
                int temp = 0;

                // Pass value of the_arr to new_arr.
                for(p = 0; p < 16; p++) {
                    new_arr[p] = the_arr[p];
                }

                // Exchange value.
                the_movement = the_movements[i];                        // the_movement = 3
                temp = new_arr[index_of_negativeOne];                   // temp         = new_arr[7]
                new_arr[index_of_negativeOne] = new_arr[the_movement];  // new_arr[7]   = new_arr[3]
                new_arr[the_movement] = temp;                           // new_arr[3]   = temp
                // Now, the index has been exchanged.
                // new_arr is the array to be inserted to the FRINGE LinkedList.

                if (check_ifAlready_inExpandedLL(new_arr) == 1) {

                    // Insert to FRINGE LinkedList.
                    if(fringeLL_head == NULL) {
                        fringeLL_head = fringe_new_node;
                    } else {
                        fringe_new_iterator = fringeLL_head;
                        while(fringe_new_iterator -> next != NULL) {
                            fringe_new_iterator = fringe_new_iterator -> next;
                        }
                        fringe_new_iterator -> next = fringe_new_node;
                    }

                    fringe_new_node -> level = what_level;
                    for(p = 0; p < 16; p++) {
                        fringe_new_node -> fringe_arr[p] = new_arr[p];
                    }
                    fringe_new_node -> next = NULL;

                } else {
                    total_of_nonzero_checker++;
                    // This variable is used to count whether all cannot anymore be expanded.
                    // Hence, we can say that the parent does not anymore have a child.
                    // Therefore, we can set what_level to the highest level found within the fringe.
                }

                i++;
            }

            if(total_of_nonzero == total_of_nonzero_checker) {
                // It means that there is no node expanded.
                // what_level = the next highest level in the FRINGE_LL.
                what_level = find_deepestNode_inFringe();
            }
            // EXPANSION/ADDING - Add to FRINGE LinkedList. [END]

            // ADDING - Add to SOLUTIONPATH LinkedList. [START]
            struct SolutionPathLL *new_node = (struct SolutionPathLL *)malloc(sizeof(struct SolutionPathLL));

            // ADDING - Add to SOLUTIONPATH LinkedList. [END]
        }

    } else {
        what_level = find_deepestNode_inFringe();
    } // Else, do not add.

}

int check_ifAlready_inExpandedLL(int the_arr[16]) {

    struct ExpandedLL *researcher = expandedLL_head;
    int i = 0;
    int cont = 1;

    while(researcher != NULL) {

        int total = 0;
        // If total == 16, then that the_arr must not be inserted to FRINGE LL.
        // Else, insert to FRINGE LL.
        
        for(i = 0; i < 16; i++) {
            if(researcher -> expanded_arr[i] == the_arr[i])
                total++;
            else
                break;
        }

        if(total == 16) {
            cont = 0;
            break;
        }
        researcher = researcher -> next;

    }

    return cont;    // cont == 0, do not add to fringe. cont == 1, add to fringe.

}

int find_deepestNode_inFringe() {
    struct FringeLL *finder = fringeLL_head;
    int deepest_node = 0;

    while(finder != NULL) {
        if(deepest_node < finder -> level)
            deepest_node = finder -> level;
        finder = finder -> next;
    }

    return deepest_node;
}

int check_if_goalState(int the_arr[16], int the_goal_state[16]) {

    int i = 0;
    int total_count = 0;
    int is_the_GOALSTATE = 0;

    for(i = 0; i < 16; i++) {
        if(the_arr[i] == the_goal_state[i])
            total_count++;  // Max value is 16.
        else
            break;          // Means that the_arr[i] is not the goal state.
    }
    
    if(total_count == 16)
        is_the_GOALSTATE = 1;   // 1 = true, means that each value per index satisfies the goal state.
    
    return is_the_GOALSTATE;    // 0 = false, 1 = true

}

void main() {
    board_guide();
}

/*  SPRINT BACKLOG - Week 2
    [DONE] 1. Create an algorithm for level issue in FringeLL.
        1.1.    It should not be fringe_new_node -> level = what_level; Where what_level is global.
        Algorithm formed:
            1.  Have an another index (new_index_checker) and check whether this index is equal to the current index.
                - This new_index_checker is set the value of 0 whenever the condition "cannot anymore be expanded" is true.
                - This means that new_index_checker is not set the value of 0 whenever the expanded not is not true to the condition above.
                - This means that there will be no more children for the current level being expanded, and hence set the value of 0.
    [DONE] 2. Create an algorithm for checking whether a certain node cannot anymore be expanded.
            - This is where the SPRINT '1' is used.
    [DONE] 3. Create an algorithm to check whether the node to be expanded is already the GOAL state.
    
    4. Create an algorithm/logic on what to do when expanded node is the GOAL state.
    5. Create an algorithm to store the solution path.
*/