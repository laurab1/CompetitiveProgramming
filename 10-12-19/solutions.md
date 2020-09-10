#Code explanation

*Minimum  spanning tree*

After sorting edges in ascending order of weights, we create a disjoint set structure and iterate over edges: each time two endpoints of the same edge don't belong to the same set, we compute the union of their sets and add the weight to the result. Complexity is O($mlogn$).