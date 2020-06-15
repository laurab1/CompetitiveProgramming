#include <vector>
#include <iostream>

int num_ways(std::vector<long> test, long sum) {
    if(sum % 3)
        return 0;

    sum /= 3;
    std::vector<long> aux(test.size());
    
    return 0;
}

int main() {
    int num_tests;
    std::cin >> num_tests;
    int size;
    std::vector<long> test;
    for(int i = 0; i < num_tests; i++) {
        std::cin >> size;
        test.reserve(size);
        int el;
        int sum = 0;
        for(int j = 0; j < size; j++) {
            std::cin >> el;
            test.push_back(el);
            sum += el;
        }
        std::cout << num_ways(test, sum) << std::endl;
        test.clear();
    }

    return 0;
}