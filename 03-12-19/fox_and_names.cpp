#include <iostream>
#include <vector>
#include <stack>

bool dfs(const std::vector<std::vector<int>> &graph, std::vector<int> &visited, int64_t i, std::stack<char> &st) {
    if(visited.at(i) == 1)
        return false;
        
    if(visited.at(i) == 0) {
        visited.at(i) = 1;
        for(auto el : graph.at(i)) {
            if(!dfs(graph, visited, el, st))
                return false;
        }
        st.push(char(i + 97));
        visited.at(i) = 2;
    }

    return true;
}

std::string topological_sort(std::vector<std::string> vec) {
    int64_t n = vec.size();
    std::vector<std::vector<int>> graph(26);
    std::vector<int> visited(26, 0);
    std::stack<char> order;

    for(int64_t i = 0; i < n - 1; i++) {
        int64_t len = std::min(vec.at(i).size(), vec.at(i+1).size());
        bool found = false;
        int64_t j = 0;
        while(j < len and !found) {
            if(vec.at(i).at(j) != vec.at(i+1).at(j)) {
                found = true;
                std::cout << int(vec.at(i+1).at(j)) - 97 << std::endl;
                graph.at(int(vec.at(i).at(j)) - 97).push_back(int(vec.at(i+1).at(j)) - 97);
                j++;
            }
        }

        if(!found and vec.at(i).size() > vec.at(i+1).size())
            return "Impossible";
    }

    bool order_found = true;
    for(int i = 0; i < 26; i++) {
        if(!visited.at(i))
            order_found = order_found and dfs(graph, visited, i, order);
    }
    
    if(order_found) {
        std::string alphabet;
        while(!order.empty()) {
            alphabet.push_back(order.top());
            order.pop();
        }
        return alphabet;
    }

    return "Impossible";
}

int main() {
    int64_t n;
    std::cin >> n;
    std::vector<std::string> vec(n);
    for(int64_t i = 0; i < n; i++)
        std::cin >> vec.at(i);
    std::cout << topological_sort(vec) << std::endl;

    return 0;
}