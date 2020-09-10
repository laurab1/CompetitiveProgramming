# Code explanation

*Firing employees*

We compute the seniors of each employee using a stack: we iterate over the number of employees and, at each iteration, we consider the vector of positions for the index which is currently on top of the stack.
We scan the vector from right to left in order to compute seniors for each employee. Complexity is O(n).

*Check for BST*

The algorithm performs an inorder visit of the tree. We keep trace of the current minimum and maximum in order to check that the BST property holds. This is true as long as both subtrees of the current node are BSTs. Complexity is O(n).

*Preorder traversal and BST*

We iterate over the elements of the vector: for each element, we first check if it is smaller than the current root value: if this is true, we return 0. Otherwise, we iterate over the elements in the stack to check the property over the left subtree. Complexity is O(n).

*Maximum path sum*

We recursively compute the maximum path sum for each subtree: this is the max between left sum and right sum. Complexity is O(n).