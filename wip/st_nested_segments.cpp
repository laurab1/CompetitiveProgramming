#include <iostream>
#include <vector>
#include <cmath>

template<typename T, T msum(T const&, T const&)>
class Unit {
    public:
    static const T empty;
};

template <typename T>
T add(T const& a, T const& b) {
    return a + b;
}

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

template <typename Tm>
class segment_tree {
    using vtype = typename Tm::mtype;
    private:
    std::vector<vtype> st;

    public:
    segment_tree(int64_t size) :st(size, Tm::munit()) {
        int64_t n = (int64_t) ceil(log2(size));
        int64_t max_nleaves = 2*pow(2, n) -1;
        st.resize(max_nleaves);
    }

    segment_tree(std::vector<vtype> v) {
        segment_tree(v.size());
        *st.begin() = (v, st.begin(), 0, v.size()-1);
    }

    vtype build_stree(std::vector<vtype> v, std::vector<vtype>::iterator st, int64_t l, int64_t r) {
        if(l == r)  {
            *st = v.at(l);
            return v.at(l);
        }
        int64_t center = l + (r-l)/2;
        std::vector<vtype>::iterator lch = st*2+1;
        std::vector<vtype>::iterator rch = st*2+2;
        *st = build_stree(v, lch, l, center) + build_stree(v, rch, center + 1, r);
        return *st;
    }

    void update(vtype val, int64_t idx) {

    }

};