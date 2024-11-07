#include <iostream>
#include <vector>
using namespace std;

vector<int> goal_state = {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
vector<int> user_input;
vector<vector<int>> expanded;
vector<vector<int>> fringe;
vector<int> fringe_level;
vector<int> to_expand;

int to_expand_level = 0;
int depth_limit = 0;

void get_user_input() {

    printf("Table Guide:\n1  2  3  4\n5  6  7  8\n9  10 11 12\n13 14 15 16\n\n");
    int the_input;

    for(int i = 0; i < 16; i++) {
        cout << "[" << (i + 1) << "] = ";
        cin >> the_input;
        user_input.push_back(the_input);
    }

}

void print_user_input() {

    for(int i : user_input) {
        cout << i << " ";
    }
    cout << "\n";

}

void start_initialization() {

    expanded.clear();
    fringe.clear();
    fringe.push_back(user_input);
    fringe_level.push_back(0);

}

bool possible_to_expand() {

    if(fringe.empty() == true) {
        return false;
    } else {
        to_expand = fringe.back();
        to_expand_level = fringe_level.back();
        return true;
    }

}

void remove_from_fringe() {

    for(int i = 0; i < fringe.size(); i++) {
        if(fringe[i] == to_expand) {
            fringe.pop_back();
            fringe_level.pop_back();
            break;
        }
    }

}

void insert_to_expanded() {

    expanded.push_back(to_expand);

}

bool check_if_goal() {

    if(to_expand == goal_state) {
        return true;
    } else {
        return false;
    }

}

bool should_be_expanded() {

    if(to_expand_level == depth_limit) {
        return false;
    } else {
        return true;
    }

}

void start_expanding() {

    /*
        Priority of Movements
        96 - UP
        97 - LEFT
        98 - DOWN
        99 - RIGHT
    */

   vector<vector<vector<int>>> movements = {
        {{4, 1},{98, 99}}, // 0
        {{0, 5, 2},{97, 98, 99}}, // 1
        {{1, 6, 3},{97, 98, 99}}, // 2
        {{2, 7},{97, 98}}, // 3
        {{0, 8, 5},{96, 98, 99}}, // 4
        {{1, 4, 9, 6},{96, 97, 98, 99}}, // 5
        {{2, 5, 10, 7},{96, 97, 98, 99}}, // 6
        {{3, 6, 11},{96, 97, 98}}, // 7
        {{4, 12, 9},{96, 98, 99}}, // 8
        {{5, 8, 13, 10},{96, 97, 98, 99}}, // 9
        {{6, 9, 14, 11},{96, 97, 98, 99}}, // 10
        {{7, 10, 15},{96, 97, 98}}, // 11
        {{8, 13},{96, 99}}, // 12
        {{9, 12, 14},{96, 97, 99}}, // 13
        {{10, 13, 15},{96, 97, 99}}, // 14
        {{11, 14},{96, 97}}  // 15
   };

}

void start_IDS() {

    if(possible_to_expand() == true) {      // Fringe is not empty.
        
        remove_from_fringe();
        insert_to_expanded();
        if(check_if_goal() == true) {

        } else {
            if(should_be_expanded() == true) {
                start_expanding();
            }
        }

    }

}

int main() {

    get_user_input();
    print_user_input();

    // Start IDS here.
    while(true) {
        start_initialization();
        start_IDS();
        depth_limit++;
    }
    return 0;

}