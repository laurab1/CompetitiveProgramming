#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <sstream>

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

std::vector<std::string> split(std::string str, char ch)
{
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string tok;

  while(std::getline(ss, tok, ch)) 
    tokens.push_back(tok);

  return tokens;
}

using stgroup = group<int64_t, sub<int64_t>, add<int64_t>>;

int main() {
    int64_t n, m;
    std::cin >> n;
    std::vector<int64_t> vec(n);

    for(int64_t i = 0; i < n; i++)
        std::cin >> vec.at(i);

    std::cin >> m;
    std::string op;
    std::getline(std::cin, op);

    for(int64_t i = 0; i < m; i++) {
      std::getline(std::cin, op);
      auto ops = (split(op, ' '));
      if(ops.size() == 2)
        std::cout << "query" << std::endl;
      else
        std::cout << "update" << std::endl;
    }
}