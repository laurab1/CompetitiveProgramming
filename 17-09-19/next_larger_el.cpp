#include <iostream>
#include <stack>
#include <vector>

typedef struct test_struct {
    int size; //size of the array
    std::vector<long> vec; //vector of integers
} test_t;

void next_larger_el(test_t test) {
    std::stack<long> st;
    int size = test.vec.size();
    std::vector<long> results(size); //array of results

    //reads the array from right to left
    for(int i = size-1; i>=0; i--) {
        while(!st.empty() && test.vec.at(i) >= st.top())
            st.pop();

        results.at(i) = st.empty()?-1:st.top();

        st.push(test.vec.at(i));
    }

    //prints the results
    for(auto it = results.begin(); it != results.end(); it++)
        std::cout << *it << " ";

    std::cout << std::endl;
}

int main() {
    int num_tests;
    std::cin >> num_tests;
    std::vector<test_t> tests(num_tests);
    for(auto it = tests.begin(); it != tests.end(); it++) {
        std::cin >> it->size;
        long num;
        for(int j=0; j<it->size; j++) {
            std::cin >> num;
            it->vec.push_back(num);
        }
    }

    for(auto it = tests.begin(); it != tests.end(); it++)
        next_larger_el(*it);

    return 0;
}
