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

using namespace std;

struct fenwick_tree {
    vector<int> arr;

    fenwick_tree(int size, int v=0) {
        arr.resize(size+1, v);
        fill(arr.begin(), arr.end(), v);
    }

    int lsb(int i) {
        // least significant bit
        return i & -i;
    }

    int get(int index) {
        int sum = 0;
        while (index > 0) {
            sum += arr[index];
            index -= lsb(index); // decr index by least significant bit
        }
        return sum;
    }

    void add(int index, int v) {
        while (index < arr.size()) {
            arr[index] += v;
            index += lsb(index); // incr index by least significant bit
        }
    }

};

vector<int> count(int N, vector<int> S, vector<int> P) {
    int tot_optimal = 0;
    vector<int> ans (N, 0);
    vector<bool> optimal (N, false);
    map<pair<int, int>, int> idx;
    vector<int> dominating (N, 0);

    fenwick_tree fwt (1000000+100);

    vector<pair<int, int>> pts;
    for (int k = 0; k < N; k++) {
        pair<int, int> p = {S[k]+5, P[k]+5};
        pts.push_back(p);
        idx[p] = k;
    }

    sort(pts.begin(), pts.end());

    int MIN_PRICE = 1000000+100;
    int MIN_IDX = -1;
    for (int k = N-1; k >= 0; k--) {
        // we are optimal if there is no one stronger and cheaper
        // everyone so far is stronger as we are going in decreasing strength
        pair<int, int> p = pts[k];
        int price = p.second;
        int i = idx[p];
        int cnt = fwt.get(price-1);
//        cout << k << " " << price << " " << cnt << "\n";
        if (cnt == 0) {
            // optimal!
            optimal[i] = true;
            tot_optimal += 1;
        }
        else if (cnt == 1) {
            // only one dominates us. this is the one with the lowest price so far
            dominating[MIN_IDX] += 1;
        }
        fwt.add(price, 1);

        if (price < MIN_PRICE) {
            MIN_PRICE = price;
            MIN_IDX = i;
        }
    }

    for (int k = 0; k < N; k++) {
        if (optimal[k]) ans[k] = tot_optimal - 1 + dominating[k];
        else ans[k] = tot_optimal;
    }

    return ans;

}

int main() {

    int N = 9;
    vector<int> S = {10, 4, 11, 14, 1, 6, 9, 12, 3};
    vector<int> P = {11, 6, 13, 7, 4, 10, 2, 12, 5};

    vector<int> ans = count(N, S, P);
    for (int i : ans) cout << i << " ";

}