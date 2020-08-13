#include <iostream>
#include <vector>
#include <utility>

using item = std::pair<uint64_t, uint64_t>;

uint64_t knapsack(std::vector<item> items, uint64_t cap) {
    uint64_t n = items.size();
    uint64_t matrix[n+1][cap+1];

    for(uint64_t i = 0; i < n + 1; i++)
        matrix[i][0] = 0;
    for(uint64_t i = 1; i < cap + 1; i++)
        matrix[0][i] = 0;
    for(uint64_t i = 1; i < n + 1; i++)
        for(uint64_t j = 1; j < cap + 1; j++)
            if(items.at(i-1).first <= j)
                matrix[i][j] = std::max(matrix[i-1][j], 
                                        matrix[i-1][j-items.at(i-1).first]+items.at(i-1).second);
            else
                matrix[i][j] = matrix[i-1][j];

    return matrix[n][cap];
}

int main() {
    uint64_t cap, n;

    std::cin >> cap >> n;
    std::vector<item> items(n);

    for(uint64_t i = 0; i < n; i++)
        std::cin >> items.at(i).first >> items.at(i).second;
    std::cout << knapsack(items, cap) << std::endl;

    return 0;
}