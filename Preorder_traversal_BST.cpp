#include <vector>
#include <iostream>

//a single testcase
typedef struct test {
    int n; //length of the vector
    std::vector<int> vec; //vector of integers
} test_t;

int main() {

    int t = 0;
    std::cin >> t;
    std::vector<test_t> tests(t);
    for(int i=0; i<t; i++) {
        std::cin >> tests.at(i).n;  
        for(int j=0; j<(tests.at(i).n); j++) {
            int el = 0;
            std::cin >> el;
            tests.at(i).vec.push_back(el);
        }
    }

}