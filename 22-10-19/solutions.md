# Code explanation

*Circular RMQ*

We use a segment tree with lazy update. As a "sum" operation we use the minimum between two values. Update and queries are performed as usual if l < r, otherwise we split the interval. Complexity is O((n + q)logn).