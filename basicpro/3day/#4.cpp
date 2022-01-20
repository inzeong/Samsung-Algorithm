#include <iostream>

constexpr int N{100};
constexpr int K{1000};
int we[N + 1];
int va[N + 1];
int dp[N + 1][K + 1];

int max(int a, int b) { 
    return a > b ? a : b; 
}

int knapsack(int cnt, int cap){
    for (int n{1}; n <= cnt; ++n) {
        for (int w{1}; w <= cap; ++w) {
            const int wn{we[n]};
            if (wn > w) {
                dp[n][w] = dp[n - 1][w];
            } else {
                dp[n][w] = max(dp[n - 1][w], va[n] + dp[n - 1][w - wn]);
            }
        }
    }
    return dp[cnt][cap];
}

int main(int argc, char **argv){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int T;
    std::cin >> T;
    for (int test_case{1}; test_case <= T; ++test_case) {
        int count, capacity;
        std::cin >> count >> capacity;
        for (int i{1}; i <= count; ++i) {
            std::cin >> we[i] >> va[i];
        }
        std::cout << '#' << test_case << ' ' << knapsack(count, capacity)<< '\n';
    }
    return 0;
}