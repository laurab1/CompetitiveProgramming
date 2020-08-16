#include <iostream>
#include <vector>
#include <set>

std::string is_magic(std::string num) {
    uint64_t n = num.size();
    std::set<std::string> magic({"1", "14", "144"});

    uint64_t i = 0;
    uint64_t j = 3;
    while(i < n) {
        if(i + j > n && j > 1)
            j--;
        auto sub = magic.find(num.substr(i, j));
        if(sub != magic.end()) {
            i += j;
            j = 3;
        } else {
            if(j > 1)
                j--;
            else
                return "NO";
        }
    }

    return "YES";
}

int main() {
    std::string num;
    std::cin >> num;
    std::cout << is_magic(num) << std::endl;

    return 0;
}