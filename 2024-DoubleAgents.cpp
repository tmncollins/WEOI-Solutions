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

/*

Each double agent must be in a different branch to ensure paths between them do not contain
other double agents. 

*/

using namespace std;


const int MOD = 1e9 + 7;

inline int ADD(int x, int y) {
    return (x+y) % MOD;
}

inline int SUB(int x, int y) {
    x -= y;
    while (x < 0) x += MOD;
    return x;
}

inline long long MULT(long long x, long long y) {
    return (x*y) % MOD;    
}

vector<vector<int>> graph;
vector<int> sets, sets_subtrees;

void dfs(int root, int parent) {
    sets[root] = 1;
    int cnt1 = 0, cnt2 = 1;
    for (int child : graph[root]) {
        if (child == parent) continue;
        
        dfs(child, root);

        // add root to S and recurse on this subtree
        sets[root] = ADD(sets[root], sets_subtrees[child]);

        // do not add root to S and recurse on multiple subtrees
        cnt2 = MULT(cnt2 , ADD(sets_subtrees[child], 1));
        sets[root] = SUB(sets[root], sets_subtrees[child]);

        // do not add root to S and recurse on this subtree
        cnt1 = ADD(cnt1, sets[child]);
    }

    sets[root] = ADD(SUB(sets[root], 1), ADD(cnt1, cnt2));
    sets_subtrees[root] = 1;
    int cnt = 1;
    for (int child : graph[root]) {
        if (child == parent) continue;
        cnt = MULT(cnt, ADD(sets_subtrees[child], 1));
    }
    sets_subtrees[root] = ADD(sets_subtrees[root], SUB(cnt, 1));
}

int count_sets(int N, vector<int> u, vector<int> v) {
    graph = vector<vector<int>>(N);
    sets = vector<int>(N, 0);
    sets_subtrees = vector<int>(N, 0);
    for (int i = 0; i + 1 < N; ++i) {
        graph[u[i]].push_back(v[i]);
        graph[v[i]].push_back(u[i]);
    }
    dfs(0, -1);
    return sets[0];
}

/*
int main() {

    int N = 5;
    vector<int> U = {0, 0, 1, 1};
    vector<int> V = {1,2,3,4};
    cout << count_sets(N, U, V);

}
*/