#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct test_struct {
    size_t size;
    int* array;
} test_t;

//printleaders simply checks for the maximum starting from the end
//every time it finds a new maximum, prints it
void printleaders(test_t test) {
    int count = 1;
    int leaders[test.size];
    int max = test.array[test.size-1];
    leaders[0] = max;
    for(int i=test.size-2; i>=0; i--)
        if(test.array[i] > max) {
            max = test.array[i];
            leaders[count] = max;
            count++;
        }
    for(int i=count-1; i>=0; i--)
        cout << leaders[i] << " ";
    cout << endl;
}

int main() {

    int t = 0; //number of test cases, given by the user
    cin >> t;
    test_t* tests = (test_t*) malloc(t*sizeof(test_t)); //array of test objects
    for(int i=0; i<t; i++) {
        cin >> tests[i].size; //get the size for each test
        tests[i].array = (int*) malloc(tests[i].size*sizeof(int)); //create the array of integers for a given test
        for(int j=0; j<tests[i].size; j++)
            cin >> tests[i].array[j]; //get the integer values
    }
    for(int i=0; i<t; i++) {
        printleaders(tests[i]); //print leaders in the arrays
        free(tests[i].array);
    }
    free(tests);

    return 0;
}
