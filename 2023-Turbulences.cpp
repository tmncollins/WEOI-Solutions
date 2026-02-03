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

long long revenue(int N, int K, vector<long long> A) {
    vector<pair<long long, long long>> arr (N);
    for (int k = 0; k < N; k++) {
        arr[k] = make_pair(abs(A[k]), A[k]);
    }

    sort(arr.begin(), arr.end());

    // count how many positive values larger than this one
    vector<int> positive (N, 0);
    if (arr[N-1].second > 0) positive[N-1] = 1;
    for (int k = N-2; k >= 0; k--) {
        positive[k] = positive[k+1];
        if (arr[k].second > 0) positive[k]++;
    }

    long long ans = 0; // x = 0

    int k = 0;
    long long tot = 0;
    while (k < N) {
        if (arr[k].first != 0) {
            tot += arr[k].second;
            // count how many of A has the same magnitude
            long long same_val_count = 0;
            while (k+1 < N && arr[k].first == arr[k+1].first) {
                k++;
                same_val_count++;
                tot += arr[k].second;
            }
            long long greater = positive[k];
            if (arr[k].second > 0) greater -= 1;
            long long lesser = N - k - 1 - greater;

            // choose this to be the value of x
            long long x = arr[k].first;
            ans = max(ans, tot + x * (greater - lesser - K));
        }
        k++;
    }

    return ans;


}

int main() {
    int N = 7;
    int K = 1;
    vector<long long> A = {0,3,4,5,-1,-2,-3};

    N = 5;
    K = 1;
    A = {7,8,-2,5,-10};

    cout << revenue(N, K, A) << "\n";
}