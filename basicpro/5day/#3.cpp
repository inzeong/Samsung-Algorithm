#include <iostream>
constexpr int N{301};
bool map[N][N], fill[N][N];

constexpr int D{8};
int dx[D]{1, 1, 0, -1, -1, -1, 0, 1};
int dy[D]{0, 1, 1, 1, 0, -1, -1, -1};
long start, end;
int width;

bool inrange(int x, int y) {
    return x >= 0 && x < width && y >= 0 && y < width;
}

bool adjacent(int x, int y) {
    for (int i{0}; i < D; ++i) {
        int nx{x + dx[i]};
        int ny{y + dy[i]};
        if (inrange(nx, ny) && map[ny][nx]) {
            return true;
        }
    }
    return false;
}

int queue_x[N * N], queue_y[N * N];
void init() { start = end = 0; }
bool empty() { return start == end; }

void enqueue(int x, int y) {
    queue_x[end] = x;
    queue_y[end++] = y;
}

void dequeue(int &x, int &y){
    x = queue_x[start];
    y = queue_y[start++];
}

void filled(int x, int y){
    fill[y][x] = true;
    init();
    enqueue(x, y);
    while (!empty()) {
        dequeue(x, y);
        for (int i{0}; i < D; ++i) {
            const int nx{x + dx[i]};
            const int ny{y + dy[i]};
            if (!inrange(nx, ny) || fill[ny][nx] || map[ny][nx]) {
                continue;
            }
            fill[ny][nx] = true;
            if (!adjacent(nx, ny)) {
                enqueue(nx, ny);
            }
        }
    }
}

long click() {
    for (int y{0}; y < width; ++y) {
        for (int x{0}; x < width; ++x) {
            fill[y][x] = false;
        }
    }

    long cnt{0};
    for (int y{0}; y < width; ++y) {
        for (int x{0}; x < width; ++x) {
            if (map[y][x] || fill[y][x]) {
                continue;
            }
            if (adjacent(x, y)) {
                
                bool zerofound{false};
                for (int i{0}; i < D; ++i) {
                    const int nx{x + dx[i]};
                    const int ny{y + dy[i]};
                    if (!inrange(nx, ny) || map[ny][nx] || fill[ny][nx] ||
                        adjacent(nx, ny)) {
                        continue;
                    }
                    zerofound = true;
                    filled(nx, ny);
                    ++cnt;
                    break;
                }
                if (!zerofound) {
                    fill[y][x] = true;
                    ++cnt;
                }
            } else {
                ++cnt;
                filled(x, y);
            }
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
        std::cin >> width;
        for (int y{0}; y < width; ++y) {
            for (int x{0}; x < width; ++x) {
                char i;
                std::cin >> i;
                map[y][x] = i == '*';
            }
        }
        std::cout <<  '#' << test_case << ' '  << click() << '\n';
    }
    return 0;
}