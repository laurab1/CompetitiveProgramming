#include <iostream>
#include <vector>
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

    void update_aux(int64_t start, int64_t end, int64_t idx, vtype diff, int64_t seg_idx) {
        if(idx < start or idx > end or seg_idx >= st.size())
            return;

        st.at(seg_idx) = Tm::madd(st.at(seg_idx), diff);

        if(start != end) {
            int64_t center = start + (end - start)/2;
            int64_t lch = seg_idx*2+1;
            int64_t rch = seg_idx*2+2;

            update_aux(start, center, idx, diff, lch);
            update_aux(center, end, idx, diff, rch);
        }
    }

    void inc_aux(int64_t start, int64_t end, int64_t idx, vtype val, int64_t seg_idx) {
        if(idx < start or idx > end or seg_idx >= st.size())
            return;

        st.at(seg_idx) = Tm::madd(st.at(seg_idx), val);

        if(start != end) {
            int64_t center = start + (end - start)/2;
            int64_t lch = seg_idx*2+1;
            int64_t rch = seg_idx*2+2;

            inc_aux(start, center, idx, val, lch);
            inc_aux(center, end, idx, val, rch);
        }
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

    void update(vtype val, int64_t idx) {
        if(idx < 0 or idx >= in_size)
            return;

        vtype diff = Tm::gdiff(val, st.at(idx));
        st.at(idx) = val;

        update_aux(0, in_size-1, idx, diff, 0);
    }

    void inc(int64_t idx, vtype val) {
        if(idx < 0 or idx >= in_size)
            return;

        st.at(idx) += val;

        inc_aux(0, in_size-1, idx, val, 0);
    }

    vtype query_sum(int64_t start, int64_t end) {
        if(start < 0 or end >= in_size or start == end)
            return Tm::munit();

        return sum_aux(0, in_size-1, start, end, 0);
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
    int64_t t, n;
    std::cin >> t;
    for(int64_t i = 0; i < t; i++) {
        std::cin >> n;
        std::vector<std::pair<int64_t, int64_t>> es(n-1);
        std::vector<int64_t> costs(n-1);
        for(int64_t j = 0; j < n-1; j++) {
            std::cin >> es.at(j).first >> es.at(j).second >> costs.at(j);
        }
        Graph<monoid<int64_t, add<int64_t>>> graph(n+1, es);
        HeavyLight<monoid<int64_t, add<int64_t>>> path_tree(graph);
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