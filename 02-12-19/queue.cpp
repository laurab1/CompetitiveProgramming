#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#define BASE 150L

using person = std::pair<std::string, int64_t>;

std::vector<person> queue(std::vector<person> people) {
    int64_t n = people.size();
    std::vector<int64_t> new_queue;

    std::sort(people.begin(), people.end(), [](person a, person b) {
        return a.second < b.second;
    });

    for(int64_t i = 0; i < n; i++) {
        if(people.at(i).second > i) {
            people.clear();
            break;
        }
        new_queue.insert(new_queue.begin() + i - people.at(i).second, i);
    }

    if(!people.empty())
        for(int64_t i = 0; i < n; i++)
            people.at(new_queue.at(i)).second = i*10 + BASE;

    return people;
}

int main() {
    int64_t n;
    std::cin >> n;
    std::vector<person> people(n);
    
    for(int64_t i = 0; i < n; i++)
        std::cin >> people.at(i).first >> people.at(i).second;

    std::vector<person> result = queue(people);
    if(result.empty()) {
        std::cout << -1 << std::endl;
        return 0;
    }

    for(auto it = result.begin(); it != result.end(); it++)
        std::cout << it->first << " " << it->second << std::endl;
    
    return 0;
}