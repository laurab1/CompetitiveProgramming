# Code explanation

*N meetings in one room*

We use a greedy approach: sort the meetings by their finishing time, then scan them: each time a meeting does not overlap with the previous ones, add 1 to the result. Complexity is O(nlogn).

*Magic numbers*

We use again a greedy approach, checking chipers three by three and decrementing the step size if the checked number is not a magic one. Complexity is O(n), where n is the size of the input string.

*Wilbur and array*

For each element, we compute the absolute value of the difference between it and its predecessor in the array. We add the computed value to the result. Complexity is O(n).

*Alternative thinking*

We compute the longest alternating sequence by scanning the vector from left to right. The result is the minimum between this value + 2 and the length of the array. Complexity is O(n).