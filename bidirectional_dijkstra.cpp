// dijkstra can be sped up with a bidirectional search, starting from both the source 
// and the target. That way, the number of nodes that need to be considered are not 
// as many as in a normal dijkstra implementation starting from the source.

#include <vector>
#include <queue>

