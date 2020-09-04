#Code explanation

*Learning languages*

We build a graph where each node is an employee and two nodes are connected if the employees share a common language. Then we count connected components: the number of languages to be learnt is the number of ccs -1. Complexity is O($n + m$).

*Checkposts*

We count the number of connected components and, for each of them, we select the node with minimum costs. If more of one node has the same (minimum) cost, than we increase the number of ways we have to protect the city. Complexity is O($n + m$).