#include <iostream>
#include <deque>
using namespace std;

typedef struct test_struct {
    int size; //size of the array
    int subsize; //size of subarrays
    int* array; //array of integers
} test_t;

void sliding_window_max(test_t test) {
    deque<int> queue; //a queue of indexes - keeps the index of current maximum

    for(int i=0; i<test.size; i++) {
        while(!(queue.empty()) && (queue.front()<=i-test.subsize)) //removes elements which are not in the window
            queue.pop_front();
        while(!(queue.empty()) && (test.array[i]>=test.array[queue.back()])) //removes elements which are smaller than the current one
            queue.pop_back();
        //now inserts the current element
        queue.push_back(i);

        //prints the current maximum
        if (i>=test.subsize-1)
            cout << test.array[queue.front()] << " ";
    }

    cout << endl;
}

int main() {
    int t;
    cin >> t; //gets the number of test cases and create an array of tests
    test_t* tests = (test_t*) malloc(t*sizeof(test_t));
    for(int i=0; i<t; i++) {
        cin >> tests[i].size; //gets size of the array
        cin >> tests[i].subsize; //and size of the sliding window
        tests[i].array = (int*) malloc(tests[i].size*sizeof(int));
        for(int j=0; j<tests[i].size; j++)
            cin >> tests[i].array[j]; //gets the elements of the array
    }

    for(int i=0; i<t; i++) {
        sliding_window_max(tests[i]); //compute the sliding window maximums
        free(tests[i].array);
    }
    free(tests);

    return 0;
}
