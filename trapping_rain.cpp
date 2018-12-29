#include <iostream>
using namespace std;

typedef struct test_struct {
    int size;
    int* array;
} test_t;

void trapping_rain(test_t test) {
    int trapped = 0; //how much water has been trapped
    int leftwall = test.array[0];
    int lidx = 0; //index of leftwall
    int rightwall = test.array[test.size-1];
    int ridx = test.size-1; //index of rightwall
    int waterlevel = 0; //the minimum between rigthwall and leftwall

    //first checks for the leftwall among the elements on the left of rightwall
    for(int i=0; i<ridx; i++)
        if(leftwall <= test.array[i]) {
            leftwall = test.array[i];
            lidx = i;
        }
    //then checks for the rigthwall among the elements on the right of leftwall
    for(int i=test.size-1; i>lidx; i--)
        if(rightwall <= test.array[i]) {
            rightwall = test.array[i];
            ridx = i;
        }

    //computes the minimum
    waterlevel = (leftwall<rightwall)?leftwall:rightwall;
    
    //computes trapped and prints it
    for(int i=lidx+1; i<ridx; i++)
        trapped += (waterlevel-test.array[i]);

    cout << trapped << endl;
}

int main() {
    int t = 0; //number of tests, given by the user
    cin >> t;
    test_t* tests = (test_t*) malloc(t*sizeof(test_t));
    for(int i=0; i<t; i++) {
        cin >> tests[i].size; //for each test, gets array's size and elements
        tests[i].array = (int*) malloc(tests[i].size*sizeof(int));
        for(int j=0; j<tests[i].size; j++)
            cin >> tests[i].array[j];
    }

    //computes trapped water
    for(int i=0; i<t; i++) {
        trapping_rain(tests[i]);
        free(tests[i].array);
    }
    free(tests);

    return 0;
}
