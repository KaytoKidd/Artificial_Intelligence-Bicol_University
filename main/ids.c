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

// Global Variables - Declaration
int user_input_arr[16];
int goal_state_arr[] = {
    -1, 1, 2, 3,
    4, 5, 6, 7,
    8, 9, 10, 11,
    12, 13, 14, 15
};
int goal_state_found = 0;

// User Input - Declaration
void board_guide();
void get_user_input();
void print_userInput_in_boardGuide(int user_input[16]);

// Fringe - Declaration
void insert_to_FringeLL(int to_insert_level, int to_insert_arr[16]);
void remove_from_FringeLL(int to_remove_arr[16]);
void print_the_FringeLL();

// Expanded - Definition
void insert_to_ExpandedLL(int to_insert_arr[16]);

// IDS Computation - Declaration
void start_IDS(int iteration_level);
void check_whether_GoalState(int to_check_arr[16]);
void free_FringeLL_ExpandedLL_SolutionPathLL();

// IDS Computation (When Goal is Found) - Declaration
int count_total_nodes_in_ExpandedLL();

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

// IDS Computation - Definition
void start_IDS(int iteration_level) {

    if(iteration_level == 0) {

        /*
            Process:
                1. Add to ExpandedLL
                2. Check whether the Goal State.
                    2.1. If Goal State = End program, show solution path.
                    2.2. If Not Goal State = Skip/Break this and continue with next iteration.
            Note:
            - We do not have to anymore include to the FringeLL then remove it again.
            - Instead, we can just add it to the ExpandedLL, then check already if Goal State.
            - For iteration_level >= 1, we need to insert first to the Fringe the user_input_arr[].
        */

        insert_to_ExpandedLL(user_input_arr);
        check_whether_GoalState(user_input_arr);

    } else {

        /*
            NOTE:
            - current_iteration_level increments by 1.
            - Once current_iteration_level == iteration_level, if no more to expand using DFS,
            then STOP.
            - Once STOP, go back to main, and iterate again (iteration_level++;).
        */
        int current_iteration_level = 0;

        insert_to_FringeLL(0, user_input_arr);

    }

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
    // Add code here later.

}

// IDS Computation (When Goal is Found) - Definition
int count_total_nodes_in_ExpandedLL() {

    struct ExpandedLL *total_counter = expandedLL_head;
    int total_count = 0;

    while(total_counter != NULL) {
        total_count++;
        total_counter = total_counter -> next;
    }

    return total_count;

}

void main() {

    board_guide();      // Show Guide Table
    get_user_input();   // Get User Input

    // Start IDS Algorithm
    int iteration_level = 0;

    while(goal_state_found == 0) {  // 0 = false (not found, continue), 1 = true (found, end program)
        start_IDS(iteration_level);

        if(goal_state_found != 0)   // 1 = Goal State Found.
            break;
        
        // The following code below will not be run when the if statement above is true.
        free_FringeLL_ExpandedLL_SolutionPathLL();
        iteration_level++;
    }

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

   printf("\n");
   printf("Nahanap rin sa wakas goal state.\n");
   printf("Nag wowork pa lang so far, pag yung mismong input is Goal State na.\n\n");
   
   printf("[SOLUTION PATH] = \n");
   printf("[SOLUTION COST] = \n");
   printf("[SOLUTION SEARCH COST] = %d\n", count_total_nodes_in_ExpandedLL());
   printf("[RUNNING TIME] = \n");
    
}