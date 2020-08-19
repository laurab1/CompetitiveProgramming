#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>

using int_pair = std::pair<uint64_t, uint64_t>;

uint64_t woodcutters(std::vector<int_pair> vec) {
    uint64_t n = vec.size();
    std::vector<uint64_t> diff(n-1);
    std::vector<uint8_t> cut(n, 0);
    cut.at(0) = 1;
    cut.back() = 1;
    
    for(uint64_t i = 0; i < n-1; i++) {
        diff.at(i) = vec.at(i+1).first - vec.at(i).first;
    }

    for(uint64_t i = 1; i < n-1; i++)
        if(vec.at(i).second < diff.at(i-1))
            cut.at(i) = 1;
        else {
            if(vec.at(i).second < diff.at(i)) {
                cut.at(i) = 1;
                diff.at(i) -= vec.at(i).second;
            }
        }

    return std::accumulate(cut.begin(), cut.end(), 0);
}

int main() {
    uint64_t n;
    std::cin >> n;
    std::vector<int_pair> vec(n);

    for(uint64_t i = 0; i < n; i++)
        std::cin >> vec.at(i).first >> vec.at(i).second;

    std::cout << woodcutters(vec) << std::endl;
    return 0;
}