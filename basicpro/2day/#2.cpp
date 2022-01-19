#include<iostream>

using namespace std;
void ez_exchange(long money) {
    constexpr int arr[] {50000,10000,5000,1000,500,100,50,10};
    for (int a : arr) {
        std::cout << money / a;
        if (a != 10) {
            std::cout << ' ';
        }
        money %= a;
    }
    std::cout << '\n';
}

int main(int argc, char** argv){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
	int test_case;
	int T;
	std::cin >> T;
	for(int test_case{1}; test_case <= T; ++test_case) {
        long money;
        std::cin >> money;
        std::cout << '#' << test_case << '\n';
        ez_exchange(money);
	}
	return 0;
}