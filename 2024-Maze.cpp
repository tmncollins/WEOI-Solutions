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

int MAX = 20;

vector<vector<char>> solve(long long K) {
    if (K == 1) {
        return {{'.'}};
    }
    MAX = log2(K) + 1;
    MAX *= 3;
    MAX = max(MAX, 10);
    MAX = min(MAX, 200);
    vector<vector<char>> ans(MAX, vector<char>(MAX, '#'));
    ans[0][0] = '.'; // start
    ans[MAX-1] = vector<char>(MAX, '.'); // bottom row to collect all powers of 2
    int x = 0;
    long long num = 0;
    long long power = 1;
    for (int p = 0; num != K; p++) {
        // construct 3x3 2-choice block
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) ans[x + i][x + j] = '.';
        }
        ans[x + 1][x + 1] = '#';
        // construct quick escape option
        if (power & K) {
            for (int i = x; i < MAX; i++) ans[i][x] = '.';
            num ^= power;
        }
        power *= 2;
        x += 2;
    }
    return ans;
}

int main() {

    long long K;

    cin >> K;

    vector<vector<char>> ans = solve(K);

    for (int y = 0; y < ans.size(); y++) {
        for (int x = 0; x < ans[y].size(); x++) {
            cout << ans[y][x];
        }
        cout << "\n";
    }

}