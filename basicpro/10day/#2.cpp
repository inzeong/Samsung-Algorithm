#include <cstring>
#include <iostream>
#define Mult(a) (((a) << 7) - (a))

constexpr int MAX_CONTENTS{500000};
constexpr int MAX_WORD{100000};
constexpr unsigned long long BASE{5381};

char contents[MAX_CONTENTS + 1];
char word[MAX_WORD + 1];

unsigned long long dib(const char *start, const char *end) {
    unsigned long long hash{BASE};
    for (const char *c{start}; c != end; ++c) {
        hash = Mult(hash) + *c;
    }
    return hash;
}

unsigned long long subtract_table['z' + 1];

int countwords() {
    const int contents_len{static_cast<int>(std::strlen(contents))};
    const int word_len{static_cast<int>(std::strlen(word))};
    if (contents_len < word_len) {
        return 0;
    }

    const auto word_hash = dib(word, word + word_len);

    auto base_to_subtract = BASE;
    for (int i{0}; i < word_len - 1; ++i) {
        base_to_subtract = Mult(base_to_subtract);
    }

    const auto tmp = base_to_subtract;
    base_to_subtract = Mult(base_to_subtract);
    base_to_subtract -= tmp;

    for (char c{'0'}; c <= '9'; ++c) {
        subtract_table[c - '0'] = c;
        for (int i{0}; i < word_len - 1; ++i) {
            subtract_table[c - '0'] = Mult(subtract_table[c - '0']);
        }
    }
    for (char c{'A'}; c <= 'Z'; ++c) {
        subtract_table[c - '0'] = c;
        for (int i{0}; i < word_len - 1; ++i) {
            subtract_table[c - '0'] = Mult(subtract_table[c - '0']);
        }
    }
        for (char c{'a'}; c <= 'z'; ++c) {
        subtract_table[c - '0'] = c;
        for (int i{0}; i < word_len - 1; ++i) {
            subtract_table[c - '0'] = Mult(subtract_table[c - '0']);
        }
    }

    int cnt{0};
    unsigned long long contents_hash;
    
    for (int i{0}; i <= contents_len - word_len; ++i) {
        if (i == 0) {
            contents_hash = dib(contents, contents + word_len);
        } else {
            contents_hash -=
                base_to_subtract + subtract_table[contents[i - 1] - '0'];
            contents_hash = Mult(contents_hash) + contents[i + word_len - 1];
        }
           if (word_hash == contents_hash) {
            ++cnt;
        }
    }
    return cnt;
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T;
    for (int test_case{1}; test_case <= T; ++test_case) {
        std::cin >> contents >> word;
        std::cout << '#' << test_case << ' ' << countwords() << '\n';
    }
    return 0;
}