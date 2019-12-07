#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print(vector<int> vec) {
    size_t size = vec.size();
    for(int i=0; i<size; i++)
        cout << vec.at(i);
    cout << endl;
}

template <class Compare>
  int min_max(vector<int> vec, Compare comp) {
        int min_max = vec.at(0);
          for(size_t i=1; i<vec.size(); i++)
              if(comp(vec.at(i), min_max))
                  min_max = vec.at(i);
          return min_max;
  }

vector<int> counting_sort(vector<int> a) {
        int n = a.size();
        int min = min_max(a, less<int>());
        int max = min_max(a, greater<int>());
        size_t csize = max - min + 1;
        vector<int> count(csize);
        for(size_t i=0; i<csize; i++)
            count.at(i) = 0;
        for(size_t i=0; i<n; i++)
            count.at(a.at(i)-min)++;
        int k = 0;
        for(size_t i=0; i<csize; i++) 
            while(count.at(i)>0) {
                a.at(k) = i + min;
                k++;
                count.at(i)--;
            }
        reverse(a.begin(), a.end());
        return a;
  }

int last_el(string vec) {
    size_t size = vec.size();
    int min;
    int min_odd;
    bool found = false; //to manage the case of all odd numbers
    if((vec.at(0)-'0') % 2 == 0) {
        min = vec.at(0) - '0';
        min_odd = 9; //at least one even number
        found = true;
    } else { 
        min = 8;
        min_odd = vec.at(0) - '0';
    }
    for(int i=1; i<size; i++)
        if((vec.at(i)-'0')%2 == 0) {
            found = true;
            if(vec.at(i)-'0'<min)
                min = vec.at(i)-'0';
        } else {
            if(vec.at(i)-'0'<min_odd)
                min_odd = vec.at(i)-'0';
        }
    
    if(found)
        return min;
    else
        return min_odd;
}

int main() {
    int t; //number of test cases
    cin >> t;
    vector<string> numbers(t);
    
    for(size_t i=0; i<t; i++)
        cin >> numbers.at(i);
    
	//convert strings to arrays of int
    vector<vector<int>> nums(t);
    vector<vector<int>> nums_aux(t);
    
    for(size_t i=0; i<t; i++) {
        int num_len = (numbers.at(i)).length();
        //cout << "num_len is " << num_len << endl;
        int local_min = last_el(numbers[i]);
        //cout << "local_min is " << local_min << endl; 
        nums.at(i) = vector<int>(num_len);
        int k = 0;
        bool found = false; //false 'til I find the min even number for the first time
        for(size_t j=0; j<num_len; j++) {
            int current = (numbers.at(i)).at(j) - '0';
            if(current == local_min && !found) {
                found = true;
            } else {
                (nums.at(i)).at(k) = current;
                k++;
            }
        }
        nums.at(i).at(num_len-1) = local_min;
        for(size_t j=0; j<num_len-1; j++)
            nums_aux.at(i).push_back(nums.at(i).at(j));
    }

    for(size_t i=0; i<t; i++) {
        int len = nums.at(i).size();
        vector<int> result = counting_sort(nums_aux.at(i));
        result.push_back(nums.at(i).at(len-1));
        print(result);
    }
	
	return 0;
}