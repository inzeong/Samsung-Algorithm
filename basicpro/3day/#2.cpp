#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int ans; int change;
string s;
void dfs(int index, int current) {
    if(current == change) {
        ans = max(ans, stoi(s));
        return;
    }
    for(int i = index; i < s.size() - 1; i++) {
        for(int j = i + 1; j < s.size(); j++) {
            swap(s[i], s[j]);
            dfs(i, current + 1);
            swap(s[i], s[j]);
        }
    }
}

int main(void) {
    int t;
    std::cin >> t;

    for(int test = 1; test <= t; test++) {
        std::cin >> s >> change;
        ans = 0;
        if(change > s.size())
            change = s.size();
        dfs(0, 0);
        std::cout << "#" << test << " " << ans << endl;
    }
    return 0;
}