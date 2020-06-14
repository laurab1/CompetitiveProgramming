#include <iostream>
#include <vector>

typedef struct test_struct {
    int size;
    std::vector<long> vec;
} test_t;

int merge(std::vector<long>& a, int l, int c, int r) { 
    int i = l;
    int j = c + 1;
    int n = 1 + (r-l);
    std::vector<long> aux(n);
    size_t k = 0;
    uint64_t n_invs = 0;
    
    while((i <= c) && (j <= r)) {
      if(a[i] < a[j]) {
        aux[k++] = a[i++];
      } else {
        aux[k++] = a[j++];
        n_invs += c-i+1;
      }
    }
    
    while(i <= c) {
      aux[k++] = a[i++];
    }
    
    while(j <= r) {
      aux[k++] = a[j++];
    }

    auto jt = a.begin() + l;
    for(auto it = aux.begin(); it != aux.end(); it++)
        *jt++ = *it;
    
    return n_invs;
}

int count_mergesort(std::vector<long>& vec, int l, int r) 
{ 
    if(l >= r)
        return 0;
    int c = (l+r)/2; 
    int left_invs = count_mergesort(vec, l, c); 
    int right_invs = count_mergesort(vec, c+1, r);
    return left_invs + right_invs + merge(vec, l, c, r);;
} 
void inversion_count(test_t test) {
    int inversions = count_mergesort(test.vec,0,test.size);
    std::cout << inversions << std::endl;
}

int main() {
    int num_tests;
    std::cin >> num_tests;
    std::vector<test_t> tests(num_tests);
    for(auto it = tests.begin(); it != tests.end(); it++) {
        std::cin >> it->size;
        long num;
        for(int j = 0; j < it->size; j++) {
            std::cin >> num;
            it->vec.push_back(num);
        }
    }

    for(auto it = tests.begin(); it != tests.end(); it++)
        inversion_count(*it);

    return 0;
}