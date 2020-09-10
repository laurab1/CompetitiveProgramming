# Code explanation

*Longest palindromic subsequence*

Compute the longest common subsequence of the original and reversed string. Complexity is O(n^2).

*Vertex cover*

NOTE: this solution does not pass the online judge. <br/>
Solution is the minimum between the number of "guards" if the root is covered and the number of guards if the root is not covered. Base case are on the leaves, where we return the propagated guarded value. Complexity is O(n^2).