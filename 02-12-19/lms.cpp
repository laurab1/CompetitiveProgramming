#include <iostream>
#include <iterator>
#include <vector>

char in;

template <class InputIterator, class Compare, class T = typename std::iterator_traits<InputIterator>::value_type>
std::vector<T> lms(InputIterator first, InputIterator last, Compare comp) {
    std::vector<T> res;
    auto max = last;

    for(auto it = last - 1; it != first - 1; it--) {
        if(comp(*it, *max)) {
            res.push_back(*it);
            max = it;
        }
    }

    return res;
}

int main() {
    std::string str;
    std::cin >> str;
    auto res = lms(str.begin(), str.end(), [](const char a, const char b){
        return a >= b;
    });

    for(auto it = res.rbegin(); it != res.rend(); it++)
        std::cout << *it;
    std::cout << std::endl;

    return 0;
}