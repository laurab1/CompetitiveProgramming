#include <iostream>
#include <vector>

typedef struct test {
    size_t size;
    std::vector<int> vec;
} test_t;

int main() {
    size_t num_tests = 0;
    std::cin >> num_tests;
    std::vector<test_t> tests(num_tests);
    std::vector<std::vector<int>> leaders(num_tests);
    int i=0;

    for(auto it = tests.begin(); it != tests.end(); it++) {
        std::cin >> it->size;
        int num = 0;
        for(int i=0; i<it->size; i++) {
            std::cin >> num;
            it->vec.push_back(num);        
        }
    }
    
    for(auto it = tests.begin(); it != tests.end(); it++) {
        int max = *it->vec.end();
        for(auto current = it->vec.rbegin(); current != it->vec.rend(); current++)
            if(*current >= max) {
                max = *current;
                leaders.at(i).push_back(max);
            }
        i++;
    }

    for(auto it = leaders.begin(); it != leaders.end(); it++) {
        for(auto j = it->rbegin(); j != it->rend(); j++)
            std::cout << *j << " ";
        std::cout << std::endl;
    }

    return 0;
}