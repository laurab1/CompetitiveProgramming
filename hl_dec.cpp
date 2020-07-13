#include <stdio.h>
#include <vector>
#include <tuple>
#include <algorithm>

template <typename T, T msum(T const&, T const&)>
class Unit {
    public:
    static const T empty;
    static const T NaE;
};

template <typename T>
T add(T const& a, T const& b) {
    return a + b;
}

template <>
const int64_t Unit<int64_t, add<int64_t>>::empty(0);

template <>
const int64_t Unit<int64_t, add<int64_t>>::NaE(-1);

template <typename T, 
          T msum(T const&, T const&), 
          T unit = Unit<T, msum>::empty,
          T nae = Unit<T, msum>::NaE>
class Monoid {
    public:
    using mtype = T;
    static T munit() {
        return unit;
    }
    static mtype madd(mtype a, mtype b) {
        return msum(a, b);
    }
    static mtype mnae() {
        return nae;
    }
};


template <typename Tm>
class SegmentTree {
    using vtype = typename Tm::mtype;

    private:
        std::vector<vtype> tree;
        int64_t size;

    public:
    SegmentTree(int64_t s) : tree(s*2, Tm::munit()), size(s) {
        for(int64_t i = s-1; i > 0; i--)
            tree.at(i) = Tm::madd(tree.at(i<<1), tree.at(i<<1|1));
    }

    //update node
    void update(int64_t idx, vtype val) {
        for(tree.at(idx + size) = val; idx > 1; idx >>= 1)
            tree.at(idx>>1) = Tm::madd(tree.at(idx), tree.at(idx^1));
    }

    //update range
    void update(int64_t left, int64_t right, vtype val) {
        for(left += size, right += size; left < right; left >>= 1, right >>= 1) {
            if(left & 1) {
                tree.at(left) = Tm::madd(tree.at(left), val);
                left++;
            }
            if(right & 1) {
                right--;
                tree.at(right) = Tm::madd(tree.at(right), val);
            }
        }
    }

    //query range
    vtype query(int64_t left, int64_t right) {
        vtype res = Tm::munit();
        for(left += size, right += size; left < right; left >>= 1, right >>= 1) {
            if(left & 1)
                res = Tm::madd(res, tree.at(left++));
            if(right & 1)
                res = Tm::madd(res, tree.at(right++));
        }
        return res;
    }

    //query point
    vtype query(int64_t idx) {
        vtype res = Tm::munit();
        for(idx += size; idx > 0; idx >>= 1)
            res = Tm::madd(res, tree.at(idx));
        return res;
    }

};

template <typename T>
class Node {
    private:
    T val;

    public:
    int64_t label;

    Node(T v, int64_t lbl) : val(v), label(lbl) {}

    void Set(T v) {
        val = v;
    }
};

template <typename Tm>
class Graph {
    using vtype = typename Tm::mtype;

    private:
    std::vector<std::vector<int64_t>> graph;
    std::vector<Node<vtype>> nodes;

    public:
    Graph(int64_t size) : graph(size), nodes(size) {}

    //build a graph from a vector of edges
    Graph(int64_t size, std::vector<std::pair<int64_t, int64_t>> edges) : graph(size), nodes(size, Node<vtype>(Tm::nae(), -1)) {
        for(int64_t i = 0; i < edges.size(); i++) {
            int64_t idx1 = edges.at(i).first;
            int64_t idx2 = edges.at(i).second;
            if(nodes.at(idx1).label == -1)
                nodes.at(idx1).label = idx1;
            if(nodes.at(idx2).label == -1)
                nodes.at(idx2).label = idx2;
            graph.at(idx1).push_back(edges.at(i).second);
            graph.at(idx2).push_back(edges.at(i).first);
        }
    }

    Graph(std::vector<Node<vtype>> nds) {
        nds.erase(std::unique(nds.begin(), nds.end(), [](Node<vtype> n1, Node<vtype> n2) {
            n1.label == n2.label;
        }), nds.end());
        graph(nds.size());
        nodes(nds.size());
        std::copy(nds.begin(), nds.end(), nodes.begin());
    }
};

template <typename Tm>
class HeavyLight {
    using vtype = typename Tm::mtype;

    private:
    std::vector<int64_t> parent;
    std::vector<int64_t> heavy;
    std::vector<int64_t> depth;
    std::vector<int64_t> root;
    std::vector<int64_t> treePos;
    SegmentTree<vtype> stree;

    template <typename G>
    int64_t dfs(const G& graph, int v) {
        int64_t size = 1;
        int64_t max_subtree = 0;
        for(int64_t u : graph[v])
            if(u != parent.at(v)) {
                parent.at(u) = v;
                depth.at(u) = depth.at(v) + 1;
                int64_t subtree = dfs(graph, u);
                if(subtree > max_subtree) {
                    heavy.at(v) = u;
                    max_subtree = subtree;
                }
                size += subtree;
            }
        return size;
    }

    template <typename ModOp>
    void process_path(int64_t u, int64_t v, ModOp op) {
        while(root.at(u) != root.at(v)) {
            if(depth.at(root.at(u)) > depth.at(root.at(v)))
                std::swap(u, v);
            op(treePos.at(root.at(v)), treePos.at(v) + 1);
            v = parent.at(root.at(v));
        }
        if(depth.at(u) > depth.at(v))
            std::swap(u, v);
            op(treePos.at(u), treePos.at(v) + 1);
    }

    public:
    template <typename G>
    HeavyLight(const G& graph) : stree(graph.size()) {
        int size = graph.size();
        parent(graph.size());
        heavy(graph.size());
        depth(graph.size());
        root(graph.size());
        treePos(graph.size());
        std::fill_n(heavy, size, -1);
        parent.at(0) = -1;
        depth.at(0) = 0;
        dfs(graph, 0);
        for(int64_t i = 0, curr = 0; i < size; i++) 
            if(parent.at(i) == -1 || heavy.at(parent.at(i)) != i)
                for(int64_t j = i; j != -1; j = heavy.at(j)) {
                    root.at(j) = i;
                    treePos.at(j) = curr++;
                }
    }

    void set(int64_t v, const vtype& val) {
        stree.set(v, val);
    }

    void modify_path(int64_t u, int64_t v, const vtype& val) {
        process_path(u, v, [this, &val](int64_t left, int64_t right) {
            stree.update(left, right, val);
        });
    }

    vtype query_path(int u, int v) {
        vtype res = Tm::munit();
        process_path(u, v, [this, &res](int64_t left, int64_t right) {
            Tm::madd(res, stree.query(left, right));
        });
    }
};