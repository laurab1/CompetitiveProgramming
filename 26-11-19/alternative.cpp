#include <iostream>
#include <vector>

uint64_t las(std::vector<int8_t> bits) {
    uint64_t n = bits.size();
    uint64_t length = 1;
    uint64_t new_length = 1;
    
    for(uint64_t i = 1; i < n; i++) {
        if(bits.at(i-1) != bits.at(i))
            new_length++;
        else {
            length = new_length > length? new_length: length;
        }
    }
    length = new_length > length? new_length: length;

    return length;
}

int main() {
    uint64_t n;
    std::cin >> n;
    std::vector<int8_t> bits(n);

    for(uint64_t i = 0; i < n; i++)
        std::cin >> bits.at(i);

    uint64_t seq_len = las(bits);
    std::cout << std::min(seq_len + 2, n) << std::endl;

    return 0;
}