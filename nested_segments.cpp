#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

template <typename T>
using pair = std::tuple<T, T, T>;

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
class fenwick_tree {
    using vtype = typename Tm::mtype;

    private:
        std::vector<vtype> ft;

    public:
        fenwick_tree(long size) : ft(size + 1, Tm::munit()) {};

        fenwick_tree(int64_t size, vtype k) {
            ft(size + 1, k);
            ft.at(0) = Tm::munit();
            update(0, k);
        }

        fenwick_tree(std::vector<vtype> vec) {
            ft(vec.size() + 1, Tm::munit());
            for(int64_t i = 0; i < vec.size(); i++)
                update(i, vec.at(i));
        }

        vtype get_sum(int64_t index) {
            vtype sum = Tm::munit();
            index++;
            while(index > 0) {
                sum = Tm::madd(this->ft.at(index), sum);
                index -= index & (-index);
            }
            return sum;
        }

        void update(int64_t index, vtype val) {
            for (int64_t i = index + 1; i < ft.size(); i += (i & -i))
                ft.at(i) = Tm::madd(ft.at(i), val);
        }
};

void nested_segments(std::vector<pair<int64_t>> segs, std::vector<int64_t> elems) {
    std::vector<int64_t> res(segs.size());
    fenwick_tree<monoid<int64_t, add<int64_t>>> ft(elems.size());
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
        ft.update(r, 1);
    }
    for(auto it = segs.begin(); it != segs.end(); it++) {
        std::tie(l, r, i) = *it;
        res.at(i) = ft.get_sum(r) - 1;
        ft.update(r, -1);
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