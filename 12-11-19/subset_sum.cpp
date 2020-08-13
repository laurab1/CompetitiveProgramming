#include <iostream>
#include <numeric>
#include <vector>

bool subset_sum(std::vector<uint64_t> vec) {
    uint64_t n = vec.size();
    uint64_t v = std::accumulate(vec.begin(), vec.end(), 0);

    if(v % 2 != 0)
        return false;

    v /= 2;
    bool matrix[n+1][v+1];
    for(uint64_t i = 0; i < v+1; i++)
        matrix[0][i] = false;
    for(uint64_t i = 0; i < n+1; i++)
        matrix[i][0] = true;
    for(uint64_t i = 1; i < n+1; i++)
        for(uint64_t j = 1; j < v+1; j++)
            if(j >= vec.at(i-1))
                matrix[i][j] = matrix[i-1][j] || matrix[i-1][j-vec.at(i-1)];
            else
                matrix[i][j] = matrix[i-1][j];

    return matrix[n][v];
}

int main() {
    uint64_t t, n;
    std::cin >> t;

    for(uint64_t i = 0; i < t; i++) {
        std::cin >> n;
        std::vector<uint64_t> vec(n);
        for(uint64_t j = 0; j < n; j++)
            std::cin >> vec.at(j);
        std::cout << (subset_sum(vec)?"YES":"NO") << std::endl;
    }

    return 0;
}