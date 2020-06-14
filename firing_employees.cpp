#include <iostream>
#include <vector>
#include <stack>
#include <math.h>

typedef struct test_struct {
    int size;
    std::vector<int> vec;
} test_t;

bool is_prime(int num) {
    for(int i=2; i<=sqrt(num); i++)
        if(num%i == 0)
            return false;
    return true;
}

void black_listed(test_t test) {
    std::vector<std::vector<int>> pos;
    for(int i=0; i<test.vec.size()+1; i++) {
        pos.push_back(std::vector<int>(1, i+1));
    }
    
    std::stack<int> stack;
    std::vector<int> sen;
    for(int i=0; i<test.vec.size()+1; i++)
        sen.push_back(0);
    stack.push(pos.at(0).front());
    for(int i=0; i<test.vec.size(); i++) {
        std::vector<int> tmp = pos[stack.top()];
        std::cout << "ok" << std::endl;
        stack.pop();
        for(auto it = tmp.begin(); it != tmp.end(); it++) {
            sen[*it] = 1+ sen[test.vec.at(*it-1)];
            stack.push(*it);
        }
    }
    
    int fired = 0;
    for(int i=0; i<test.vec.size(); i++)
        if(sen.at(i) && is_prime(sen.at(i) + i))
            fired += 1;

    std::cout << fired << std::endl;
}

int main() {
    int num_tests;
    std::cin >> num_tests;
    std::vector<test_t> tests(num_tests);
    for(auto it = tests.begin(); it != tests.end(); it++) {
        std::cin >> it->size;
        long num;
        for(int j = 0; j < it->size; j++) {
            std::cin >> num;
            it->vec.push_back(num);
        }
    }

    for(auto it = tests.begin(); it != tests.end(); it++)
        black_listed(*it);

    return 0;
}