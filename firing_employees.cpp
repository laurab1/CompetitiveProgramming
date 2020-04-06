#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <math.h>
using namespace std;

//node of the tree
typedef struct node {
    int rnk;
    int superior;
    int sum; //number of superiors
    bool checked = false;
    node* parent;
    vector<node*> children;
    node(int r, int s) : rnk(r), superior(s), sum(0) {}

    //overload of the greater() operator:
    //needed to sort employees in descending order w.r.t their superior
    bool operator > (const node& str) const
    {
        return (superior > str.superior);
    }
} node_t;

bool is_prime(int num) {
    for(int i=2; i<=sqrt(num); i++)
        if(num%i == 0)
            return false;
    return true;
}

int main() {
    int t;
    cin >> t;
    vector<vector<int>> tests(t);
    for(size_t i=0; i<t; i++) {
        int n = 0;
        cin >> n;
        tests.at(i) = vector<int>(n);
        for(int j=0; j<n; j++) {
            int sup_rnk = 0;
            cin >> sup_rnk;
            tests.at(i).at(j) = sup_rnk;
        }
    }
    for(size_t i=0; i<t; i++) {
        int black_listed = 0;
        vector<node_t> employees;
        for(size_t j=0; j<tests.at(i).size(); j++) {
            employees.push_back(node_t(j+1, tests.at(i).at(j)));
        }
        size_t n = employees.size();
        sort(employees.begin(), employees.end(), greater<node_t>());
        for(size_t j=0; j<n; j++) { //build a tree
            int sup_j = employees.at(j).superior;
            if(sup_j == 0)
                employees.at(j).parent = nullptr; //Mr. Alfred is the root
            else {
                employees.at(j).parent = &(employees.at(sup_j-1));
                employees.at(j).parent->children.push_back(&employees.at(j));
            }
        }
        for(size_t i=n-1; i>0; i--) {
            auto emp = employees.at(i);
            for(size_t j = 0; j<emp.children.size(); j++) {
                emp.children.at(j)->sum = emp.sum + 1;
                int check = emp.children.at(j)->rnk + emp.children.at(j)->sum;
                if(!emp.children.at(j)->checked && is_prime(check))
                    black_listed++;
                emp.children.at(j)->checked = true;
            }
        }
        std::cout << black_listed << endl;
    }
}