# Code explanation

*Longest increasing subsequence*

Using dynamic programming, we compute the longest increasing subsequence for each substring of s. Using binary search we get a O(nlogn) solution.

*Longest bitonic subsequence*

Compute lis on the original and reversed string. The solution for the substring of length i is the sum between the length of computed lis on the original and reversed string -1. Complexity is O(n^2).