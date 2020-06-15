#include <bits/stdc++.h>
using namespace std;

/********* DRIVER CODE *********/

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

Node *buildTree(string str) {
    // Corner Case
    if (str.length() == 0 || str[0] == 'N') return NULL;

    // Creating vector of strings from input
    // string after spliting by space
    vector<string> ip;

    istringstream iss(str);
    for (string str; iss >> str;) ip.push_back(str);

    // Create the root of the tree
    Node *root = new Node(stoi(ip[0]));

    // Push the root to the queue
    queue<Node *> queue;
    queue.push(root);

    // Starting from the second element
    int i = 1;
    while (!queue.empty() && i < ip.size()) {

        // Get and remove the front of the queue
        Node *currNode = queue.front();
        queue.pop();

        // Get the current Node's value from the string
        string currVal = ip[i];

        // If the left child is not null
        if (currVal != "N") {

            // Create the left child for the current Node
            currNode->left = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->left);
        }

        // For the right child
        i++;
        if (i >= ip.size()) break;
        currVal = ip[i];

        // If the right child is not null
        if (currVal != "N") {

            // Create the right child for the current Node
            currNode->right = new Node(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->right);
        }
        i++;
    }

    return root;
}

int maxPathSum(Node *);

int main() {
    int tc;
    scanf("%d ", &tc);
    while (tc--) {
        string treeString;
        getline(cin, treeString);
        Node *root = buildTree(treeString);
        cout << maxPathSum(root) << "\n";
    }
    return 0;
}

/********* SOLUTION *********/

int max_path_sum(struct Node* root, int* max_sum) {
    if(root == NULL)
        return 0;
    if(root->left == NULL && root->right == NULL)
        return root->data;

    int left_sum = max_path_sum(root->left, max_sum);
    int right_sum = max_path_sum(root->right, max_sum);
    int curr_sum = root->data;
    

    if(root->left && root->right) {
        int tmp = left_sum + right_sum + curr_sum;
        *max_sum = (*max_sum >= tmp)?*max_sum:tmp;
        int max = (left_sum >= right_sum)?left_sum:right_sum;

        return max + root->data;
    }

    if(root->left == NULL) {
        curr_sum += right_sum;
    } else
        curr_sum += left_sum;
    
    return curr_sum;
}

int maxPathSum(struct Node* root) {
    int max_sum = INT_MIN;
    max_path_sum(root, &max_sum);
    return max_sum;
}
