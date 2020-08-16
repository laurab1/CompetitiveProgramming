#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

using int_tuple = std::tuple<uint64_t, uint64_t, uint64_t>;

std::vector<uint64_t> max_n_meetings(std::vector<int_tuple> vec) {
    uint64_t n = vec.size();
    std::vector<uint64_t> results;

    std::sort(vec.begin(), vec.end(), [](const int_tuple a, const int_tuple b) {
        return std::get<1>(a) < std::get<1>(b);
    });

    results.push_back(std::get<2>(vec.at(0))); 

    uint64_t i = 0;
    for(uint64_t j = 1; j < n; j++)
        if(std::get<1>(vec.at(i)) <= std::get<0>(vec.at(j))) {
            results.push_back(std::get<2>(vec.at(j)));
            i = j;
        }
    return results;
}

int main() {
    uint64_t t, n;
    std::cin >> t;

    for(uint64_t i = 0; i < t; i++) {
        std::cin >> n;
        std::vector<int_tuple> vec(n);

        for(uint64_t j = 0; j < n; j++)
            std::cin >> std::get<0>(vec.at(j));
        for(uint64_t j = 0; j < n; j++) {
            std::cin >> std::get<1>(vec.at(j));
            std::get<2>(vec.at(j)) = j + 1;
        }
        
        std::vector<uint64_t> res = max_n_meetings(vec);
        for(uint64_t j = 0; j < res.size(); j++)
            std::cout << res.at(j) << " ";
        std::cout << std::endl;
    }

    return 0;
}