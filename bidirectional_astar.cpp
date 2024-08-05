// the following contains three implementations for an bidirectional A* algorithm
// the differences between them lay in the termination criterion

#include <queue>
#include <vector>

template<typename T, typename Func>
T astar_first(std::vector<std::vector<std::pair<int, T>>> &graph, std::vector<std::vector<std::pair<int, T>>> &reverse_graph, 
              int source, int target, T infinity, Func&& potential_forward, Func&& potential_backward) {
    std::vector<T> distanceFromSource(graph.size(), infinity), distanceFromTarget(graph.size());
    std::vector<bool> visitedFromSource(graph.size(), false), visitedFromTarget(graph.size(), false);
    distanceFromSource[source] = 0;
    distanceFromTarget[target] = 0;

    std::priority_queue<std::pair<T, int>> prio_queue_source, prio_queue_target;

    for (int i=0;i<(int)graph.size();i++) {
        prio_queue_source.push(std::make_pair(-distanceFromSource[i] - potential_forward(target, i), i));
        prio_queue_target.push(std::make_pair(-distanceFromTarget[i] - potential_backward(source, i), i));
    }

    T distance_between_source_and_target = infinity;

    while (!prio_queue_source.empty()) {
        auto [dist, node] = prio_queue_source.top();
        prio_queue_source.pop();

        if (-dist > distance_between_source_and_target) {
            return distance_between_source_and_target;
        }

        if (visitedFromSource[node]) continue;
        visitedFromSource[node] = true;

        if (visitedFromTarget[node]) {
            distance_between_source_and_target = min(distance_between_source_and_target, distanceFromSource[node] + distanceFromTarget[node]);
        }

        for (auto [neighbor, weight] : graph[node]) {
            if (distanceFromSource[neighbor] > distanceFromSource[node] + weight) {
                distanceFromSource[neighbor] = distanceFromSource[node] + weight;
                prio_queue_source.push(std::make_pair(-distanceFromSource[neighbor] - potential_forward(target, neighbor), neighbor));
            }
        }

        while (!prio_queue_target.empty()) {
            auto [dist, node] = prio_queue_target.top();
            prio_queue_target.pop();

            if (-dist > distance_between_source_and_target) {
                return distance_between_source_and_target;
            }

            if (visitedFromTarget[node]) continue;
            visitedFromTarget[node] = true;

            if (visitedFromSource[node]) {
                distance_between_source_and_target = min(distance_between_source_and_target, distanceFromSource[node] + distanceFromTarget[node]);
            }

            for (auto [neighbor, weight] : reversed_graph[node]) {
                if (distanceFromTarget[neighbor] > distanceFromTarget[node] + weight) {
                    distanceFromTarget[neighbor] = distanceFromTarget[node] + weight;
                    prio_queue_target.push(std::make_pair(-distanceFromTarget[neighbor] + potential_backward(source, neighbor), neighbor));
                }
            }

            // only one node should be visited by this loop
            break;
        }
    }

    return infinity;
}
