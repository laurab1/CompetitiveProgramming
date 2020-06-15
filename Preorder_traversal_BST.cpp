#include <vector>
#include <stack>
#include <iostream>

int check_preorder(std::vector<int> vec) {
    std::stack<int> s;
    int root = INT32_MIN;

    for(auto it = vec.begin(); it != vec.end(); it++) {
        if(*it < root) 
            return 0;
        while(!s.empty() && s.top() < *it) {
            root = s.top();
            s.pop();
        }
        s.push(*it);
    }
    return 1;        
}

int main() {
    int num_tests;
    std::cin >> num_tests;
    std::vector<int> test;
    int size;
    for(int i = 0; i < num_tests; i++) {
        std::cin >> size;
        test.reserve(size);
        int el;
        for(int j = 0; j < size; j++) {
            std::cin >> el;
            test.push_back(el);
        }
        std::cout << check_preorder(test) << std::endl;
        test.clear();
    }
}