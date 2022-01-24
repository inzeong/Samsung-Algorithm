#include <iostream>

constexpr long N{100000};
long start[N], end[N];
long des[N+1]


void swap(long *a, long *b) {
    long tmp{*a};
    *a = *b;
    *b = tmp;
}

long max(long a, long b) { 
    return a > b ? a : b; 
}

void quick_sort(long *begin, long *end) {
    if (end - begin < 2) {
        return;
    }

    long *d{begin};
    long *r{end - 1};

    const long pivot{
        *(begin + (end - begin) / 2)
    };

    while (d < r) {
        while (*d < pivot) {
            ++d;
        }
        while (*r > pivot) {
            --r;
        }

        if (d <= r) {
            swap(d++, r--);
        }
    }

    quick_sort(begin, r + 1);
    quick_sort(d, end);
}

long maxover(long len, long cnt) {
    
    quick_sort(start, start + cnt);
    quick_sort(end, end + cnt);

    for (long i{0}; i < cnt; ++i) {
        accum[i + 1] = accum[i] + end[i] - start[i];
    }

    long option{0};
    for (long i{0}; i < cnt; ++i) {

        const long limit{start[i] + len};

        long low{i};
        long high{cnt - 1};

        while (low <= high) {
            const long middle{(low + high) / 2};
            if (start[middle] >= lim) {
                high = middle - 1;
            } 
            else if (end[middle] <= limit) {
                low = middle + 1;
                option = max(option, des[middle + 1] - des[i]);
            } 
            else {
                option = max(option, des[middle] - des[i] + limit - start[middle]);
                break;
            }
        }
    }

    return option;
}

int main(int argc, char **argv){}
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int T;
    std::cin >> T;
    for (int test_case{1}; test_case <= T; ++test_case) {
        long len, cnt;
        std::cin >> len >> cnt;

        for (int i{0}; i < cnt; ++i) {
            std::cin >> start[i] >> end[i];
        }

        std::cout << '#' << test_case << ' ' << maxover(len, cnt) << '\n';
    }
    return 0;
}