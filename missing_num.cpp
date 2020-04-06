#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct test_struct {
    int size;
    int* array;
} test_t;

//prints the missing element in a given array
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
    test_t* tests = (test_t*) malloc(t*sizeof(test_t)); //array of test objects
    for(int i=0; i<t; i++) {
        cin >> tests[i].size;
        tests[i].array = (int*) malloc((tests[i].size-1)*sizeof(int)); //each array contains size-1 integers
        for(int j=0; j<tests[i].size-1; j++)
            cin >> tests[i].array[j];
    }
    for(int i=0; i<t; i++) {
        print_missing(tests[i]);
        free(tests[i].array);
    }
    free(tests);

    return 0;
}
