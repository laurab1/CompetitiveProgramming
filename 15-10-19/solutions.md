# Code explanation

*Nested segments*

Sort the enpoints of the segments in a separate vector, then sort the segments by left endpoint. Iterate over the segments vector and perform an update on the BIT at index r with value 1. Iterate again and query the index r, then remove 1 from that. Finally output the queries result vector. Complexity is O(nlogn).

*Pashmak and Parmida's problem*

We first sort the input vector and recompute its values as 0 based. We scan the vector from right to left and update the occurrences of each value and build a BIT on the occurrences vector values. We repeat this operation scanning the vector from left to right. Finally we query the BIT subtracting 1 each time a query is processed, to remove the constribut of already processed entries. Complexity is O(nlogn).