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
int goal_state_found = 0;   // 0 = not found, 1 = found

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
    fringe_level.clear();
    to_expand.clear();

    to_expand_level = 0;
    goal_state_found = 0;

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

    fringe.pop_back();
    fringe_level.pop_back();

}

void insert_to_expanded() {

    expanded.push_back(to_expand);

}

bool check_if_goal() {

    if(to_expand == goal_state) {
        goal_state_found = 1;
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

bool check_whether_already_in_expanded(vector<int> to_expand_for_exchanging) {

    for(int i = 0; i < expanded.size(); i++) {
        if(to_expand_for_exchanging == expanded[i]) {
            return true;
        }
    }

    return false;

}

void start_expanding() {
    
    /*
        Priority of Movements
        96 - UP
        97 - LEFT
        98 - DOWN
        99 - RIGHT

    NOTE: We need to reverse so that push-pop will still follow
          the priority UP -> DOWN -> LEFT -> RIGHT
    */
    vector<vector<vector<int>>> movements = {
        {{1, 4},{99, 98}}, // 0
        {{2, 5, 0},{99, 98, 97}}, // 1
        {{3, 6, 1},{99, 98, 97}}, // 2
        {{7, 2},{98, 97}}, // 3
        {{5, 8, 0},{99, 98, 96}}, // 4
        {{6, 9, 4, 1},{99, 98, 97, 96}}, // 5
        {{7, 10, 5, 2},{99, 98, 97, 96}}, // 6
        {{11, 6, 3},{98, 97, 96}}, // 7
        {{9, 12, 4},{99, 98, 96}}, // 8
        {{10, 13, 8, 5},{99, 98, 97, 96}}, // 9
        {{11, 14, 9 ,6},{99, 98, 97, 96}}, // 10
        {{15, 10, 7},{98, 97, 96}}, // 11
        {{13, 8},{99, 96}}, // 12
        {{14, 12, 9},{99, 97, 96}}, // 13
        {{15, 13, 10},{99, 97, 96}}, // 14
        {{14, 11},{97, 96}}  // 15
    };

    int index_of_negative_one = 0;
    for(int i = 0; i < to_expand.size(); i++) {
        if(to_expand[i] == -1) {
            index_of_negative_one = i;
            break;
        }
    }

    int x = index_of_negative_one;
    int index_y = 0;
    int label_y = 1;

    vector<int> movements_index;
    vector<int> movements_label;

    for(int i = 0; i < movements[x][index_y].size(); i++) {
        movements_index.push_back(movements[x][index_y][i]);
        movements_label.push_back(movements[x][label_y][i]);
    }

    for(int i = 0; i < movements_index.size(); i++) {

        vector<int> to_expand_for_exchanging = to_expand;

        // Exchange Value Per Index
        int temp = to_expand_for_exchanging[index_of_negative_one];
        to_expand_for_exchanging[index_of_negative_one] = to_expand_for_exchanging[movements_index[i]];
        to_expand_for_exchanging[movements_index[i]] = temp;

        if(check_whether_already_in_expanded(to_expand_for_exchanging) == false) {
            // Then add to fringe
            // Then add to fringe_level
            fringe.push_back(to_expand_for_exchanging);
            fringe_level.push_back(to_expand_level + 1);
        }
    }

}

void start_IDS() {

    continue_and_go_here:

    if(possible_to_expand() == true) {      // Fringe is not empty.
        
        remove_from_fringe();
        insert_to_expanded();
        if(check_if_goal() == true) {

            // Nothing yet.

        } else {
            if(should_be_expanded() == true) {
                start_expanding();
            }
            goto continue_and_go_here;
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

        if(goal_state_found == 1) {
            break;
        }

        depth_limit++;
    }
    cout << "GOAL FOUND!\n";
    cout << "Total Level Generated = " << depth_limit << "\n";
    return 0;

}