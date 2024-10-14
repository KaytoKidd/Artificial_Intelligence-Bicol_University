#include <stdio.h>
#include <stdlib.h>

void user_input_to_ARRAY();
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

    // Printing the array.
    printf("\n\n");
    for(i = 0; i < 16; i++) {
        printf("%c\n", table_input[i]);
    }

}

void main() {

    user_input_to_ARRAY();

}