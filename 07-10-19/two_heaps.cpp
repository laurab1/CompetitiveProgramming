#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <utility>

template<typename T, typename Compare>
void two_heaps(std::vector<std::pair<T,int64_t>> vec, Compare compare) {
    std::vector<int64_t> heaps(vec.size());
    std::pair<int64_t, int64_t> heaps_dim(0,0);
    int64_t f, s;
    std::tie(f, s) = heaps_dim;
    bool first = true;

    std::sort(vec.begin(), vec.end(), compare);

    for(int64_t i = 0; i < vec.size()-1; i++) {
        if(vec.at(i).first == vec.at(i+1).first) {
            if(first) {
                heaps.at(vec.at(i).second) = 1;
                heaps.at(vec.at(i+1).second) = 2;
                f++; s++;
                first = false;
            }
            continue;
        }
        if(first) {
            heaps.at(vec.at(i).second) = (f > s)? 2 : 1;
            (heaps.at(vec.at(i).second) == 1) ? f++ : s++; 
        }
        first = true;
    }

    if(first and vec.back().second != vec.back().second - 1) {
        heaps.at(vec.back().second) = (f > s)? 2 : 1;
        (heaps.at(vec.back().second) == 1) ? f++ : s++; 
    }

    std::cout << f*s << std::endl;

    for(auto it = heaps.begin(); it != heaps.end(); it++) {
        if(!*it) {
            *it = (f > s) ? 2 : 1;
            (*it == 1) ? f++ : s++;
        }
        std::cout << *it << " ";
    }

    std::cout << std::endl;

}

int main() {
    int64_t n;
    std::cin >> n;
    n *= 2;
    std::vector<std::pair<int64_t, int64_t>> test(n);
    
    for(int64_t i = 0; i < n; i++){
        std::cin >> test.at(i).first;
        test.at(i).second = i;
    }

    struct {
        bool operator()(std::pair<int64_t, int64_t> a, std::pair<int64_t, int64_t> b) const {   
            return a.first > b.first;
        }   
    } comp;

    two_heaps(test, comp);

    return 0;
}