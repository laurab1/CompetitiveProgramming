#Code explanation

*Megacity*

We first sort the cities by distance. Then we seek for the index i of the first city such that its population plus the original one sums up to the goal. The result is the distance from this city. If such index does not exist, result is -1. Complexity is O($nlogn$).

*Find pair*

The first element of the pair is k/n. As for the second one, we have to deal with occurrences of the first element: we first compute this value, then the index i of the first occurence. The second element is (k - i*n)/occ. Complexity is O($n$).