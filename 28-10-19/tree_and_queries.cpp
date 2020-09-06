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
std::vector<int64_t> flatten;
std::vector<int64_t> start;
std::vector<int64_t> end;
int64_t occurr[100001];
int64_t occurrk[100001];
int64_t d = 0;
int64_t b = 0;

void dfs(std::vector<int64_t> &colors, std::vector<int64_t> &flatten, tree &adj, int64_t idx, int64_t old) {
    start[idx] = ++b;
    flatten[b] = colors[idx];
    for(auto u : adj[idx])
        if(u != old)
            dfs(colors, flatten, adj, u, idx);
    end[idx] = b;
}

void add(int64_t idx) {
    occurr[flatten[idx]]++;
    occurrk[occurr[flatten[idx]]]++;
}

void remove(int64_t idx) {
    occurrk[occurr[flatten[idx]]]--;
    occurr[flatten[idx]]--;
}

void tree_and_queries(std::vector<int64_t> &colors, tree &adj, std::vector<query> &queries) {
    int64_t n = colors.size();
    int64_t m = queries.size();
    block_size = (int64_t)sqrt(n);
    std::vector<int64_t> results(m);

    std::sort(queries.begin(), queries.end(), [](query a, query b) {
        if(a.l/block_size != b.l/block_size)
            return a.l/block_size < b.l/block_size;
        return a.r < b.r;
    });

    int64_t l = queries[0].l;
    int64_t r = l - 1;

    for(int64_t i = 0; i < m; i++) {
        int64_t lq = queries[i].l;
        int64_t rq = queries[i].r;

        while(l < lq) {
            remove(l);
            l++;
        }

        while(l > lq) {
            l--;
            add(l);
        }
        
        while(r < rq) {
            r++;
            add(r);
        }

        while(r > rq) {
            remove(r);
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
    std::vector<int64_t> colors(n+1);
    flatten.resize(n+1);
    start.resize(n);
    end.resize(n);
    tree adj(n);

    for(int64_t i = 0; i < n; i++) {
        std::cin >> colors[i];
    }

    for(int64_t i = 0; i < n - 1; i++) {
        int64_t s, d;
        std::cin >> s >> d;
        adj[s-1].push_back(d-1);
        adj[d-1].push_back(s-1);
    }
    dfs(colors, flatten, adj, 0, -1);
    
    std::vector<query> queries(m);
    for(int64_t i = 0; i < m; i++) {
        int64_t q1, q2;
        std::cin >> q1 >> q2;
        queries[i].l = start[q1-1];
        queries[i].r = end[q1-1];
        queries[i].i = i;
        queries[i].c = q2;
    }
    tree_and_queries(colors, adj, queries);
}