#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

int N; int room[401] = {0};
int now_room; int next_room;
int now_check; int next_check;
int cnt = 0;
int main(int argc, char** argv) {
	int test_case;
	int T;
	std::cin >> T;
	for(test_case = 1; test_case <= T; ++test_case) {
		memset(room, 0 , sizeof(room));
        std::cin>>N;
        for(int i = 0; i < N; i++){
            std::cin >> now_room;
            std::cin >> next_room;
            if(now_room > next_room){
				swap(now_room, next_room);
            }
            if((now_room % 2) == 0) now_room--;
            if((next_room % 2) == 1) next_room++;
            for(int j = now_room; j <= next_room; j++){
             room[j]++;   
            }
        }
        cnt = *max_element(room, room+401);
        std::cout << "#" << test_case << " " << cnt << endl;
	}
	return 0;
}