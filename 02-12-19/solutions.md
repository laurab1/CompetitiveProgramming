# Code explanation

*Lexicographically maximum subsequence*

We scan the string from right to left: each time we find a character which is greater or equal to the current maximum, we add it to the result. Complexity is O(n).

*Woodcutters*

Cut trees on the left until this is possible: then start to cut on the right. If this is not possible, go to the next tree. Complexity is O(n).

*Queue*

Sort people by height, then insert each people in the queue in position i - height_i. Return -1 if the height of a person is greater than the number of people preceeding him. Complexity is O(n).