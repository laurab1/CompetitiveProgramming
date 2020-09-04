#Code explanation

*Invertion count*

The problem is easily solved by sorting the array using merge sort: each time an inversion is found, we increase a global counter by 1. Complexity is O($nlogn$).

*Largest even number*

We first scan the number in order to find the minimum even cipher. Then we sort ciphers in descending order and we put the minimum even at the end. As we know the range of ciphers we can use counting sort, thus complexity is O($n$).