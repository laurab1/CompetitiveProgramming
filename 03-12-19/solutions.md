# Code explanation

*X total shapes*

We consider each cell as a node in a graph: we then run on any unvisited X cell until we keep on finding an X shape in the neighbourhood. Each time a new dfs is started we add 1 to the result. Complexity is O(n + m).

*Is bipartite*

We run dfs propagating alternating colors, 0 and 1. If we find a node which is already colored with the current color, we return false, otherwise we return true. Complexity is O(n + m).

*Fox and names*

We create a graph where each node is a character in the alphabet. Each time two strings contain different characters, we connect them with an edge. We then run dfs on the resulting graph: if we detect a back edge, then the result is impossible, otherwise we recur and then push the current node in the result stack. Complexity is O(n + m).