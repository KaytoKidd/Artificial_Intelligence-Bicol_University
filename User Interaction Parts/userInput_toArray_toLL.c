#include <stdio.h>
#include <stdlib.h>

void user_input_to_ARRAY();
void user_input_to_LL(char table_input[]);

struct user_input_LL {

    char data;
    struct user_input_LL *next;

};

struct user_input_LL *user_input_LL_head = NULL;

void user_input_to_ARRAY() {

    char table_guide[] = {'a', 'b', 'c', 'd', 
                          'e', 'f', 'g', 'h', 
                          'i', 'j', 'k', 'l', 
                          'm', 'n', 'o', 'p'};
    char table_input[16];

    int i = 0;
    char user_input = ' ';

    for(i = 0; i < 16; i++) {

        printf("%c = ", table_guide[i]);
        scanf(" %c", &user_input);

        if (user_input == 'B')
            table_input[i] = ' ';
        else
            table_input[i] = user_input;
            
    }

    // Call the function user_input_to_LL to transfer Array to LinkedList.
    user_input_to_LL(table_input);

}

void user_input_to_LL(char table_input[]) {

    struct user_input_LL *iterator = user_input_LL_head;
    int i = 0;
    
    for(i = 0; i < 16; i++) {

        iterator = user_input_LL_head;
        struct user_input_LL *new_node = malloc(sizeof(struct user_input_LL *));

        if (user_input_LL_head == NULL) {
            user_input_LL_head = new_node;
        } else {
            while(iterator -> next != NULL) {
                iterator = iterator -> next;
            }
            iterator -> next = new_node;
        }

        new_node -> next = NULL;
        new_node -> data = table_input[i];

    }

    // Printing all of the contents of the LinkedList "user_input_LL".
    printf("\n\n");

    iterator = user_input_LL_head;
    while (iterator != NULL) {
        printf("%c\n", (iterator -> data));
        iterator = iterator -> next;
    }

}

void main() {

    user_input_to_ARRAY();

}