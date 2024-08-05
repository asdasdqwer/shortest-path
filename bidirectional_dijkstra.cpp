// dijkstra can be sped up with a bidirectional search, starting from both the source 
// and the target. That way, the number of nodes that need to be considered are not 
// as many as in a normal dijkstra implementation starting from the source.

#include <vector>
#include <queue>

// this implementation stops as soon as there is a node that has been visited by both
// has been visited by both traversals

template<typename T> T bidirectional_search(std::vector<std::vector<std::pair<int, T>>> &graph, std::vector<std::vector<std::pair<int, T>>> &reversed_graph, int source, int target, T infinity) {
    std::vector<T> distanceFromSource(graph.size(), infinity), distanceFromTarget(graph.size());
    std::vector<bool> visitedFromSource(graph.size(), false), visitedFromTarget(graph.size(), false);
    distanceFromSource[source] = 0;
    distanceFromTarget[target] = 0;

    std::priority_queue<std::pair<T, int>> prio_queue_source, prio_queue_target;

    for (int i=0;i<(int)graph.size();i++) {
        prio_queue_source.push(std::make_pair(-distanceFromSource[i], i));
        prio_queue_target.push(std::make_pair(-distanceFromTarget[i], i));
    }

    T distance_between_source_and_target = infinity;

    while (!prio_queue_source.empty()) {
        auto [dist, node] = prio_queue_source.top();
        prio_queue_source.pop();

        if (visitedFromSource[node]) continue;
        visitedFromSource[node] = true;

        if (visitedFromTarget[node]) {
            return distanceFromSource[node] + distanceFromTarget[node];
        }

        for (auto [neighbor, weight] : graph[node]) {
            if (distanceFromSource[neighbor] > distanceFromSource[node] + weight) {
                distanceFromSource[neighbor] = distanceFromSource[node] + weight;
                prio_queue_source.push(std::make_pair(-distanceFromSource[neighbor], neighbor));
            }
        }

        while (!prio_queue_target.empty()) {
            auto [dist, node] = prio_queue_target.top();
            prio_queue_target.pop();

            if (visitedFromTarget[node]) continue;
            visitedFromTarget[node] = true;

            if (visitedFromSource[node]) {
                return distanceFromSource[node] + distanceFromTarget[node];
            }

            for (auto [neighbor, weight] : reversed_graph[node]) {
                if (distanceFromTarget[neighbor] > distanceFromTarget[node] + weight) {
                    distanceFromTarget[neighbor] = distanceFromTarget[node] + weight;
                    prio_queue_target.push(std::make_pair(-distanceFromTarget[neighbor], neighbor));
                }
            }

            // only one node should be visited by this loop
            break;
        }
    }

    return infinity;
}