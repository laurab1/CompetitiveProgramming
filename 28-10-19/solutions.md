# Code explanation

*Powerful array*

We use MO's algorithm to solve the queries: sort by left end if they are in different blocks, by right end otherwise. Then process the queries removing the contribution of elements which are no longer in the query window and adding the contribute of new entries. Complexity is O((n + q)*Sqrt(n)).

*Tree and queries*

We use MO's algorithm on trees. First flat the tree using dfs. Then sort queries and process them as before. Add and remove operations count colors occurrences. For each query, the result is the kth element of the occurrences array. Complexity is O((n + q)*Sqrt(n)).