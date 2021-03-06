#include <bits/stdc++.h>
using namespace std;
#define MAX_HEIGHT 100000

/****** DRIVER CODE ******/

//Tree node
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

bool isBST(Node* root);
int isBSTUtil(struct Node* node, int min, int max);

Node* buildTree(string str) {
    if(str.length() == 0 || str[0] == 'N')
        return NULL;

    vector<string> ip;

    istringstream iss(str);
    for(string str; iss >> str; )
        ip.push_back(str);
    
    Node* root = new Node(stoi(ip[0]));

    queue<Node*> queue;
    queue.push(root);

    int i = 1;
    while(!queue.empty() && i < ip.size()) {
        Node* currNode = queue.front();
        queue.pop();

        string currVal = ip[i];

        if(currVal != "N") {
            currNode->left = new Node(stoi(currVal));
            queue.push(currNode->left);
        }

        i++;
        if(i >= ip.size())
            break;

        currVal = ip[i];

        if(currVal != "N") {
            currNode->right = new Node(stoi(currVal));

            queue.push(currNode->right);
        }
        i++;
    }
    return root;
}

void inorder(Node* root, vector<int> &v) {
    if(root == NULL)
        return;

    inorder(root->left, v);
    v.push_back(root->data);
    inorder(root->right, v);
}

int main() {
    int t;
    string tc;

    getline(cin, tc);
    t = stoi(tc);
    while(t--) {
        string s;
        getline(cin, s);
        Node* root = buildTree(s);
        cout << isBST(root) << endl;
    }

    return 0;
}

/******** SOLUTION ********/

int isBSTUtil(struct Node* node, int min, int max) {
    if(node == NULL)
        return 1;
    
    if(node->data <= min || node->data >= max)
        return 0;

    int check = isBSTUtil(node->left, min, node->data);
    check = check && isBSTUtil(node->right, node->data, max);
}

bool isBST(Node* root) {
    if(root == NULL)
        return true;

    int check = isBSTUtil(root, INT32_MIN, INT32_MAX);
}
