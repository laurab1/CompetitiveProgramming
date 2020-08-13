#include <iostream>
#include <vector>

typedef struct test_struct {
    int size;
    std::vector<int> vec;
} test_t;

//prints the missing element in a given array
void print_missing(test_t test) {
    int vec_sum = test.vec.front();
    int sum = 0;
    for(auto it = test.vec.begin()+1; it != test.vec.end(); it++)
        vec_sum = vec_sum + *it;
    sum = ((test.size+2)*(test.size+1))/2;
    std::cout << sum - vec_sum << std::endl;
}

int main() {
    int num_tests = 0; //number of test cases
    std::cin >> num_tests;
    std::vector<test_t> tests(num_tests);
    for(auto it = tests.begin(); it != tests.end(); it++) {
        std::cin >> it->size;
        it->size--;
        int el;
        for(int i=0; i<it->size; i++) {
            std::cin >> el;
            it->vec.push_back(el);
        }
    }
    for(auto it = tests.begin(); it != tests.end(); it++) 
        print_missing(*it);

    return 0;
}
