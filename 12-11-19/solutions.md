# Code explanation

*Subset sum*

We use again dynamic programming. Solution is similar to the knapsack's one, but matrix values are boolean as, for each subproblem, we only want to check if the current set contains a subset which sums to the current value. Given v, the value each subset should equal, complexity is O(v*n) (pseudo-polynomial).

*Minimum number of jumps*

We iterate over the vector: at each iteration, next element is chosen as the maximum between the previous one and the current element. If next is not reachable, then we return -1, otherwise we count one more jump until we reach the end of the vector. Complexity is O(n).

*Edit distance*

The classic dynamic programming edit distance algorithm: for each substring, if the current characters are equal, we propagate the value over the diagonal, otherwise we compute the edit distance as 1 + the minimum distance between the previous substrings. Complexity is O(m*n), where m and n are the length of the strings. 