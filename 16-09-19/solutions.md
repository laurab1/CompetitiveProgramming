# Code explanation

*Leaders in array*

We scan the array from right to left: each time a new maximum is found, we store it in a vector and finally print this one in reverse order. Complexity is O(n).

*Kadane's algorithm*

The goal is to find the subarray with maximum sum. While scanning the array, we keep in memory the largest sum found so far. When checking a new element, we add it to sum only if the result is greater or equal than 0. Max is updated if the result is larger than the stored value. Complexity is O(n).

*Missing number in array*

The problem is easily solved by computing the sum of all the elements in the array and the sum of first 
n integers using the Gauss formula. The difference between the latter and the former is the missing number. Complexity is O(n).

*Trapping rain water*

We use two indexes to scan the array right to left and viceversa, stopping when they become equal. The level of water is updated according to the values stored in the array, being at each moment the minimum between the left and right maximum found so far. We update the quantity of trapped water with the difference betweem the (possibly updated) waterlevel and the minimum found. Complexity is O(n).

*Sliding window maximum*

The idea is to use memoization in order to avoid a O($n^2$) solution. We thus use a queue as an auxiliary data structure and we scan the array. At each iteration, we remove from the queue (which is initially empty) the elements which are no longer in the window and those being smaller than the current one. Then we push the current element: the current maximum is thus stored in the queue front. Complexity is O(n).