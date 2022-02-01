#include <iostream>

constexpr int N{100};
char tree[N + 1];
int left[N + 1], right[N + 1];

bool leaf(int n, int v) {
    return v > n / 2; 
}

bool has_right(int n, int v) {
    return v * 2 < n;
}

void read_tree(int n, int i = 1) {
    if (i > n || i <= 0) {
        return;
    }
    
    read_tree(n, left[i]);
    std::cout << tree[i];
    read_tree(n, right[i]);
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    constexpr int T{10};
    for (int test_case{1}; test_case <= T; ++test_case) {
        int n;
        std::cin >> n;
        for (int i{0}; i < n; ++i) {
            int idx, l, r;
            char ch;
            std::cin >> idx >> ch;
            tree[idx] = ch;
            if (!leaf(n, idx)) {
                std::cin >> l;
                left[idx] = l;
                if (has_right(n, idx)) {
                    std::cin >> r;
                    right[idx] = r;
                }
            }
        }
        std::cout << '#' << test_case << ' ';
        read_tree(n);
        std::cout << '\n';
    }
    return 0;
}