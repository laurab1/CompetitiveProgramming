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
    std::vector<std::vector<int>> pos(test.vec.size() + 1, std::vector<int>());
    for(int i=0; i<test.vec.size()+1; i++) {
        pos.at(test.vec.at(i)).push_back(i + 1);
    }
    
    std::stack<int> stack;
    std::vector<int> sen(test.vec.size() + 1, 0);
    stack.push(pos.at(0).front());
    for(int i=0; i<test.vec.size(); i++) {
        std::vector<int> tmp = pos[stack.top()];
        std::cout << "bla" << std::endl;
        stack.pop();
        while(!tmp.empty()) {
            sen[tmp.back()] = 1 + sen[test.vec.at(tmp.back()-1)];
            stack.push(tmp.back());
            tmp.pop_back();
        }
        std::cout << "bla bla" << std::endl;
    }
    std::cout << "bla bla bla" << std::endl;
    
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