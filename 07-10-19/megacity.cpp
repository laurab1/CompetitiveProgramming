#include <iostream>
#include <vector>
#include <tuple>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <numeric>
#define GOAL 1000000
using ddouble = long double;

std::pair<ddouble, int64_t> pair_sum(std::pair<ddouble, int64_t> a, std::pair<ddouble, int64_t> b) {
    return std::pair<ddouble, int64_t>(b.first, a.second + b.second);
}

std::vector<std::pair<ddouble, int64_t>> find_radius(std::vector<std::tuple<int64_t, int64_t, int64_t>> vec) {
    std::vector<std::pair<ddouble, int64_t>> radius(vec.size());
    int64_t x, y, k;
    for(int i = 0; i < vec.size(); i++) {
        std::tie(x, y, k) = vec.at(i);
        radius.at(i).first = sqrt(pow(x, 2) + pow(y, 2));
        radius.at(i).second = k;
    }
    return radius;
}

ddouble megacity(std::vector<std::tuple<int64_t, int64_t, int64_t>> vec, int64_t s) {
    std::vector<std::pair<ddouble, int64_t>> rads = find_radius(vec);
    std::vector<std::pair<ddouble, int64_t>> res(vec.size());

    struct {
        bool operator()(std::pair<ddouble, int64_t> a, std::pair<ddouble, int64_t> b) const {
            return a.first < b.first;
        }   
    } comp;

    std::sort(rads.begin(), rads.end(), comp);
    std::partial_sum(rads.begin(), rads.end(), res.begin(), pair_sum);

    for(auto it = res.begin(); it != res.end(); it++) {
        if(it->second + s >= GOAL)
            return it->first;
    }

    return -1;
}

int main() {
    int64_t n, s;
    std::cin >> n >> s;
    int64_t x, y, k;
    std::vector<std::tuple<int64_t, int64_t, int64_t>> vec(n);
    for(int i = 0; i < n; i++) {
        std::cin >> x >> y >> k;
        x = abs(x);
        y = abs(y);
        vec.at(i) = std::make_tuple(x, y, k);
    }
    std::cout.precision(8);
    std::cout << megacity(vec, s) << std::endl;

    return 0;
}