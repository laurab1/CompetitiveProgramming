#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using matrix = std::vector<std::vector<int64_t>>;
using pair = std::pair<int64_t, int64_t>;

void dfs(matrix &graph, std::vector<bool> &visited, int64_t i) {
    if(visited.at(i))
        return;

    visited.at(i) = true;
    for(auto el : graph.at(i))
        dfs(graph, visited, el);

}

int64_t learning_languages(matrix langs, int64_t n) {
    int64_t m = langs.size();
    matrix graph(n);
    std::vector<bool> visited(n);
    int64_t ccs = 0;

    for(auto it = langs.begin(); it != langs.end(); it++)
        for(int64_t j = 0; j < (int64_t)it->size() - 1; j++)
            for(int64_t k = j + 1; k < it->size(); k++) {
                graph.at(it->at(j)).push_back(it->at(k));
                graph.at(it->at(k)).push_back(it->at(j));
            }

    for(int64_t i = 0; i < n; i++) {
        if(!visited.at(i)) {
            ccs++;
            dfs(graph, visited, i);
        }
    }

    return ccs - 1;
}

int main() {
    int64_t n, m;
    std::cin >> n >> m;
    matrix lang(m);
    int64_t no_lang = 0;
    for(int64_t i = 0; i < n; i++) {
        int64_t k;
        std::cin >> k;
        if(!k)
            no_lang++;
        for(int64_t j = 0; j < k; j++) {
            int64_t lan;
            std::cin >> lan;
            lang.at(lan-1).push_back(i);
        }
    }
    if(no_lang == n)
        std::cout << n << std::endl;
    else
        std::cout << learning_languages(lang, n) << std::endl;

    return 0;
}