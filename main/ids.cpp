#include <iostream>
#include <vector>
using namespace std;

vector<int> goal_state = {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
vector<int> user_input;
vector<int> expanded;
vector<int> fringe;
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

}

int main() {

    get_user_input();
    print_user_input();

    // Start IDS here.
    while(true) {
        
        depth_limit++;
    }
    return 0;

}