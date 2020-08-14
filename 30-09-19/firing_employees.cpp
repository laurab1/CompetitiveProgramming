#include <iostream>
#include <vector>
#include <stack>
#include <math.h>


bool is_prime(long num) {
    for(long i=2; i<=sqrt(num); i++)
        if(num%i == 0)
            return false;
    return true;
}

void black_listed(std::vector<long> vec) {
    std::vector<std::vector<long>> pos(vec.size() + 1, std::vector<long>());
    for(long i=0; i<vec.size(); i++) {
        pos.at(vec.at(i)).push_back(i + 1);
    }
    
    std::stack<long> stack;
    std::vector<long> sen(vec.size() + 1, 0);
    stack.push(pos.at(0).front());
    for(long i=0; i<vec.size(); i++) {
        std::vector<long> tmp = pos[stack.top()];
        stack.pop();
        while(!tmp.empty()) {
            sen[tmp.back()] = 1 + sen[vec.at(tmp.back()-1)];
            stack.push(tmp.back());
            tmp.pop_back();
        }
    }
    
    long fired = 0;
    for(long i=0; i<vec.size()+1; i++)
        if(sen.at(i) && is_prime(sen.at(i) + i))
            fired += 1;

    std::cout << fired << std::endl;
}

int main() {
    long num_tests, n;
    std::cin >> num_tests;
    for(long i = 0; i < num_tests; i++) {
        std::cin >> n;
        std::vector<long> vec(n);
        for(long j = 0; j < n; j++) {
            std::cin >> vec.at(j);
        }
        black_listed(vec);
    }

    return 0;
}