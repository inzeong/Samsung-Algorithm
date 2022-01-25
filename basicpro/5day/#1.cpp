#include <iostream>
using namespace std;

#define MAXN 200000
int W[MAXN], S[MAXN];
int N, K;

bool verify(int val) {
    int pivot = -1;
    for(int k = 0; k < K; k++) {
        for(int s = 0; s < S[k]; s++) {
            pivot++;
           
            if(W[pivot] > val) {
                k--;
                break;
            }
             if(pivot == N) return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N >> K;
        for(int n = 0; n < N; n++) cin >> W[n];
        for(int k = 0; k < K; k++) cin >> S[k];
        
		int l = 0, r = 200000;
        while(l < r) {
            int m = (l + r) / 2;
            if(verify(m)) r = m;
            else l = m + 1;
        }
        cout << &apos;#&apos; << tc << &apos; &apos; << r << &apos;\n&apos;;
    }
    return 0;
}