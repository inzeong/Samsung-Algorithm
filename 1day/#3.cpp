#include <iostream>

long activities(const char *schedule){
    constexpr int N{15};
    constexpr long M{1'000'000'007};

    long long count[N], old_count[N];
    const int selected = 1 << (*schedule++ - 'A');
    for (int set = 1; set <= N; ++set) {
        count[set - 1] = (selected & set) && (1 & set);
    }

    for (char c = *schedule; c; c = *++schedule) {
        const int selected = 1 << (c - 'A');

        for (int i = 0; i < N; ++i) {
            old_count[i] = count[i];
            count[i] = 0LL;
        }

        for (int set = 1; set <= N; ++set) {
            if (!(selected & set)) {
                continue;
            }
            for (int old_set = 1; old_set <= N; ++old_set) {
                if (!(set & old_set)) {
                    continue;
                }
                count[set - 1] += old_count[old_set - 1];
            }
            count[set - 1] %= M;
        }
    }
    long long sum{0LL};
    for (int i = 0; i < N; ++i) {
        sum += count[i];
    }
    return sum % M;
}

int main(int argc, char **argv){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T;

    char sbuf[10001];
    for (int test_case = 1; test_case <= T; ++test_case) {
        std::cin >> sbuf;
        std::cout << '#' << test_case << ' ' << activities(sbuf) << '\n';
    }
    return 0;
}