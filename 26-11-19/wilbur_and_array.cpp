#include <iostream>
#include <vector>
#include <cstdlib>

int main() {
    uint64_t n;
    std::cin >> n;
    std::vector<uint64_t> b(n);

    for(uint64_t i = 0; i < n; i++)
        std::cin >> b.at(i);

    uint64_t first = 0;
    uint64_t sum = 0;
    
    for(auto el : b) {
        if(el != first) {
            sum += abs(first - el);
            first = el;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}