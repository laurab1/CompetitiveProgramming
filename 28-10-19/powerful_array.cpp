#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct query {
    int64_t l;
    int64_t r;
    int64_t i;
    query() {}
};

int64_t occurr[1000000];
int64_t block_size;

void powerful_array(std::vector<int64_t> &elems, std::vector<query> &queries, int64_t n, int64_t t) {
    block_size = (int64_t)sqrt(n);
    std::vector<int64_t> result(t);

    std::sort(queries.begin(), queries.end(), [](query a, query b) {
        if(a.l/block_size != b.l/block_size)
            return a.l/block_size < b.l/block_size;
        return a.r < b.r;
    });

    int64_t l = 0;
    int64_t r = 0;
    int64_t sum = 0;

    for(int64_t i = 0; i < t; i++) {
        int64_t lq = queries[i].l;
        int64_t rq = queries[i].r;

        while(l < lq) {
            sum -= (2*(occurr[elems[l]]) - 1)*elems[l];
            occurr[elems[l]]--;
            l++;
        }


        while(l > lq) {
            sum += (2*occurr[elems[l-1]] + 1)*elems[l-1];
            occurr[elems[l-1]]++;
            l--;
        }
        
        while(r <= rq) {
            sum += (2*occurr[elems[r]] + 1)*elems[r];
            occurr[elems[r]]++;
            r++;
        }

        while(r > rq + 1) {
            sum -= (2*occurr[elems[r-1]] - 1)*elems[r-1];
            occurr[elems[r-1]]--;
            r--;
        }

        result[queries[i].i] = sum;
    }

    for(int64_t i = 0; i < t; i++)
        std::cout << result[i] << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int64_t n, t;
    std::cin >> n;
    std::cin >> t;
    std::vector<query> queries(t);
    std::vector<int64_t> elems(n);

    for(int64_t i = 0; i < n; i++)
        std::cin >> elems[i];

    for(int64_t i = 0; i < t; i++) {
        int64_t l, r;
        std::cin >> l >> r;
        queries[i].l = l - 1;
        queries[i].r = r - 1;
        queries[i].i = i;
    }

    powerful_array(elems, queries, n, t);

    return 0;
}