#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <climits>
#include <algorithm>

template <typename T>
T add(T const& a, T const& b) {
    return a + b;
}

template <typename T>
T min(T const& a, T const& b) {
    return std::min(a, b);
};

template<typename T, T msum(T const&, T const&)>
class Unit {
    public:
    static const T empty;
};

template<>
const int64_t Unit<int64_t, add<int64_t>>::empty(0);

template<>
const int64_t Unit<int64_t, min<int64_t>>::empty(LLONG_MAX);

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

template<typename T, T idem(T const&, T const&), 
                     T msum(T const&, T const&), 
                     T unit = Unit<T, msum>::empty,
                     T idunit = Unit<T, idem>::empty>
class semiring : public monoid<T, msum> {
    public:
    
    static T runit() {
        return idunit;
    }
    static T midem(T a, T b) {
        return idem(a, b);
    }
};

template <typename Tm>
class segment_tree {
    using vtype = typename Tm::mtype;
    private:
    std::vector<vtype> st;
    std::vector<vtype> lazy;
    int64_t in_size;

    void build_stree(std::vector<vtype> &v, int64_t idx, int64_t l, int64_t r) {
        if(l > r) return;
        if(l == r)  {
            st.at(idx) = v.at(l);
            return;
        }
        int64_t center = l + (r-l)/2;
        int64_t lch = idx*2+1;
        int64_t rch = idx*2+2;
        build_stree(v, lch, l, center);
        build_stree(v, rch, center + 1, r);
        st.at(idx) = Tm::midem(st.at(lch), st.at(rch));
    }

    void update_aux(int64_t start, int64_t end, int64_t ustart, int64_t uend, vtype val, int64_t seg_idx) {
        int64_t lch = seg_idx*2+1;
        int64_t rch  = seg_idx*2+2;
        if(lazy.at(seg_idx) != Tm::munit()) {
            st.at(seg_idx) = Tm::madd(st.at(seg_idx), lazy.at(seg_idx));
            if(start != end) {
                lazy.at(lch) = Tm::madd(lazy.at(lch), lazy.at(seg_idx));
                lazy.at(rch) = Tm::madd(lazy.at(rch), lazy.at(seg_idx));
            }
            lazy.at(seg_idx) = Tm::munit();
        }
        if(start > end or start > uend or end < ustart)
            return;

        if(start >= ustart and end <= uend) {
            st.at(seg_idx) = Tm::madd(st.at(seg_idx), val);
            if(start != end) {
                lazy.at(lch) = Tm::madd(lazy.at(lch), val);
                lazy.at(rch) = Tm::madd(lazy.at(rch), val);
            }
            return;
        }

        int64_t center = start + (end - start)/2;
        update_aux(start, center, ustart, uend, val, lch);
        update_aux(center + 1, end, ustart, uend, val, rch);

        st.at(seg_idx) = Tm::midem(st.at(lch), st.at(rch));
    }

    vtype sum_aux(int64_t start, int64_t end, int64_t qstart, int64_t qend, int64_t seg_idx) {
        int64_t lch = seg_idx*2+1;
        int64_t rch = seg_idx*2+2;

        if(lazy.at(seg_idx) != Tm::munit()) {
            st.at(seg_idx) = Tm::madd(st.at(seg_idx), lazy.at(seg_idx));
            if(start != end) {
                lazy.at(lch) = Tm::madd(lazy.at(lch), lazy.at(seg_idx));
                lazy.at(rch) = Tm::madd(lazy.at(rch), lazy.at(seg_idx));
            }
            lazy.at(seg_idx) = Tm::munit();
        }

        if(qstart <= start and qend >= end)
            return st.at(seg_idx);

        if(end < qstart or start > qend or start > end)
            return Tm::runit();

        int64_t center = start + (end - start)/2;
        vtype v1 = sum_aux(start, center, qstart, qend, lch);
        vtype v2 = sum_aux(center+1, end, qstart, qend, rch);
        return Tm::midem(v1, v2);
    }

    public:
    segment_tree(int64_t n) : in_size(n) {
        int64_t size = (int64_t)(ceil(log2(n)));
        int64_t max_size = 2*(int64_t)pow(2, size) - 1;
        st.resize(max_size);
        lazy.resize(max_size);
    }

    segment_tree(std::vector<vtype> &v) : in_size(v.size()) {
        int64_t size = (int64_t)(ceil(log2(in_size)));
        int64_t max_size = 2*(int64_t)pow(2, size) - 1;
        st.resize(max_size);
        build_stree(v, 0, 0, in_size-1);
        lazy.resize(max_size);
    }

    void update(int64_t start, int64_t end, vtype val) {
        if(start > end) {
            update_aux(0, in_size-1, start, in_size - 1, val, 0);
            update_aux(0, in_size-1, 0, end, val, 0);
        } else
            update_aux(0, in_size-1, start, end, val, 0);
    }

    vtype query_sum(int64_t start, int64_t end) {
        if(start > end)
            return Tm::midem(query_sum(start, in_size - 1), query_sum(0, end));

        return sum_aux(0, in_size-1, start, end, 0);
    }
};

std::vector<std::string> split(std::string str, char ch)
{
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string tok;

  while(std::getline(ss, tok, ch)) 
    tokens.push_back(tok);

  return tokens;
}

using stmonoid = monoid<int64_t, add<int64_t>>;
using stsemiring = semiring<int64_t, min<int64_t>, add<int64_t>>;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    
    int64_t n, m;
    std::cin >> n;
    std::vector<int64_t> vec(n);

    for(int64_t i = 0; i < n; i++)
        std::cin >> vec.at(i);

    segment_tree<stsemiring> st(vec);

    std::cin >> m;
    std::string op;
    std::getline(std::cin, op);

    for(int64_t i = 0; i < m; i++) {
      std::getline(std::cin, op);
      auto ops = (split(op, ' '));
      if(ops.size() == 2)
        std::cout << st.query_sum(std::stol(ops.at(0)), std::stol(ops.at(1))) << std::endl;
      else
        st.update(std::stol(ops.at(0)), std::stol(ops.at(1)), std::stol(ops.at(2)));
    }
}