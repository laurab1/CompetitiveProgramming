#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

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

        fenwick_tree(std::vector<vtype> vec) : ft(vec.size() + 1, Tm::munit()) {
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

template <typename T>
using pair  = std::pair<int64_t, int64_t>;

int64_t pashmak(std::vector<int64_t> vec) {
    std::vector<pair<int64_t>> aux(vec.size());

    for(int64_t i = 0; i < vec.size(); i++) {
        aux.at(i).first = vec.at(i);
        aux.at(i).second = i;
    }
    std::sort(aux.begin(), aux.end(), [](pair<int64_t> a, pair<int64_t> b) {
        return a.first < b.first;
    });
    int64_t rank = 0;
    for(int64_t i = 1; i < aux.size(); i++)
        if(aux.at(i).first == aux.at(i-1).first)
            aux.at(i-1).first = rank;
        else
            aux.at(i-1).first = rank++;
    aux.back().first = rank;

    for(int64_t i = 0; i < aux.size(); i++) 
        vec.at(aux.at(i).second) = aux.at(i).first;

    std::vector<int64_t> counter(vec.size(), 0);
    std::vector<int64_t> s_counter(vec.size(), 0);
    fenwick_tree<monoid<int64_t, add<int64_t>>> ft(vec.size());
    for(int64_t i = vec.size()-1; i >= 0; i--) {
        counter.at(vec.at(i))++;
        s_counter.at(i) = counter.at(vec.at(i));
        ft.update(counter.at(vec.at(i)), 1);
    }

    int64_t num_pairs = 0;
    std::fill(counter.begin(), counter.end(), 0);
    for(int64_t i = 0; i < vec.size(); i++) {
        ft.update(s_counter.at(i), -1);
        counter.at(vec.at(i))++;
        num_pairs += ft.get_sum(counter.at(vec.at(i))-1);
    }

    return num_pairs;
}

int main() {
    int64_t n;
    std::cin >> n;
    std::vector<int64_t> vec(n);
    for(int64_t i = 0; i < n; i++)
        std::cin >> vec.at(i);
    std::cout << pashmak(vec) << std::endl;
}