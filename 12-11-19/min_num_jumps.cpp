#include <iostream>
#include <vector>

int64_t min_jumps(std::vector<int64_t> vec) {
    if(!vec.at(0))
        return -1;
    if(vec.size() < 2)
        return 0;

    int64_t jump;
    int64_t next = jump = vec.at(0);
    int64_t num_jumps = 1;

    for(auto it = vec.begin() + 1; it != vec.end(); it++) {
        int64_t k = (it - vec.begin());
        
        if(it == vec.end() - 1)
            return num_jumps;
        next = std::max(next, *it + k);
        if(k >= next)
                return -1;
        jump--;
        if(!jump) {
            num_jumps++;
            jump = next - k;        
        }
    }

    return -1;
}

int main() {
    int64_t t, n;
    std::cin >> t;

    for(int64_t i = 0; i < t; i++) {
        std::cin >> n;
        std::vector<int64_t> vec(n);

        for(int64_t j = 0; j < n; j++)
            std::cin >> vec.at(j);

        std::cout << min_jumps(vec) << std::endl;
    }
}