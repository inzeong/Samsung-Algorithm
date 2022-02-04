#include <iostream>
#include <limits>
#include <map>

constexpr int N{10};

long divisors[N];
std::map<long, long> memo;

long minadd(int n, long s){
    const auto search = memo.find(s);
    if (s == 0) {
        return 0;
    }
    if (search != memo.end()) {
        return search->second;
    }

    long min{std::numeric_limits<long>::max()};
    for (int i{0}; i < n; ++i) {
        const long val{s % divisors[i] + minadd(n, s / divisors[i])};
        if (min > val) {
            min = val;
        }
    }
    memo[s] = min;
    return min;
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T;
    
    for (int test_case{1}; test_case <= T; ++test_case) {
        memo.clear();
        int n;
        std::cin >> n;
        for (int i{0}; i < n; ++i) {
            std::cin >> divisors[i];
        }
        long s;
        std::cin >> s;
        std::cout << '#' << test_case << ' ' << minadd(n, s) << '\n';
    }
    return 0;
}