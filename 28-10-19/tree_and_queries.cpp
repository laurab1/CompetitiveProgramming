#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>

struct query {
    int64_t l;
    int64_t r;
    int64_t c;
    int64_t i;
    query() {}
};

using tree = std::vector<std::vector<int64_t>>;
int64_t block_size;
std::vector<int64_t> stimes;
std::vector<int64_t> ftimes;
std::vector<bool> visited;
std::vector<int64_t> start;
std::vector<int64_t> end;
int64_t occurr[10000];
int64_t occurrk[10000];
int64_t t = 0;
int64_t d = 0;
int64_t b = 0;

void dfs(std::vector<query> &queries, std::vector<int64_t> &flatten, tree &adj, int64_t idx) {
    if(visited.at(idx))
        return;
    flatten.at(t) = idx;
    start.at(idx) = ++b;
    stimes.at(idx) = t++;
    visited.at(idx) = true;
    for(auto u : adj.at(idx))
        dfs(queries, flatten, adj, u);
    flatten.at(t) = idx;
    end.at(idx) = b;
    ftimes.at(idx) = t++;
}

void add(std::vector<int64_t> &colors, int64_t idx) {
    occurr[colors[idx]]++;
    occurrk[occurr[colors[idx]]]++;
}

void remove(std::vector<int64_t> &colors, int64_t idx) {
    occurrk[occurr[colors[idx]]]--;
    occurr[colors[idx]]--;
}

void tree_and_queries(std::vector<int64_t> &colors, tree &adj, std::vector<query> &queries) {
    int64_t n = colors.size();
    int64_t m = queries.size();
    std::vector<int64_t> flatten(n*2);
    stimes.resize(n);
    ftimes.resize(n);
    visited.resize(n);
    start.resize(n);
    end.resize(n);
    block_size = sqrt(n);
    std::vector<int64_t> results(m);

    std::sort(queries.begin(), queries.end(), [](query a, query b) {
        if(a.l/block_size != b.l/block_size)
            return a.l/block_size < b.l/block_size;
        return a.r < b.r;
    });

    dfs(queries, flatten, adj, 0);
    for(int64_t i = 0; i < m; i++) {
        int64_t j = queries.at(i).l;
        queries.at(i).l = start[j];
        queries.at(i).r = end[j] - 1;
    }

    int64_t l = 0;
    int64_t r = 0;

    for(int64_t i = 0; i < m; i++) {
        int64_t lq = queries[i].l;
        int64_t rq = queries[i].r;

        while(l < lq) {
            remove(colors, flatten.at(l));
            l++;
        }

        while(l > lq) {
            add(colors, flatten.at(l-1));
            l--;
        }
        
        while(r <= rq) {
            add(colors, flatten.at(r));
            r++;
        }

        while(r > rq + 1) {
            remove(colors, flatten.at(r-1));
            r--;
        }

        results[queries[i].i] = occurrk[queries[i].c];
    }

    for(int64_t i = 0; i < m; i++)
        std::cout << results[i] << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int64_t n, m;
    std::cin >> n >> m;
    std::vector<int64_t> colors(n);
    tree adj(n);

    for(int64_t i = 0; i < n; i++)
        std::cin >> colors.at(i);
    for(int64_t i = 0; i < n - 1; i++) {
        int64_t s, d;
        std::cin >> s >> d;
        adj.at(s-1).push_back(d-1);
    }
    std::vector<query> queries(m);
    for(int64_t i = 0; i < m; i++) {
        int64_t q1, q2;
        std::cin >> q1 >> q2;
        queries.at(i).l = q1 - 1;
        queries.at(i).r = q2;
        queries.at(i).i = i;
        queries.at(i).c = q2;
    }
    tree_and_queries(colors, adj, queries);
}