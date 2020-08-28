#include <iostream>
#include <vector>
#include <algorithm>

int64_t lbs(std::vector<int64_t> vec) {
    int64_t n = vec.size();
    std::vector<int64_t> lisvec(n, 1);
    std::vector<int64_t> ldsvec(n, 1);

    for(int64_t i = 1; i < n; i++) {
        for(int64_t j = 0; j < i; j++)
            if(vec.at(i) > vec.at(j) and lisvec.at(i) < lisvec.at(j) + 1)
                lisvec.at(i) = lisvec.at(j) + 1;
    }

    std::reverse(vec.begin(), vec.end());

    for(int64_t i = 1; i < n; i++) {
        for(int64_t j = 0; j < i; j++)
            if(vec.at(i) > vec.at(j) and ldsvec.at(i) < ldsvec.at(j) + 1)
                ldsvec.at(i) = ldsvec.at(j) + 1;
    }

    std::reverse(ldsvec.begin(), ldsvec.end());

    int64_t max = lisvec.at(0) + ldsvec.at(0) - 1;
    for(int64_t i = 1; i < n; i++) {
        int64_t tmp = lisvec.at(i) + ldsvec.at(i) - 1;
        max = (tmp > max)? tmp: max;
    }
    return max;
}

int main() {
    int64_t t, n;
    std::cin >> t;
    for (int64_t i = 0; i < t; i++) {
        std::cin >> n;
        std::vector<int64_t> vec(n);
        for(int64_t j = 0; j < n; j++)
            std::cin >> vec.at(j);
        std::cout << lbs(vec) << std::endl;
    }
    return 0;
}