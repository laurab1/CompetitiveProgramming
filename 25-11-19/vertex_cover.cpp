#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

template<typename T>
using edge = std::pair<T, T>;

template<typename T>
using adj_list = std::vector<std::vector<T>>;

template<typename T>
int64_t vertex_cover(std::vector<T> parents,
                     std::vector<std::vector<int64_t>> dp, 
                     adj_list<T> adj, 
                     T node, 
                     int64_t covered) {
    if(adj.at(node).size() == 0)
        return covered;
    if(dp.at(node).at(covered) != -1)
        return dp.at(node).at(covered);

    int64_t sum = covered;

    for(int64_t i = 0; i < adj.at(node).size(); i++) {
        T v = adj.at(node).at(i);
        if(v != parents.at(node)) {
            parents.at(v) = node;
            if(!covered)
                sum += vertex_cover(parents, dp, adj, v, 1L);
            else
                sum += std::min(vertex_cover(parents, dp, adj, v, 1L), vertex_cover(parents, dp, adj, v, 0L));
        }
    }
    dp.at(node).at(covered) = sum;
    return dp.at(node).at(covered);
}

int main() {
    int64_t n;

    std::cin >> n;
    std::vector<edge<int64_t>> edges(n-1);
    std::vector<std::vector<int64_t>> adj(n);
    std::vector<int64_t> parents(n);

    for(int64_t i = 0; i < n-1; i++) {
        std::cin >> edges.at(i).first >> edges.at(i).second;
        adj.at(edges.at(i).first - 1).push_back(edges.at(i).second - 1);
        adj.at(edges.at(i).second - 1).push_back(edges.at(i).first - 1);
        parents.at(edges.at(i).second - 1) = edges.at(i).first - 1;
    }

    std::vector<std::vector<int64_t>> dp(n, std::vector<int64_t>(2, -1));

    std::cout << std::min(vertex_cover(parents, dp, adj, 0L, 0L), 
                          vertex_cover(parents, dp, adj, 0L, 1L)) << std::endl;

    return 0;
}