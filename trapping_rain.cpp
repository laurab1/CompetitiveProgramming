#include <iostream>
#include <vector>

typedef struct test_struct {
    int size;
    std::vector<int> vec;
} test_t;

void trapping_rain(test_t test) {
    int trapped = 0; //how much water has been trapped
    auto lidx = test.vec.begin(); //index of leftwall
    auto ridx = test.vec.end()-1; //index of rightwall
    int waterlevel = 0; //the minimum between rigthwall and leftwall

    while(lidx != ridx) {
        if(*lidx <= *ridx) {
            if(waterlevel < *lidx) {
                waterlevel = *lidx;
            }
            trapped += waterlevel - *lidx;
            lidx++;
        } else {
            if(waterlevel < *ridx) {
                waterlevel = *ridx;
            }
            trapped += waterlevel - *ridx;
            ridx--;
        }
    }
    
    std::cout << trapped << std::endl;
}

int main() {
    int num_tests = 0; //number of tests, given by the user
    std::cin >> num_tests;
    std::vector<test_t> tests(num_tests);

    for(auto it = tests.begin(); it != tests.end(); it++) {
        std::cin >> it->size; //for each test, gets array's size and elements
        int num;
        for(int j=0; j<it->size; j++) {
            std::cin >> num;
            it->vec.push_back(num);
        }
    }

    //computes trapped water
    for(auto it = tests.begin(); it != tests.end(); it++)
        trapping_rain(*it);

    return 0;
}