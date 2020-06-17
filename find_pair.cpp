#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

void find_pair(std::vector<int64_t> test, uint64_t k) {
    std::sort(test.begin(), test.end());
    uint64_t n = test.size();

    std::pair<int64_t, int64_t> pair(test.at(k/n), 0);

    uint64_t occ = std::count(test.begin(), test.end(), pair.first);
    auto it = std::find(test.begin(), test.end(), pair.first);
    uint64_t loc = it - test.begin();
    pair.second = test.at((k-loc*n)/occ);

    std::cout << pair.first << " " << pair.second << std::endl;
}

int main() {
    uint64_t size, k;

    std::cin >> size;
    std::cin >> k;
    std::vector<int64_t> test(size);

    for(int i = 0; i < size; i++) 
        std::cin >> test.at(i);

    find_pair(test, k-1);
}