#include <iostream>
using namespace std;

typedef struct test_struct {
    int size;
    int* array;
} test_t;

void kadane(test_t test) {
    int sum = 0;
    int max = test.array[0];

    for(int i=0; i<test.size; i++) {
        //if sum is positive, then add next element to it
        //else restart from current element
        sum = sum>0?(sum+test.array[i]):test.array[i];
        max = sum>max?sum:max;
    }

    cout << max << endl;
}

int main() {
    int t;
    cin >> t; //gets number of test cases
    test_t* tests = (test_t*) malloc(t*sizeof(test_t));
    //gets test cases: size of arrays and arrays' elements
    for(int i=0; i<t; i++) {
        cin >> tests[i].size;
        tests[i].array = (int*) malloc(tests[i].size*sizeof(int));
        for(int j=0; j<tests[i].size; j++)
            cin >> tests[i].array[j];
    }
    //for each array, performs kadane's algo
    for(int i=0; i<t; i++) {
        kadane(tests[i]);
        free(tests[i].array);
    }
    free(tests);

    return 0;
}
