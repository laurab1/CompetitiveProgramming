#include <iostream>

//an aux function to compute the mas_sum_path
int max_sum_path(struct Node* root, int *max_sum) {
    //if node is NULL or node is a leaf
    //then max_sum_path is either INT_MIN or root->data
    if(root == NULL)
        return INT_MIN;
    if(root->left == NULL || root->right == NULL)
        return root->data;

    //compute the left path and right path
    //then compute the current max path between left and right
    int left_sum = max_sum_path(root->left, max_sum);
    int right_sum = max_sum_path(root->right, max_sum);
    int curr_sum = root->data;
    curr_sum += left_sum>right_sum?left_sum:right_sum;

    if(right_sum != INT_MIN && left_sum != INT_MIN) {
        int tmp = root->data + left_sum + right_sum;
        //if tmp is greater than the current maximum, then it is the new one
        *max_sum = tmp>*max_sum?tmp:*max_sum;
    }
    
    return curr_sum;
}

//calls the aux function which computes the max_sum_path
int maxSumPath(struct Node* root) {
    int max_sum = INT_MIN;
    max_sum_path(root, &max_sum);
    return max_sum;
}
