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

struct SolutionPathLL {

    int movement;
    struct SolutionPathLL *next;

};

struct ExpandedLL *expandedLL_head = NULL;
struct FringeLL *fringeLL_head = NULL;
struct SolutionPathLL *solutionPathLL_head[4];

// Global Variables - Declaration
int user_input_arr[16];
int goal_state_arr[] = {
    -1, 1, 2, 3,
    4, 5, 6, 7,
    8, 9, 10, 11,
    12, 13, 14, 15
};
int goal_state_found = 0;

// Global Variables - Declaration (Used for find_which_to_expand())
int to_expand_arr[16];
int to_expand_arr_level = 0;
int index_of_negative_one = 0;
int iteration_level = 0;
int fringe_is_empty = 0;

// Global Variables - Declaration (Used for Solution Path)
int initial_solutionpath_insertion = 1;  // 1 = true, 0 = false
int which_solutionPath_head = 0;

// User Input - Declaration
void board_guide();
void get_user_input();
void print_userInput_in_boardGuide(int user_input[16]);

// Fringe - Declaration
void insert_to_FringeLL(int to_insert_level, int to_insert_arr[16]);
void remove_from_FringeLL(int to_remove_arr[16]);
void print_the_FringeLL();

// Expanded - Declaration
void insert_to_ExpandedLL(int to_insert_arr[16]);
int check_if_already_in_ExpandedLL(int to_check_arr[16]);

// IDS Computation - Declaration
void start_IDS();
int check_if_possible_to_expand();
void check_whether_GoalState(int to_check_arr[16]);
void free_FringeLL_ExpandedLL_SolutionPathLL();
void find_which_to_expand();
void start_IDS_Expansion();
void levelRestarted_restartAllGlobalVariable();

// Solution Path - Declaration
void insert_to_SolutionPathLL(int to_insert_movement);
void remove_from_SolutionPathLL();

// IDS Computation (When Goal is Found) - Declaration
void todo_when_IDSGoalState_found();
int count_total_nodes_in_ExpandedLL();
void get_the_solution_path_to_goal();

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
    int i = 0;

    for(i = 0; i < 16; i++) {

        printf("[%c] = ", board_guide_label[i]);
        scanf("%d", &user_input_arr[i]);

    }

    print_userInput_in_boardGuide(user_input_arr);
    // insert_to_FringeLL(0, user_input_arr);  // 0 = Level 0, ROOT.

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

