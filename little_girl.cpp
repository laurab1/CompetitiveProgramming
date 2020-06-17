#include <iostream>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>

int64_t maximum_sum(std::vector<int64_t> vec, std::vector<std::pair<size_t, size_t>> queries) {
    std::vector<int64_t> freq(vec.size() + 1, 0);
    std::vector<int64_t> sums(vec.size(), 0);
    int64_t sum = 0;

    for(auto it = queries.begin(); it != queries.end(); it++) {
        freq.at(it->first) += 1;
        freq.at(it->second + 1) -= 1;
    }

    std::partial_sum(freq.begin(), freq.end(), sums.begin());
    std::sort(vec.begin(), vec.end());
    std::sort(sums.begin(), sums.end());

    for(int i = 0; i < vec.size(); i++)
        sum += vec.at(i) * sums.at(i);

    return sum;
}

int main() {
    int64_t size, num_queries, el;
    size_t left, right;

    std::cin >> size;
    std::cin >> num_queries;

    std::vector<std::pair<size_t, size_t>> queries(num_queries);
    std::vector<int64_t> test(size);
    
    for(int i = 0; i < size; i++)
        std::cin >> test.at(i);

    for(int i = 0; i < num_queries; i++) {
        std::cin >> left;
        std::cin >> right;
        queries.at(i) = std::pair<size_t, size_t>(left-1, right-1);
    }

    std::cout << maximum_sum(test, queries) << std::endl;

    return 0;
}