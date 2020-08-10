#include <iostream>
#include <vector>
#include <algorithm>

uint64_t edit_distance(std::vector<char> s1, std::vector<char> s2) {
    uint64_t p = s1.size();
    uint64_t q = s2.size();
    uint64_t matrix[p+1][q+1];

    for(uint64_t i = 0; i < p+1; i++)
        matrix[i][0] = i;
    for(uint64_t i = 0; i < q+1; i++)
        matrix[0][i] = i;
    for(uint64_t i = 1; i < p+1; i++)
        for(uint64_t j = 1; j < q+1; j++)
            if(s1.at(i-1) == s2.at(j-1))
                matrix[i][j] = matrix[i-1][j-1];
            else
                matrix[i][j] = 1 + std::min(std::initializer_list<uint64_t>({matrix[i-1][j], 
                                                                             matrix[i][j-1], 
                                                                             matrix[i-1][j-1]}));

    return matrix[p][q];
}

int main() {
    uint64_t t, p, q;
    std::cin >> t;

    for(uint64_t i = 0; i < t; i++) {
        std::cin >> p >> q;
        std::vector<char> s1(p);
        std::vector<char> s2(q);
        for(uint64_t j = 0; j < p; j++)
            std::cin >> s1.at(j);
        for(uint64_t j = 0; j < q; j++)
            std::cin >> s2.at(j);
        std::cout << edit_distance(s1, s2) << std::endl;
    }
    
}