#include <iostream>
#include <list>
#include <sstream>
#include <vector>  
#include <iterator> 
#include <tuple>
#include <istream>
#include <map>
#include <set>
#include <deque>
#include <limits>
#include <algorithm>
#include <queue>
#include <cstring>
#include <array>
#include <unordered_set>
#include <random>
#include <chrono>
#include <fstream>
#include <variant>

using namespace std;

vector<int> find_tour(int N, vector<int> A) {
    vector<int> empty;
    // check end shops are valid
    if (A[0] != 2 || A[N-1] != 2) return empty;

    /*
    Categorise all shops into 3 camps:
        1 - We are the left end of both intervals
        2 - We are the right end of both intervals
        3 - We are the left end on one interval and the right end of the other
    */

    int LEFT = 1, RIGHT = 2, BOTH = 3;
    vector<int> shop_type (N, 0);
    shop_type[0] = LEFT;
    int incomplete_intervals = 2; // we don't know the right ends of both intervals including shop 0

    for (int shop = 1; shop < N; shop++) {
        if (A[shop] == 2 + incomplete_intervals) {
            // shop must be the left ends of two intervals we have not yet encountered
            shop_type[shop] = LEFT;
            incomplete_intervals += 2;
        }
        else if (A[shop] == incomplete_intervals) {
            // shop must be the right ends of two intervals we have already encountered
            shop_type[shop] = RIGHT;
            incomplete_intervals -= 2;
        }
        else if (A[shop] == incomplete_intervals + 1) {
            // shop must be a right & left end of its two intervals
            shop_type[shop] = BOTH;
        }
        else {
            // too many / too few intervals required -- not possible
            return empty;
        }

        if (incomplete_intervals < 0) return empty;
    }

    if (incomplete_intervals != 0) return empty;

    /*
    Construct the lexicographically smallest shop tour
    - Since the tour is cyclic, start at shop 0 and end at shop N-1
    - Shop 0 is category 1 (LEFT) so next must be category 2 or 3
    - Iterately over remaining shops in order, adding shops greedily
        - If shop has category 3 (BOTH), then simply add
        - If shop has category 1 (LEFT), then store for later use
        - If shop has category 2 (RIGHT), then add and add a LEFT shop that was stored earlier
    */

    vector<int> tour;
    tour.push_back(0);
    deque<int> q;
    for (int shop = 1; shop < N-1; shop++) {
        if (shop_type[shop] == LEFT) {
            q.push_back(shop); // save this corresponding left end for later
        }
        else if (shop_type[shop] == RIGHT) {
            tour.push_back(shop);
            if (q.empty()) return empty; // no corresponding left end!
            tour.push_back(q.front());
            q.pop_front();
        }
        else if (shop_type[shop] == BOTH) {
            tour.push_back(shop);
        }
    }
    tour.push_back(N-1);

    return tour;
}

void output(vector<int> v) {
    if (v.empty()) cout << "FALSE";
    for (int i : v) cout << i << " ";
    cout << "\n";
}

int main() {
    int N = 4;
    vector<int> A = {2,4,4,2};
    N = 3;
    A = {2,2,2};

    output(find_tour(N, A));
}
