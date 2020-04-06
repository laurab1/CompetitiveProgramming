#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {

    int towers = 0;
    int height = 1;
    int size;
    cin >> size;
    vector<int> seq(size);

    for(int i=0; i<size; i++)
        cin >> seq[i];

    sort(seq.begin(), seq.end());
    int auxheight = 0;
    int auxlength = 0;

    for(int j=0; j<size; j++) {
        if(auxlength == seq[j]) {
            auxheight++;
            height = (auxheight>height)?auxheight:height;
        } else {
            auxlength = seq[j];
            auxheight = 1;
            towers++;
        } 
    }

    cout << height << " " << towers << endl;

    return 0;
}
