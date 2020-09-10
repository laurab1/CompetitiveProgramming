#Code explanation

*Ilya and queries*

As we are dealing with static queries, we precompute the prefix sums of the string and answer each query. Complexity is O($n + q$) for a string of length $n$.

*Alice, Bob and chocolate*

Again we use prefix sums to compute the amount of time needed to consume the bars. We then iterate over the vector of bars, decreasing the available time each time we add a bar to the number of bars consumed by Alice. Left bars are consumed by Bob. Complexity is O($n$).

*Number of ways*

If sum%3 is different than 0, then result is impossible. Otherwise, we compute the prefix sums of the input vector and place 1 in an aux vector each time the current value is equal to sum/3. We then find the position j of the elements equal to sum/3 and add the value in position j+2 of vector aux to the result. Complexity is O($n$).

*Little girl and maximum sum*

For each query, we compute the frequency of the queries and then compute prefix sums of the frequency vector. We then sort both the vector of prefix sums and the input vector. Finally, we compute the result as the sum of the frequency prefix sums times the corresponding value in the input vector. Complexity is O($(q+n)logn)$.