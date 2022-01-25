#include <iostream>

constexpr long INF{2147483647L};
constexpr long N{100001};

long arr[N];
long larr[N / 2 + 1];
long rarr[N / 2 + 1];

long merge(long begin, long middle, long end) {
    const long llen{middle - begin};
    const long rlen{end - middle};

    long i{0},j{0};
    long count{0};

    while (i < llen || j < rlen) {
        if (larr[i] <= rarr[j]) {
            arr[i + j + begin] = larr[i];
            ++i;
        }
        else {
            arr[i + j + begin] = rarr[j];
            ++j;
            count += llen - i;
        }
    }
    return count;
}

void copy(long *dest, long begin, long end) {
    long j{0};
    for (long i{begin}; i < end; ++i) {
        dest[j++] = arr[i];
    }
    dest[j] = INF;
}

long inversion(long begin, long end) {
    if (end - begin <= 1) {
        return 0;
    }
    const long middle{(begin + end) / 2};
    const long lcnt{inversion(begin, middle)};
    const long rcnt{inversion(middle, end)};
    
    copy(larr, begin, middle);
    copy(rarr, middle, end);
    return lcnt + rcnt + merge(begin, middle, end);
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T;
    
    for (int test_case{1}; test_case <= T; ++test_case) {
        long len;
        std::cin >> len;
        
        for (long i{0}; i < len; ++i) {
            std::cin >> arr[i];
        }
        std::cout << '#' << test_case << ' ' << inversion(0, len) << '\n';
    }
    return 0;
}