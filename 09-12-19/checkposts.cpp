#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <numeric>
#define MODULE 1000000007;

using matrix = std::vector<std::vector<int64_t>>;
using pair = std::pair<int64_t, int64_t>;

struct graph_info {
    std::vector<bool> visited;
    std::vector<int64_t> time;
    std::vector<int64_t> costs;
    std::vector<int64_t> t_order;

    graph_info(int64_t size) : visited(size, false), time(size), costs(size, 0) {}
};

void dfs(matrix &graph, graph_info &info, graph_info &tinfo, int64_t i, int64_t* cost, std::vector<int64_t> &min, int64_t t) {
    if(info.visited.at(i))
        return;

    info.visited.at(i) = true;
    info.time.at(i) = t++;
    if(*cost > info.costs.at(i)) {
        *cost = info.costs.at(i);
        min.back() = 0;
    }
    if(*cost == info.costs.at(i))
        min.back()++;
    for(auto el : graph.at(i))
        dfs(graph, info, tinfo, el, cost, min, t);
    info.time.at(i) = t++;
    tinfo.t_order.push_back(i);
}

pair checkposts(std::vector<int64_t> costs, matrix graph, matrix tgraph) {
    int64_t n = costs.size();
    graph_info info(n);
    graph_info tinfo(n);
    int64_t total = 0;
    int64_t cost = 0;
    std::vector<int64_t> min(1, 0);

    info.costs = costs;
    tinfo.costs = costs;

    for(int64_t i = 0; i < n; i++) {
        if(!info.visited.at(i))
            dfs(graph, info, tinfo, i, &cost, min, 1);
    }

    int64_t ccs = 0;
    int64_t tot_ways = 1;
    min.clear();
    for(auto it = tinfo.t_order.rbegin(); it != tinfo.t_order.rend(); it++) {
        if(!tinfo.visited.at(*it)) {
            cost = costs.at(*it);
            min.push_back(0);
            ccs++;
            dfs(tgraph, tinfo, info, *it, &cost, min, 1);
            total += cost;
            tot_ways = tot_ways * min.back() % MODULE;
        }
    }

    return pair(total, tot_ways);
}

int main() {
    int64_t n, m;
    std::cin >> n;
    std::vector<int64_t> costs(n);
    matrix graph(n);
    matrix tgraph(n);
    for(int64_t i = 0; i < n; i++)
        std::cin >> costs.at(i);
    std::cin >> m;
    for(int64_t i = 0; i < m; i++) {
        int64_t u, v;
        std::cin >> u >> v;
        graph.at(u-1).push_back(v-1);
        tgraph.at(v-1).push_back(u-1);
    }

    pair res = checkposts(costs, graph, tgraph);
    std::cout << res.first << " " << res.second << std::endl;

    return 0;
}