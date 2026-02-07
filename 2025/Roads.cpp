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

/*
1) Find shortest path from home to rome and orient all roads towards rome
2) BFS from rome to home orienting all roads towards home
3) If we can't reach home, it is impossible
4) Orient all other roads randomly
*/

const long long INF = 1152921504606846976;

vector<pair<int, int>> roads;
map<pair<int, int>, int> road_lookup;
vector<bool> road_set;
vector<vector<pair<long long, long long>>> graph;

void set_road(int u, int v) {
    int k = road_lookup[{min(u,v), max(u,v)}];
    roads[k] = {u,v};
    road_set[k] = true;
}

bool home_to_rome(int N, int M, vector<int> &A, vector<int> &B) {
    priority_queue<vector<long long>, deque<vector<long long>>, greater<vector<long long>>> pq;
    pq.push({0, 0});

    vector<long long> seen (N, INF);
    vector<int> parent (N, -1);
    seen[0] = 0;

    bool found_rome = false;

    while (!pq.empty()) {
        vector<long long> vec = pq.top();
        pq.pop();
        int u = vec[1];
        long long d = vec[0];

        if (u == N-1) {
            // reached ROME!
            found_rome = true;
            break;
        }

        for (auto p : graph[u]) {
            int v = p.first;
            long long d2 = p.second;
            
            if (d2 + d < seen[v]) {
                seen[v] = d2 + d;
                parent[v] = u;
                pq.push({d2+d, v});
            }
        }
    }

    if (!found_rome) return false;

    // orient roads on path towards ROME
    int v = N-1;
    while (true) {
        int u = parent[v];
        if (u == -1) break;
//        cout << u << " -> " << v << "\n";
        // road from u to v
        set_road(u, v);
        v = parent[v];
    }

    return true;
}

bool rome_back_home(int N, int M, vector<int> &A, vector<int> &B) {

    deque<int> q;
    q.push_back(N-1);
    vector<bool> seen (N, false);
    seen[N-1] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();

        if (u == 0) {
            // found home
            return true;
        }

        for (auto p : graph[u]) {
            int v = p.first;
            int k = road_lookup[{min(u,v), max(u,v)}];
            if (seen[v]) continue;
            if (!road_set[k]) {
                set_road(u, v);
                q.push_back(v);
                seen[v] = true;
            }
            else {
                if (roads[k].first == u) {
                    q.push_back(v);
                    seen[v] = true;
            }
            }
        }
    }

    return false;

}

vector<pair<int, int>> orient_roads(int N, int M, vector<int> A, vector<int> B, vector<int> W) {
    vector<pair<int, int>> empty;
    if (M < N) return empty;

    roads.resize(M);
    graph.resize(N);
    road_set = vector<bool> (M, false);

    for (int k = 0; k < M; k++) {
        int u = A[k];
        int v = B[k];
        long long d = W[k];
        graph[u].push_back({v, d});
        graph[v].push_back({u, d});
        road_lookup[{min(u,v), max(u,v)}] = k;
    }

    // 1 - shortest back from home to rome
//    cout << "1\n";
    if (!home_to_rome(N, M, A, B)) return empty;

    // 2 - find a path back home
//    cout << "2\n";
    if (!rome_back_home(N, M, A, B)) return empty;

    // 3 - set all remaining edges at random
//    cout << "3\n";
    for (int k = 0; k < M; k++) {
        if (!road_set[k]) set_road(A[k], B[k]);
    }

    return roads;
}

int main() {
    int N = 7;
    int M = 8;
    vector<int> A = {0,1,2,3,0,4,5,1};
    vector<int> B = {1,2,3,6,4,5,6,5};
    vector<int> W = {3,1,2,1,1,4,2,1};

    /*
    N = 5;
    M = 6;
    A = {0,1,0,3,2,3};
    B = {1,2,3,2,4,4};
    W = {1,1,1,1,1,5};

    N = 8;
    M = 9;
    A = {0,1,2,0,3,4,5,6,5};
    B = {1,2,4,3,4,5,6,7,7};
    W = {3,4,2,6,1,3,1,2,3};
    */
    vector<pair<int, int>> ans = orient_roads(N, M, A, B, W);
    if (ans.size() == 0) cout << "No" << "\n";
    else cout << "Yes" << "\n";
    for (auto p : ans) {
        cout << p.first << " " << p.second << "\n";
    }
}
