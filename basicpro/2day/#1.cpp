#include<iostream>
#include<list>
 
#define endl "\n"
using namespace std;
 
int origin_i;
int pw;
 
list<int> List;
 
void Initialize() {
    List.clear();
}
 
void Input() {
    cin >> origin_i;
    for (int i = 0; i < origin_i; i++) {
        int a; 
        cin >> a;
        List.push_back(a);
    }
    
    cin >> pw;
    for (int i = 0; i < pw; i++){
        char c; 
        cin >> c;
        if (c == 'I') {
            int Post; 
            cin >> Post;
            int N; 
            cin >> N;
            
            list<int> PW;
            for (int j = 0; j < N; j++) {
                int a; cin >> a;
                PW.push_back(a);
            }
 
            list<int>::iterator Iter = List.begin();
            
            for (int i = 0; i < Post; i++) Iter++;
            List.splice(Iter, PW);
        }
        else if(c == 'D') {
            int Post; 
            cin >> Post;
            int N; 
            cin >> N;
            list<int>::iterator Start = List.begin();
            list<int>::iterator End;
            
            for (int i = 0; i < Post; i++) Start++;
            End = Start;
            for (int i = 0; i < N; i++) End++;
            List.erase(Start, End);
        }
        else {
            int Cnt; 
            cin >> Cnt;
            
            for (int i = 0; i < Cnt; i++) {
                int a; 
                cin >> a;
                List.push_back(a);
            }
        }
    }
}
 
void Solve() {
    int Tc = 10;
    for (int T = 1; T <= Tc; T++){
        Initialize();
        Input();
        cout << "#" << T << " ";
        for (int i = 0; i < 10; i++) {
            cout << List.front() << " ";
            List.pop_front();
        }
        cout << endl;
    }
}
 
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Solve();
    return 0;
}