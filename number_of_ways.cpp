#include <vector>
#include <iostream>

uint64_t num_ways(std::vector<uint64_t> test, uint64_t sum) {
    //if the reminder of sum / 3 is != 0, return 0
    if(sum % 3)
        return 0;

    sum /= 3;
    std::vector<int> aux(test.size());
    int tmp = 0;

    //count the number of suffixes of test which sum to "sum"
    for(int j = test.size() - 1; j >= 0; j--) {
        tmp += test.at(j);
        if(tmp == sum) {
            aux.at(j) = 1;
        } else 
            aux.at(j) = 0;
    }

    for(int j = test.size() - 2; j >= 0; j--) {
        aux.at(j) += aux.at(j+1);
    }

    uint64_t num_ways = 0;
    tmp = 0;

    //compute the sum of prefixes of test
    //if a prefix sums to "sum", add aux[i+2] to the result
    for(int j = 0; j < test.size() - 2; j++) {
        tmp += test.at(j);
        if(tmp == sum) {
            num_ways += aux.at(j+2);
        }
    }

    return num_ways;
}

int main() {
    int size;
    std::vector<uint64_t> test;
    std::cin >> size;
    test.reserve(size);
    int el;
    uint64_t sum = 0;

    while(size--) {
        std::cin >> el;
        test.push_back(el);
        sum += el;
    }
    
    std::cout << num_ways(test, sum) << std::endl;

    return 0;
}