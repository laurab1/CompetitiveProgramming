#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct test_struct {
    int size;
    int* array;
} test_t;

void print_missing(test_t test) {
    int array_sum = 0;
    int sum = 0;
    for(int i=0; i<test.size-1; i++)
        array_sum = array_sum + test.array[i];
    sum = (test.size*(test.size+1))/2;
    cout << sum - array_sum << endl;
}

int main() {
    int t = 0; //number of test cases
    cin >> t;
    test_t* tests = (test_t*) malloc(t*sizeof(test_t));
    for(int i=0; i<t; i++) {
        cin >> tests[i].size;
        tests[i].array = (int*) malloc((tests[i].size-1)*sizeof(int));
        for(int j=0; j<tests[i].size-1; j++)
            cin >> tests[i].array[j];
    }
    for(int i=0; i<t; i++)
        print_missing(tests[i]);

    return 0;
}
