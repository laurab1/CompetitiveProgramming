#include <iostream>
#include <vector>
#include <algorithm>

uint64_t lcs_length(std::string s1, std::string s2) {
    uint64_t rows = s1.size() + 1;
    uint64_t columns = s2.size() + 1;

    uint64_t matrix[rows][columns];
    for(uint64_t i = 0; i < rows; i++)
        matrix[i][0] = 0;
    for(uint64_t j = 0; j < columns; j++)
        matrix[0][j] = 0;

    for(uint64_t i = 1; i < rows; i++)
        for(uint64_t j = 1; j < columns; j++)
            if(s1.at(i-1) == s2.at(j-1))
                matrix[i][j] = matrix[i-1][j-1] + 1;
            else
                matrix[i][j] = std::max(matrix[i-1][j], matrix[i][j-1]);

    return matrix[rows-1][columns-1];
}

int main() {
    uint64_t t;
    std::cin >> t;
    for(uint64_t i = 0; i < t; i++) {
        std::string s1;
        std::cin >> s1;
        std::string s2(s1.size(), ' ');
        std::reverse_copy(s1.begin(), s1.end(), s2.begin());
        std::cout << lcs_length(s1, s2) << std::endl;
    }
    return 0;
}