#include <iostream>
constexpr long MAX{100001};

class MaxHeap {
    long size{0};
    long arr[MAX];

    static long parent(long i) { 
        return (i - 1) >> 1; 
    }
    static long left(long i) { 
        return (i << 1) + 1; 
    }
    static long right(long i) { 
        return (i + 1) << 1; 
    }

    bool cmp(long i, long j) const { 
        return arr[i] > arr[j]; }

    void max_heap(long i){
        const long l{left(i)};
        const long r{right(i)};
        long max{l < size && cmp(l, i) ? l : i};
        if (r < size && cmp(r, max)) {
            max = r;
        }
        if (max != i) {
            const long tmp{arr[i]};
            arr[i] = arr[max];
            arr[max] = tmp;
            max_heap(max);
        }
    }

    void increase_key(long i, long key){
        arr[i] = key;
        long p{parent(i)};
        while (i && cmp(i, p)) {
            const long tmp{arr[i]};
            arr[i] = arr[p];
            arr[p] = tmp;
            i = p;
            p = parent(i);
        }
    }

  public:
    void init() { 
        size = 0;
    }
    
    bool empty() const {
        return size == 0; 
    }
    
    long max() const { 
        return arr[0]; 
    }

    long emax(){
        if (empty()) {
            return -1;
        }
        const long key{
            arr[0]
        };

        arr[0] = arr[--size];
        max_heap(0);

        return key;
    }

    void insert(long val) {
        arr[size] = 0;
        increase_key(size++, val);
    }
} heap;

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T;
    
    for (int test_case{1}; test_case <= T; ++test_case) {
        std::cout << '#' << test_case;
        heap.init();

        long cnt;
        std::cin >> cnt;
        
        while (cnt--) {
            int op;
            std::cin >> op;
            
            if (op == 1) {
                long x;
                std::cin >> x;
                heap.insert(x);
                
            } 
            else {
                std::cout << ' ' << heap.emax();
            }
        }
        std::cout << '\n';
    }
    return 0;
}