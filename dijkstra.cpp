// contains a basic dijkstra implementation using priority queues
// the operation "decrease-key" is not going to be used throughout the implementation

#include <vector>
#include <queue>

// the graph should be passed as an adjacency list
// the datatype used for describing a neighbor node is a pair, where
// the first object contains the index of the neighbor node and the second
// object the weight of the incident edge
template<typename T> std::vector<T> dijkstra(std::vector<std::vector<std::pair<int, T>>> &graph, int source, T infinity) {
    std::vector<T> distance(graph.size(), infinity);
    std::vector<bool> visited(graph.size(), false);
    distance[source] = 0;
    std::priority_queue<std::pair<T, int>> prio_queue;

    for (int i=0;i<(int)graph.size();i++) {
        prio_queue.push(std::make_pair(-distance[i], i));
    }

    while (!prio_queue.empty()) {
        auto [dist, node] = prio_queue.top();
        prio_queue.pop();

        if (visited[node]) continue;
        visited[node] = true;

        for (auto [neighbor, weight] : graph[node]) {
            if (distance[neighbor] > distance[node] + weight) {
                distance[neighbor] = distance[node] + weight;
                prio_queue.push(std::make_pair(-distance[neighbor], neighbor));
            }
        }
    }

    return distance;
}

// this function just returns the distance between the source and a target
template<typename T> T dijkstra(std::vector<std::vector<std::pair<int, T>>> &graph, int source, int target, T infinity) {
    std::vector<T> distance(graph.size(), infinity);
    std::vector<bool> visited(graph.size(), false);
    distance[source] = 0;
    std::priority_queue<std::pair<T, int>> prio_queue;

    for (int i=0;i<(int)graph.size();i++) {
        prio_queue.push(std::make_pair(-distance[i], i));
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
                prio_queue.push(std::make_pair(-distance[neighbor], neighbor));
            }
        }
    }

    return distance[target];
}

