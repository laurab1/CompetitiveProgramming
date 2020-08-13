#include <iostream>
#include <vector>
#include <string>
using namespace std;

//a template function to compute the prefix sums for a given vector
//returns a new vector of prefix sums
template <class T>
vector<int> prefix_sum(vector<T> vec, bool (*compare) (T,T)) {
    vector<int> sums(vec.size()+1);
    sums[0] = 0;

    for(size_t i = 1; i<vec.size(); i++)
        sums[i] = compare(vec[i-1],vec[i])?sums[i-1]+1:sums[i-1];
    sums[vec.size()] = sums[vec.size()-1];

    return sums;
}

//compare function to be passed to the prefix_sum function
bool comp(char a, char b) {
    return a == b;
}

int main() {
    string str;
    size_t queries = 0;
    int left = 0;
    int right = 0;

    cin >> str;
    //prefix_sum won't work with strings: I need to convert the
    //input string to a vector<char>
    vector<char> s(str.length());
    for(size_t i=0; i<str.length(); i++)
        s[i] = str[i];
    vector<int> prefsums = prefix_sum(s,comp);

    //get the queries and answer them
    cin >> queries;
    for(size_t i=0; i<queries; i++) {
        cin >> left;
        cin >> right;
        cout << prefsums[right-1]-prefsums[left-1] << endl;
    }

    return 0;
}
