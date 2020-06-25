#include <iostream>
#include <vector>

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

template<typename M>
using a_monoid = monoid<M, add<M>>;

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
            for (size_t i = index + 1; i < ft.size(); i += (i & -i))
                ft.at(i) = Tm::madd(ft.at(i), val);
        }
};

int main() {
    int64_t t, n, u, q, l, r, val;
    std::cin >> t;
    for(int64_t i = 0; i < t; i++) {
        std::cin >> n >> u;
        fenwick_tree<a_monoid<int64_t>> ft(n);
        for(int64_t j = 0; j < u; j++) {
            std::cin >> l >> r >> val;
            ft.update(l, val);
            val *= -1;
            ft.update(r+1, val);
        }
        std::cin >> q;
        for(int64_t j = 0; j < q; j++) {
            std::cin >> val;
            std::cout << ft.get_sum(val) << std::endl;
        }
    }
}