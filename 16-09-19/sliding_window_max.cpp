#include <iostream>
#include <deque>
#include <vector>

typedef struct test_struct {
    int size; //size of the array
    int subsize; //size of subarrays
    std::vector<int> vec; //array of integers
} test_t;

void sliding_window_max(test_t test) {
    std::deque<int> queue; //a queue of indexes - keeps the index of current maximum

    for(int i=0; i<test.size; i++) {
        while(!(queue.empty()) && (queue.front()<=i-test.subsize)) //removes elements which are not in the window
            queue.pop_front();
        while(!(queue.empty()) && (test.vec.at(i)>=test.vec.at(queue.back()))) //removes elements which are smaller than the current one
            queue.pop_back();
        //now inserts the current element
        queue.push_back(i);

        //prints the current maximum
        if (i>=test.subsize-1)
            std::cout << test.vec.at(queue.front()) << " ";
    }

    std::cout << std::endl;
}

int main() {
    int num_tests;
    std::cin >> num_tests; //gets the number of test cases and create an array of tests
    std::vector<test_t> tests(num_tests);
    for(auto it = tests.begin(); it != tests.end(); it++) {
        std::cin >> it->size; //gets size of the array
        std::cin >> it->subsize; //and size of the sliding window
        int num;
        for(int j=0; j<it->size; j++) {
            std::cin >> num; //gets the elements of the array
            it->vec.push_back(num);
        }
    }

    for(auto it = tests.begin(); it != tests.end(); it++)
        sliding_window_max(*it); //compute the sliding window maximums

    return 0;
}
