#include <iostream>
#include <vector>
#include <functional>

template <typename T>
T add(T const& a, T const& b) {
    return a + b;
}

template<typename T>
class monoid {
    private:
    T const unit;
    std::function<T(T const&,T const&)> add;

    public:
    monoid(T const u, std::function<T(T const&,T const&)> a) : unit(u), add(a) {}

    using mtype = T;
    mtype munit() {
        return unit;
    }
    mtype madd(mtype a, mtype b) {
        return add(a, b);
    }
};

template <typename Tm>
class fenwick_tree {
    using vtype = Tm;

    private:
        std::vector<vtype> ft;
        monoid<vtype> mon;

    public:
        fenwick_tree(long size, monoid<vtype> m) : ft(size + 1) , mon(m) {
            std::fill(ft.begin(), ft.end(), mon.munit());
        };

        fenwick_tree(int64_t size, vtype k, monoid<vtype> m) : mon(m) {
            ft(size + 1, k);
            ft.at(0) = mon.munit();
            update(0, k);
        }

        fenwick_tree(std::vector<vtype> vec, monoid<vtype> m) : mon(m) {
            ft(vec.size() + 1, mon.munit());
            for(int64_t i = 0; i < vec.size(); i++)
                update(i, vec.at(i));
        }

        vtype get_sum(int64_t index) {
            vtype sum = mon.munit();
            index++;
            while(index > 0) {
                sum = mon.madd(this->ft.at(index), sum);
                index -= index & (-index);
            }
            return sum;
        }

        void update(int64_t index, vtype val) {
            for (int64_t i = index + 1; i < ft.size(); i += (i & -i)) {
                ft.at(i) = mon.madd(ft.at(i), val);
            } 
        }
};

int main() {
    monoid<int64_t> mon(INT64_C(0), add<int64_t>);
    int64_t t, n, u, q, l, r, val;
    std::cin >> t;
    for(int64_t i = 0; i < t; i++) {
        std::cin >> n >> u;
        fenwick_tree<int64_t> ft(n, mon);
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