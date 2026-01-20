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

//#include "equal.h"

using namespace std;

int N; 
vector<long long> nums;

bool compare(int i, int j) {
    return nums[i] == nums[j];
}

void add(vector<int> S, long long X) {
    for (int i : S) {
        nums[i] += X;
    }
    sort(nums.begin(), nums.end());
}

void output() {
    for (int i : nums) cout << i << " ";
    cout << "\n";
}

void make_all_equal(int N, int Q_add, int Q_compare) {
    // MERGE SORT
    for (int p = 2; p <= N; p *= 2) {
        vector<int> q;
        for (int i = 0; i < N - p + 1; i += p) {
            for (int j = i; j < i + p/2; j++)
                q.push_back(j);
        }
        // keep adding to the smaller half until difference is at most 1
        for (int i = 19; i >= 0; i--) {
            long long x = (1 << i);
            add(q, x);
        }
        // identify if difference between halves is 0 or 1
        vector<int> q2; 
        for (int i = 0; i < N - p + 1; i += p) {
            if (!compare(i, i+p-1)) {
                for (int j = i; j < i + p/2; j++)
                    q2.push_back(j);
            }
        }
        if (!q2.empty()) add(q2, 1);
        output();
    }
}

int main() {

    nums = {1,3,5,6,7,8,12,34};
    N = nums.size();

    make_all_equal(N, 1, 1);


}