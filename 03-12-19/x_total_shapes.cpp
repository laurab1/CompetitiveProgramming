#include <iostream>
#include <vector>

using matrix = std::vector<std::string>;

void dfs(matrix &mat, int64_t i, int64_t j) {
    if(i < 0 or j < 0 or i >= mat.size() or j >= mat.at(0).size())
        return;
    if(mat.at(i).at(j) == 'O')
        return;

    mat.at(i).at(j) = 'O';
    for(int64_t a = -1; a <= 1; a++)
        for(int64_t b = -1; b <= 1; b++)
            if(abs(a-b) == 1)
                dfs(mat, i + a, j + b);
}

int64_t x_shapes(matrix mat) {
    int64_t n = mat.size();
    int64_t m = mat.at(0).size();
    int64_t count = 0;

    for(int64_t i = 0; i < n; i++)
        for(int64_t j = 0; j < m; j++)
            if(mat.at(i).at(j) == 'X') {
                count++;
                dfs(mat, i, j);
            }
    return count;
}

int main() {
    int64_t t, n, m;
    std::cin >> t;

    for(int64_t i = 0; i < t; i++) {
        std::cin >> n >> m;
        matrix mat(n, std::string(m, 'O'));
        for(int64_t j = 0; j < n; j++)
            std::cin >> mat.at(j); 
        std::cout << x_shapes(mat) << std::endl;
    }

    return 0;
}