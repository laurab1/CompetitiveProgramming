#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <algorithm>

template <typename T>
T add(T const& a, T const& b) {
    return a + b;
}

template <typename T>
T sub(T const& a, T const& b) {
    return a - b;
};

template<typename T, T msum(T const&, T const&)>
class Unit {
    public:
    static const T empty;
};

template<>
const int64_t Unit<int64_t, add<int64_t>>::empty(0);

template<typename T, T msum(T const&, T const&), T unit = Unit<T, msum>::empty>
class monoid {
    public:
    using mtype = T;
    static T munit() {
        return unit;
    }
    static mtype madd(mtype a, mtype b) {
        return msum(a, b);
    }
};

template<typename T, T gsub(T const&, T const&), T msum(T const&, T const&), T unit = Unit<T, msum>::empty>
class group : public monoid<T, msum> {
    public:
    
    static T gdiff(T a, T b) {
        return gsub(a, b);
    }
};

template <typename Tm>
class segment_tree {
    using vtype = typename Tm::mtype;
    private:
    std::vector<vtype> st;
    int64_t in_size;

    void build_stree(std::vector<vtype> v, int64_t idx, int64_t l, int64_t r) {
        if(l == r)  {
            st.at(idx) = v.at(l);
            return;
        }
        int64_t center = l + (r-l)/2;
        int64_t lch = idx*2+1;
        int64_t rch = idx*2+2;
        build_stree(v, lch, l, center);
        build_stree(v, rch, center + 1, r);
        st.at(idx) = Tm::madd(st.at(lch), st.at(rch));
    }

    void update_aux(int64_t start, int64_t end, int64_t idx, vtype val, int64_t seg_idx) {
        if(idx < start or idx > end or seg_idx >= st.size())
            return;

        int64_t lch = seg_idx*2+1;
        int64_t rch  = seg_idx*2+2;
        if(lch >= in_size or rch >= in_size) {
            st.at(seg_idx) = Tm::madd(st.at(seg_idx), val);
        }

        int64_t center = start + (end - start)/2;
        update_aux(start, center, idx, val, lch);
        update_aux(center + 1, end, idx, val, rch);
        
        if(lch < in_size and rch < in_size)
            st.at(seg_idx) = Tm::madd(st.at(lch), st.at(rch));
    }

    vtype sum_aux(int64_t start, int64_t end, int64_t qstart, int64_t qend, int64_t seg_idx) {

        if(qstart <= start and qend >= end)
            return st.at(seg_idx);

        if(end < qstart or start > qend)
            return Tm::munit();

        int64_t center = start + (end - start)/2;
        int64_t lch = seg_idx*2+1;
        int64_t rch = seg_idx*2+2;

        return Tm::madd(sum_aux(start, center, qstart, qend, lch), sum_aux(center+1, end, qstart, qend, rch));
    }

    public:
    segment_tree(int64_t n) : in_size(n) {
        int64_t size = (int64_t)(ceil(log2(n)));
        int64_t max_size = 2*(int64_t)pow(2, size) - 1;
        st.resize(max_size);
    }

    segment_tree(std::vector<vtype> v) : in_size(v.size()) {
        int64_t size = (int64_t)(ceil(log2(in_size)));
        int64_t max_size = 2*(int64_t)pow(2, size) - 1;
        st.resize(max_size);
        build_stree(v, 0, 0, in_size-1);
    }

    void print() {
        for(auto it = st.begin(); it != st.end(); it++)
            std::cout << *it << std::endl;
    }

    void update(int64_t idx, vtype val) {
        if(idx < 0 or idx >= in_size)
            return;

        update_aux(0, in_size-1, idx, val, 0);
    }

    vtype query_sum(int64_t start, int64_t end) {
        if(start < 0 or end >= in_size or start == end)
            return Tm::munit();

        return sum_aux(0, in_size-1, start, end, 0);
    }
};

using stgroup = group<int64_t, sub<int64_t>, add<int64_t>>;
template <typename T>
using pair = std::tuple<T, T, T>;

void nested_segments(std::vector<pair<int64_t>> segs, std::vector<int64_t> elems) {
    std::vector<int64_t> res(segs.size());
    segment_tree<stgroup> st(elems.size());
    int64_t l, r, i;

    std::sort(elems.begin(), elems.end());

    for(auto it = segs.begin(); it != segs.end(); it++) {
        std::tie(l, r, i) = *it;
        std::get<0>(*it) = std::lower_bound(elems.begin(), elems.end(), l) - elems.begin();
        std::get<1>(*it) = std::lower_bound(elems.begin(), elems.end(), r) - elems.begin();
    }

    std::sort(segs.begin(), segs.end(), [](pair<int64_t> a, pair<int64_t> b) {
        return std::get<0>(a) < std::get<0>(b);
    });

    for(auto it = segs.begin(); it != segs.end(); it++) {
        std::tie(l, r, i) = *it;
        st.update(r, 1);
    }

    for(auto it = segs.begin(); it != segs.end(); it++) {
        std::tie(l, r, i) = *it;
        res.at(i) = st.query_sum(l, r) - 1;
        st.update(r, -1);
    }

    for(auto it = res.begin(); it != res.end(); it++)
        std::cout << *it << std::endl;
}

int main() {
    int64_t n, f, s;
    std::cin >> n;
    std::vector<pair<int64_t>> segs(n);
    std::vector<int64_t> elems;
    elems.reserve(n*2);
    for(int64_t i = 0; i < n; i++) {
        std::cin >> f >> s;
        segs.at(i) = pair<int64_t>(f, s, i);
        elems.push_back(f);
        elems.push_back(s);
    }
    nested_segments(segs, elems);

    return 0;
}