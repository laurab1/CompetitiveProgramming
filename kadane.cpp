#include <iostream>
#include <vector>

typedef struct test {
    int size;
    std::vector<int> vec;
} test_t;

void kadane(test_t test) {
    int sum = test.vec.front();
    int max = test.vec.front();

    for(auto it = test.vec.begin()+1; it != test.vec.end(); it++) {
        //if sum is positive, then add next element to it
        //else restart from current element
        sum = sum>=0?(sum+*it):*it;
        max = sum>=max?sum:max;
    }

    std::cout << max << std::endl;
}

int main() {
    int num_tests;
    std::cin >> num_tests; //gets number of test cases
    std::vector<test_t> tests(num_tests);
    //gets test cases: size of arrays and arrays' elements
    for(auto it = tests.begin(); it != tests.end(); it++) {
        std::cin >> it->size;
        int el;
        for(int i=0; i<it->size; i++) {
            std::cin >> el;
            it->vec.push_back(el);
        }
    }
    //for each array, performs kadane's algo
    for(auto it = tests.begin(); it != tests.end(); it++) {
        kadane(*it);
    }

    return 0;
}
