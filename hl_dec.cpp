#include <iostream>
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
    public:
    int64_t label;
    T val;

    Node(T v, int64_t lbl) : val(v), label(lbl) {}

    static void swap(Node<T> u, Node<T> v) {
        T tmp = u.val;
        int64_t lbl = u.label;
        u.val = v.val;
        u.label = v.label;
        v.val = tmp;
        v.label = lbl;
    }
};

template <typename Tm>
class Graph {

    private:
    std::vector<Node<typename Tm::mtype>> nodes;

    public:
    using vtype = typename Tm::mtype;
    std::vector<std::vector<int64_t>> graph;
    int64_t size;
    
    Graph(int64_t size) : graph(size), nodes(size), size(size) {}

    //build a graph from a vector of edges
    Graph(int64_t size, std::vector<std::pair<int64_t, int64_t>> es) : size(size), graph(size), nodes(size, Node<vtype>(Tm::mnae(), -1)) {
        for(int64_t i = 0; i < es.size(); i++) {
            int64_t idx1 = es.at(i).first;
            int64_t idx2 = es.at(i).second;
            if(nodes.at(idx1).label == -1)
                nodes.at(idx1).label = idx1;
            if(nodes.at(idx2).label == -1)
                nodes.at(idx2).label = idx2;
            graph.at(idx1).push_back(es.at(i).second);
            graph.at(idx2).push_back(es.at(i).first);
        }
        std::cout << "graph created" << std::endl;
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
    std::vector<Node<vtype>> parent;
    std::vector<Node<vtype>> heavy;
    std::vector<int64_t> depth;
    std::vector<Node<vtype>> root;
    std::vector<int64_t> treePos;
    SegmentTree<Tm> stree;

    int64_t dfs(Graph<Tm>& graph, int64_t v) {
        int64_t size = 1;
        int64_t max_subtree = 0;
        for(int64_t u : graph.graph.at(v))
            if(u != parent.at(v).label) {
                parent.at(u).label = v;
                depth.at(u) = depth.at(v) + 1;
                int64_t subtree = dfs(graph, u);
                if(subtree > max_subtree) {
                    heavy.at(v).label = u;
                    max_subtree = subtree;
                }
                size += subtree;
            }
        return size;
    }

    template <typename ModOp>
    void process_path(Node<vtype> u, Node<vtype> v, ModOp op) {
        int64_t l1 = u.label;
        int64_t l2 = v.label;
        std::cout << "process path" << std::endl;
        while(root.at(l1).label != root.at(l2).label) {
            if(depth.at(root.at(l1).label) > depth.at(root.at(l2).label)){
                Node<vtype>::swap(u, v);
                std::swap(l1, l2);
            }
            op(treePos.at(root.at(l2).label), treePos.at(l2) + 1);
            v = parent.at(root.at(l2).label);
        }
        std::cout << "endwhl" << std::endl;
        if(depth.at(l1) > depth.at(l2)) {
            Node<vtype>::swap(u, v);
            std::swap(l1, l2);
        }
        op(treePos.at(l1), treePos.at(l2) + 1);
    }

    public:
    HeavyLight(Graph<Tm> graph) : stree(graph.size),
                                  parent(graph.size, Node<vtype>(Tm::mnae(), -1)),
                                  heavy(graph.size, Node<vtype>(Tm::mnae(), -1)),
                                  depth(graph.size, 0),
                                  root(graph.size, Node<vtype>(Tm::mnae(), -1)),
                                  treePos(graph.size, 0) {
        dfs(graph, 0);
        for(int64_t i = 0, curr = 0; i < graph.size; i++) 
            if(parent.at(i).label == -1 || heavy.at(parent.at(i).label).label != i)
                for(int64_t j = i; j != -1; j = heavy.at(j).label) {
                    root.at(j).label = i;
                    treePos.at(j) = curr++;
                }
    }

    void set(int64_t v, vtype& val) {
        stree.update(v, val);
    }

    void modify_path(Node<vtype> u, Node<vtype> v, const vtype& val) {
        process_path(u, v, [this, &val](int64_t left, int64_t right) {
            stree.update(left, right, val);
        });
    }

    vtype query_path(Node<vtype> u, Node<vtype> v) {
        vtype res = Tm::munit();
        std::cout << "query path" << std::endl;
        process_path(u, v, [this, &res](int64_t left, int64_t right) {
            Tm::madd(res, stree.query(left, right));
        });
    }
};

int main() {
    //std::ios_base::sync_with_stdio(false);

    int64_t t, n;
    std::cin >> t;
    for(int64_t i = 0; i < t; i++) {
        std::cin >> n;
        std::vector<std::pair<int64_t, int64_t>> es(n-1);
        std::vector<int64_t> costs(n-1);
        for(int64_t j = 0; j < n-1; j++) {
            std::cin >> es.at(j).first >> es.at(j).second >> costs.at(j);
        }
        Graph<Monoid<int64_t, add<int64_t>>> graph(n+1, es);
        HeavyLight<Monoid<int64_t, add<int64_t>>> path_tree(graph);
        for(int64_t i = 0; i < es.size(); i++) {
            path_tree.set(i+1, costs.at(i));
        }
        std::cout << "blah" << std::endl;
        std::string query = "";
        int64_t a, b;
        std::cin >> query;
        std::cin >> a >> b;
        if(query.compare("CHANGE") == 0)
            path_tree.set(a+1, b);
        else {
            if(query.compare("QUERY") == 0)
                std::cout << path_tree.query_path(Node<int64_t>(a, a), Node<int64_t>(b, b));
        }
        std::cout << std::endl;
    }
    return 0;
}