#include <iostream>
#include <vector>
#include <tuple>
#include <numeric>

std::pair<int64_t, int64_t> consumed_bars(std::vector<int64_t> bars) {
    int64_t a = 0;
    int64_t b = 0;
    std::vector<int64_t> sums(bars.size(), 0);

    std::partial_sum(bars.begin(), bars.end(), sums.begin());

    int64_t sum = 0;
    int64_t tot_time = sums.back();
    int64_t partial_sum = 0;

    while(a < bars.size() and partial_sum < tot_time) {
        tot_time -= bars.at(a);
        partial_sum += bars.at(a);
        a++;
    }

    if(a != 0 and tot_time < partial_sum - bars.at(a-1))
        a--;

    b = bars.size() - a;

    return std::pair<int64_t, int64_t>(a, b); 
}

int main() {
    int64_t n, a, b;
    std::cin >> n;
    std::vector<int64_t> bars(n);
    for(int64_t i = 0; i < n; i++)
        std::cin >> bars.at(i);
    std::tie(a, b) = consumed_bars(bars);
    std::cout << a << " " << b << std::endl;

    return 0;
}