void remove_from_FringeLL(int to_remove_arr[16]) {

    struct FringeLL *connector = fringeLL_head;
    struct FringeLL *deleter = fringeLL_head;
    int in_the_beginning = 0;

    while(deleter != NULL) {

        int all_the_same = 0;
        int i = 0;

        for(i = 0; i < 16; i++) {
            if(deleter -> fringeLL_arr[i] == to_remove_arr[i])
                all_the_same++; // If all_the_same == 16, means array is same as to_remove_arr[16].
            else
                break;          // Current array is not the same with to_remove_arr[16]
        }

        if(all_the_same == 16)  // We want to end, so that 'deleter' will have the address of what to delete.
            break;

        in_the_beginning++;
        connector = deleter;
        deleter = deleter -> next;

    }

    if(in_the_beginning == 0)
        fringeLL_head = fringeLL_head -> next;
    else
        connector -> next = deleter -> next;

    free(deleter);

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

// Expanded - Definition
void insert_to_ExpandedLL(int to_insert_arr[16]) {

    struct ExpandedLL *new_node = (struct ExpandedLL *)malloc(sizeof(struct ExpandedLL));
    struct ExpandedLL *iterator = expandedLL_head;
    int i = 0;

    if(expandedLL_head == NULL) {
        expandedLL_head = new_node;
    } else {
        iterator = expandedLL_head;
        while(iterator -> next != NULL) {
            iterator = iterator -> next;
        }
        iterator -> next = new_node;
    }

    for(i = 0; i < 16; i++) {
        new_node -> expandedLL_arr[i] = to_insert_arr[i];
    }
    new_node -> next = NULL;

}

int check_if_already_in_ExpandedLL(int to_check_arr[16]) {

    struct ExpandedLL *checker = expandedLL_head;
    int already_in_expanded = 0;    // 0 = false, 1 = true
    int total_counter = 0;
    int i = 0;

    while(checker != NULL) {

        for(i = 0; i < 16; i++){
            if(to_check_arr[i] == checker -> expandedLL_arr[i])
                total_counter++;
            else
                break;
        }
        checker = checker -> next;

        if(total_counter == 16) {
            already_in_expanded = 1;
            break;
        }

    }

    return already_in_expanded;

}

// IDS Computation - Definition
void start_IDS() {

    perform_this:
    remove_from_FringeLL(to_expand_arr);
    insert_to_ExpandedLL(to_expand_arr);
    check_whether_GoalState(to_expand_arr);

    if(goal_state_found == 1) {

        todo_when_IDSGoalState_found();

    } else {

        if(check_if_possible_to_expand() == 1) {    // Possible to expand
            
            start_IDS_Expansion();
            find_which_to_expand();
            goto perform_this;

        } else {    // Not possible to expand.

            if(iteration_level >= 1)
                remove_from_SolutionPathLL();

            find_which_to_expand();
            if(fringe_is_empty == 0) // Fringe is not empty. We will continue
                goto perform_this;
        }

    }

}

int check_if_possible_to_expand() {

    int possible_to_expand = 0; // 0 = false, 1 = true

    if(to_expand_arr_level == iteration_level)
        possible_to_expand = 0; // NO, not possible to expand.
    else
        possible_to_expand = 1; // YES, possible to expand.

    return possible_to_expand;

}

void check_whether_GoalState(int to_check_arr[16]) {

    int i = 0;
    int is_goal_state = 0;
    
    for(i = 0; i < 16; i++) {

        if(to_check_arr[i] == goal_state_arr[i])
            is_goal_state++;
        else
            break;

    }

    if(is_goal_state == 16)
        goal_state_found = 1;

}

void free_FringeLL_ExpandedLL_SolutionPathLL() {

    // The purpose of this function is to delete the entire Fringe and Expanded LinkedList.
    // This is done per iteration level, following IDS rules on iteration.

    // ExpandedLL
    struct ExpandedLL *expandedLL_freer = expandedLL_head;

    while(expandedLL_head != NULL) {
        expandedLL_freer = expandedLL_head;
        expandedLL_head = expandedLL_head -> next;
        free(expandedLL_freer);
    }

    expandedLL_head = NULL;

    // FringeLL
    struct FringeLL *fringeLL_freer = fringeLL_head;

    while(fringeLL_head != NULL) {
        fringeLL_freer = fringeLL_head;
        fringeLL_head = fringeLL_head -> next;
        free(fringeLL_freer);
    }

    fringeLL_head = NULL;

    // SolutionPathLL
    int i = 0;
    for(i = 0; i < 4; i++) {
        struct SolutionPathLL *solutionPathLL_freer = solutionPathLL_head[i];
        
        while(solutionPathLL_head[i] != NULL) {
            solutionPathLL_freer = solutionPathLL_head[i];
            solutionPathLL_head[i] = solutionPathLL_head[i] -> next;
            free(solutionPathLL_freer);
        }
    }

}

void find_which_to_expand() {

    struct FringeLL *finder = fringeLL_head;
    int deepest_node = 0;
    int i = 0;

    // Condition - For when the fringe is now empty.
    if(fringeLL_head == NULL) {

        // The fringe is empty, nothing anymore to expand.
        // This happens when on the certain level, the goal state is not found.
        fringe_is_empty = 1;    // True, fringe is empty.
    
    } else {

        // Getting the deepest level from the FringeLL.
        finder = fringeLL_head;
        while(finder != NULL) {
            if(deepest_node < finder -> level)
                deepest_node = finder -> level;
            finder = finder -> next;
        }

        // Finding which array from the FringeLL is to be expanded.
        finder = fringeLL_head;
        while(finder != NULL) {
            if(finder -> level == deepest_node)
                break;  // Now, 'finder' will have the address of the node/array that we want to expand.
            finder = finder -> next;
        }

        // Inserting the level of the to_expand_arr[16] to the global variable to_expand_arr_level.
        to_expand_arr_level = finder -> level;

        // Inserting array from FringeLL to the global array to_expand_arr[16].
        for(i = 0; i < 16; i++) {
            to_expand_arr[i] = finder -> fringeLL_arr[i];
        }

        // Finding the index of negative one(-1) in the array to be expanded.
        for(i = 0; i < 16; i++) {
            if(to_expand_arr[i] == -1) {
                index_of_negative_one = i;
                break;
            }
        }
        

    }

}

void start_IDS_Expansion() {

    // Hierarchy of Priority: UP -> DOWN -> LEFT -> RIGHT
    // UP       - 96
    // DOWN     - 97
    // LEFT     - 98
    // RIGHT    - 99
    int movements_index_arr[4];
    int movements_label_arr[4];

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

    int x = index_of_negative_one;
    int y = 1;
    int z = 0;

    for(z = 0; z < 4; z++){ 
        movements_index_arr[z] = movements[x][y][z];        // Example: 3,11,6,8
        movements_label_arr[z] = movements[x][y + 1][z];    // Example: 96,97,98,99
    }

    /*  EXCHANGING INDEX
        Process:
            1. Copy to_expand_arr to temp_expand_arr.
                - This is to not change the value of to_expand_arr, since
                  it may be used again for other movements later.
                - This is because to_expand_arr is the parent, and the
                  children depends on the parent.
    */

    int i = 0;

    // Exchange Index
    i = 0;
    while(movements_index_arr[i] != 0 || i != 4) {

        // Copy to_expand_arr to temp_expand_arr.
        int temp_expand_arr[16];
        int j = 0;

        for(j = 0; j < 16; j++) {
            temp_expand_arr[j] = to_expand_arr[j];
        }

        int temp = temp_expand_arr[index_of_negative_one];
        temp_expand_arr[index_of_negative_one] = temp_expand_arr[movements_index_arr[i]];
        temp_expand_arr[movements_index_arr[i]] = temp;

        if(check_if_already_in_ExpandedLL(temp_expand_arr) == 0) {  // Not yet in the ExpandedLL.

            insert_to_FringeLL(to_expand_arr_level + 1, temp_expand_arr);

        }

        if(initial_solutionpath_insertion == 0) {

            insert_to_SolutionPathLL(movements_label_arr[i]);

        }

        i++;

    }

    // Solution Path
    i = 0;
    if(initial_solutionpath_insertion == 1 && iteration_level >= 1) {   // True, it is the initial insertion of solution path.

        while(movements_label_arr[i] != 0 || i != 4) {

            struct SolutionPathLL *new_node = (struct SolutionPathLL *)malloc(sizeof(struct SolutionPathLL));
            struct SolutionPathLL *iterator;

            if(solutionPathLL_head[i] == NULL) {
                solutionPathLL_head[i] = new_node;
            } else {
                iterator = solutionPathLL_head[i];
                while(iterator -> next != NULL) {
                    iterator = iterator -> next;
                }
                iterator -> next = new_node;
            }

            new_node -> movement = movements_label_arr[i];
            new_node -> next = NULL;
            
        }

        initial_solutionpath_insertion = 0;
        // Once the above code is done, this will not anymore be accessed until the end.
        // However, once per level on the while loop on main() is processed, this will be processed once again.
        // Note: This only works if Level is >= 1.
        // Note: When Level 0, it will not do anything.

    }

}

void levelRestarted_restartAllGlobalVariable() {

    goal_state_found = 0;

    // to_expand_arr[16];
    int i = 0;
    for(i = 0; i < 16; i++) {
        to_expand_arr[i] = 0;
    }

    to_expand_arr_level = 0;
    index_of_negative_one = 0;
    fringe_is_empty = 0;

    initial_solutionpath_insertion = 1;
    which_solutionPath_head = 0;

}

// Solution Path - Definition
void insert_to_SolutionPathLL(int to_insert_movement) {

    struct SolutionPathLL *new_node = (struct SolutionPathLL *)malloc(sizeof(struct SolutionPathLL));
    struct SolutionPathLL *iterator;

    iterator = solutionPathLL_head[which_solutionPath_head];
    while(iterator -> next != NULL) {
        iterator = iterator -> next;
    }
    iterator -> next = new_node;

    new_node -> movement = to_insert_movement;
    new_node -> next = NULL;

}

void remove_from_SolutionPathLL() {

    struct SolutionPathLL *deleter = solutionPathLL_head[which_solutionPath_head];
    struct SolutionPathLL *connector;

    if(solutionPathLL_head[which_solutionPath_head] -> next == NULL) {  // Only one left node.
        solutionPathLL_head[which_solutionPath_head] = NULL;
        which_solutionPath_head++;
    } else {    // >= 2 number of nodes.
        while(deleter -> next != NULL) {
            connector = deleter;
            deleter = deleter -> next;
        }
        connector -> next = NULL;
    }
    free(deleter);

}

// IDS Computation (When Goal is Found) - Definition
void todo_when_IDSGoalState_found() {

    /*
        Insert the code below for when the Goal State is achieved.
    
        Process:
            1. Show Solution Path
                - Must show the movement label.
                - Example: UP -> DOWN -> DOWN -> RIGHT -> ...
            2. Show Solution Cost
                - The number of moves required to reach the goal state.
            3. Show Search Cost
                - This is the number of nodes expanded before finding the solution.
                - The answer for this is the total count of nodes in the ExpandedLL.
            4. Show Running Time
                - Help.
    */

    printf("[SOLUTION PATH] = \n");
    get_the_solution_path_to_goal();

    printf("[SOLUTION COST] = \n");

    int solution_search_cost = count_total_nodes_in_ExpandedLL();
    printf("[SOLUTION SEARCH COST] = %d\n", solution_search_cost);
    
    printf("[RUNNING TIME] = \n");

}

int count_total_nodes_in_ExpandedLL() {

    struct ExpandedLL *total_counter = expandedLL_head;
    int total_count = 0;

    while(total_counter != NULL) {
        total_count++;
        total_counter = total_counter -> next;
    }

    return total_count;

}

void get_the_solution_path_to_goal() {

    struct SolutionPathLL *printer = solutionPathLL_head[which_solutionPath_head];
    int found_movement = 0;

    while(printer != NULL) {

        found_movement = printer -> movement;

        switch(found_movement) {
            case 96:
                printf("UP");
                break;
            case 97:
                printf("DOWN");
                break;
            case 98:
                printf("LEFT");
                break;
            case 99:
                printf("RIGHT");
                break;
        }

        if(printer -> next != NULL)
            printf(" -> ");

        printer = printer -> next;
    }

    printf("\n");

}

void main() {

    board_guide();      // Show Guide Table
    get_user_input();   // Get User Input

    // Start IDS Algorithm
    while(goal_state_found == 0) {  // 0 = false (not found, continue), 1 = true (found, end program)
        start_IDS();

        if(goal_state_found == 1)
            break;

        free_FringeLL_ExpandedLL_SolutionPathLL();
        levelRestarted_restartAllGlobalVariable();
        iteration_level++;
    }
    
}