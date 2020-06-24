#include <iostream>
#include <vector>

void leaders(int* vec, int size) {
    std::vector<int> leaders;
    int max = vec[size-1];
    leaders.push_back(max);
    for(int i = size-2; i >= 0; i--)
        if(vec[i] >= max) {
            max = vec[i];
            leaders.push_back(max);
        }

    for(auto it = leaders.rbegin(); it != leaders.rend(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

int main() {
    size_t num_tests = 0;
    std::cin >> num_tests;
    int size = 0;

    for(int i = 0; i < num_tests; i++) {
        std::cin >> size;
        int test[size];
        int num = 0;
        for(int i=0; i < size; i++) {
            std::cin >> test[i];
        }
        leaders(test, size);
    }

    return 0;
}