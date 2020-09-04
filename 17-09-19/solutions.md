#Code explanation

*Next larger element*

We use a stack as a support data structure. While scanning the vector from right to left, we pop an element from the stack as long as the current one is grater than the former. We stop popping as the top element of the stack is greater than the current one or the stack is empty: should it be the case, there is no greater element than the current one, thus we output -1. Otherwise, we output the stack top. Finally, we push the current element on the stack. Complexity is O($n$).

*Towers*

We use a greedy approach: after sorting the vector, we take two counters: the first one is the current length, while the second one is the current height. If the vector element is equal to the current length, we add one to the current height, updating the maximum height if the former is greater. Otherwise, the current height is set to 1 and the current length is set to the vector element. Complexity is O($n$).

*Finding team members*

Again we use a greedy approach. First, we generate all possible teams: then, teams are sort by strength in descending order. Finally, we scan the sorted array and assign mates as we find them in the teams. Complexity is O($n$).