#include <iostream>
#include <algorithm>
#include <vector>

class DisjointSet {
    private:
        std::vector<int64_t> parents;
        std::vector<int64_t> ranks;
        int64_t size;

    public:
        DisjointSet(int64_t n) : size(n)  {
            parents.resize(n);
            ranks.resize(n);
            this->makeSet();
        }

        void makeSet() {
            
            for(int64_t i = 0; i < this-> size; i++)
                parents[i] = i;
        }

        int64_t find(int64_t x) {
            if(parents[x] != x)
                parents[x] = find(parents[x]);

            return parents[x];
        }

        void unionSet(int64_t x, int64_t y) {
            int64_t xset = find(x);
            int64_t yset = find(y);

            if (xset == yset) 
                return; 

            if (ranks[xset] < ranks[yset]) 
                parents[xset] = yset; 
            else {
                if (ranks[xset] > ranks[yset])
                    parents[yset] = xset; 
                else { 
                    parents[yset] = xset; 
                    ranks[xset]++; 
                }
            }  
        }
};

using graph = std::vector<std::vector<int64_t>>;

struct edge {
    public:
        int64_t s;
        int64_t d;
        int64_t w;
        edge() {}
};


int main() {
    int64_t n, m;
    std::cin >> n >> m;
    graph gr(n);
    std::vector<edge> edges(m);

    for(int64_t i = 0; i < m; i++) {
        int64_t s, d, w;
        std::cin >> s >> d >> edges[i].w;
        edges[i].s = s - 1;
        edges[i].d = d - 1;
        gr[edges[i].s].push_back(edges[i].d);
        gr[edges[i].d].push_back(edges[i].s);
    }

    std::sort(edges.begin(), edges.end(), [](edge &a, edge &b) {
        return a.w < b.w;
    });

    DisjointSet ds(n);

    int64_t result = 0;
    for(int64_t i = 0; i < m; i++)
        if(ds.find(edges[i].s) != ds.find(edges[i].d)) {
            ds.unionSet(edges[i].s, edges[i].d);
            result += edges[i].w;
        }

    std::cout << result << std::endl;

    return 0;    
}