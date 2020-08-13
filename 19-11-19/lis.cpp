#include <iostream>
#include <vector>

uint64_t lis(std::vector<uint64_t> vec) {
    uint64_t n = vec.size();
    std::vector<uint64_t> m(n+1, 0);
    uint64_t length = 0;
    uint64_t tmp_lenght = 0;

    m.at(1) = vec.at(0);
    for(uint64_t i = 0; i < n; i++) {
        uint64_t low = 1;
        uint64_t high = length;

        while(low <= high) {
            uint64_t mid = low + (high - low)/2;
            if(vec.at(m.at(mid)) >= vec.at(i))
                high = mid - 1;
            else
                low = mid + 1;
        }

        tmp_lenght = low;

        m.at(tmp_lenght) = i;

        length = tmp_lenght>length? tmp_lenght: length;
    }

    return length;
}

int main() {
    uint64_t t, n;
    std::cin >> t;
    for(uint64_t i = 0; i < t; i++) {
        std::cin >> n;
        std::vector<uint64_t> vec(n);
        for (uint64_t j = 0; j < n; j++)
            std::cin >> vec.at(j);
        std::cout << lis(vec) << std::endl;
    }
}