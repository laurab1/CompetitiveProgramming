#include <iostream>
#include <vector>
using namespace std;

vector<int> auxvec;
int j = 0;

//node of a tree, according to the problem's specification
struct Node {
    int data;
    Node* left;
    Node* right;
};

//a generic "is_sorted" function
template <typename T> int is_sorted(vector<T> vec) {
    for(int i = 0; i<vec.size()-1; i++)
        if(vec.at(i)>vec.at(i+1))
            return 0;
    return 1;
}

void check_for_BST(Node* root) {
    //performs an inorder traversal and checks if elements are sorted:
    //if they are, then is BST
    if(root == NULL)
        return;
    check_for_BST(root->left);
    auxvec.at(j++) = root->data;
    check_for_BST(root->right);
    cout << is_sorted(auxvec);
}
