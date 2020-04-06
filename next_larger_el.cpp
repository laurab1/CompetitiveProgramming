#include <iostream>
#include <stack>
using namespace std;

typedef struct test_struct {
    int size; //size of the array
    int* array; //array of integers
} test_t;

void next_larger_el(test_t test) {
    //not exactly like sliding window max: uses a stack instead
    stack<int> st;
    int a[test.size]; //array of results
    int j = test.size-1;

    //initialise the array of results to -1
    for(int i=0; i<test.size; i++)
        a[i] = -1;

    //reads the array from right to left
    for(int i=test.size-1; i>=0; i--) {
        while(!st.empty()) {
            //if there is at least an element on the stack, checks if it's
            //greater than the current element. If it is, inserts it in a.
            if(st.top()>test.array[i]) {
                a[i] = st.top();
                break;
            }
            //stack top is not greater than the larger element, I can remove it
            st.pop();
        }
        //inserts the current element on the stack
        st.push(test.array[i]);
    }

    //prints the results
    for(int i=0; i<test.size; i++)
        cout << a[i] << " ";

    cout << endl;
}

int main() {
    int t;
    cin >> t; //gets the number of test cases and create an array of tests
    test_t* tests = (test_t*) malloc(t*sizeof(test_t));
    for(int i=0; i<t; i++) {
        cin >> tests[i].size; //gets size of the array
        tests[i].array = (int*) malloc(tests[i].size*sizeof(int));
        for(int j=0; j<tests[i].size; j++)
            cin >> tests[i].array[j]; //gets the elements of the array
    }

    for(int i=0; i<t; i++) {
        next_larger_el(tests[i]); //compute the sliding window maximums
        free(tests[i].array);
    }
    free(tests);

    return 0;
}
