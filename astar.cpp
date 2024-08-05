// a simple implementation of A*-Algorithm
// the implementation needs a potential function, which is passed
// as a parameter to the function

#include <vector>
#include <queue>


template<typename T, typename Func>
T astar(std::vector<std::vector<std::pair<int, T>>> &graph, int source, int target, T infinity, Func&& potential) {
    std::vector<T> distance(graph.size(), infinity);
    std::vector<bool> visited(graph.size(), false);
    distance[source] = 0;
    std::priority_queue<std::pair<T, int>> prio_queue;

    for (int i=0;i<(int)graph.size();i++) {
        prio_queue.push(std::make_pair(-distance[i]-potential(target, i), i));
    }

    while (!prio_queue.empty()) {
        auto [dist, node] = prio_queue.top();
        prio_queue.pop();
        
        if (node == target) break;
        
        if (visited[node]) continue;
        visited[node] = true;

        for (auto [neighbor, weight] : graph[node]) {
            if (distance[neighbor] > distance[node] + weight) {
                distance[neighbor] = distance[node] + weight;
                prio_queue.push(std::make_pair(-distance[neighbor]-potential(target, neighbor), neighbor));
            }
        }
    }

    return distance[target];
}