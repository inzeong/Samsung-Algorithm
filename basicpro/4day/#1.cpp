#include <iostream>

constexpr long N{200000};
long days[N];
long start[N], end[N];
long accum[N + 1];

long max(long a, long b) { 
    return a > b ? a : b; 
}

long check(long cnt, long rem) {
    long c{0};
    bool inside{false};
    long ch{0}; //chunck
    
    for (int i{0}; i < cnt; ++i) {
        if (!inside) {
            start[ch] = days[i];
            inside = true;
        }
        
        if (inside && (i + 1 == cnt || days[i + 1] - days[i] > 1)) {
            end[ch] = days[i];
            accum[ch + 1] = accum[ch] + end[ch] - start[ch] + 1;
            ++ch;
            inside = false;
        }
    }
    
    long option{0};
    for (long i{0}; i < ch; ++i) {
        long low{i};
        long high{ch - 1};
        
        while (low <= high) {
            const long middle{(low + high) / 2};
            const long dur{end[middle] - start[i] + 1};
            const long diff{dur - accum[middle + 1] + accum[i]};
            if (diff == rem) {
                option = max(option, dur);
                break;
            } 
            else if (diff < rem) {
                low = middle + 1;
                option = max(option, dur + rem - diff);
            } 
            else {
                high = middle - 1;
            }
        }
    }

    return option;
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int T;
    std::cin >> T;
    for (int test_case{1}; test_case <= T; ++test_case) {
        long cnt, rem;
        std::cin >> cnt >> rem;
        for (int i{0}; i < cnt; ++i) {
            std::cin >> days[i];
        }
        std::cout << '#' << test_case << ' ' << check(cnt, rem) << '\n';
    }
    return 0;
}