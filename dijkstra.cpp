// contains a basic dijkstra implementation using priority queues
// the operation "decrease-key" is not going to be used throughout the implementation

#include <vector>
#include <queue>

template<typename T> std::vector<T> dijkstra(std::vector<std::vector<std::pair<int, T>>> &g, int source, T infinity) {
    std::vector<T> distance(g.size(), infinity);
    std::vector<bool> visited(g.size(), false);
    distance[source] = 0;
    std::priority_queue<std::pair<T, int>> prio_queue;

    for (int i=0;i<(int)g.size();i++) {
        prio_queue.push(std::make_pair(-distance[i], i));
    }

    while (!prio_queue.empty()) {
        auto [dist, node] = prio_queue.top();
        prio_queue.pop();

        if (visited[node]) continue;
        visited[node] = true;

        for (auto [neighbor, weight] : g[node]) {
            if (distance[neighbor] > distance[node] + weight) {
                distance[neighbor] = distance[node] + weight;
                prio_queue.push(std::make_pair(-distance[neighbor], neighbor));
            }
        }
    }

    return distance;
}

// this function just returns the distance between the source and a target
template<typename T> T dijkstra(std::vector<std::vector<std::pair<int, T>>> &g, int source, int target, T infinity) {
    std::vector<T> distance(g.size(), infinity);
    std::vector<bool> visited(g.size(), false);
    distance[source] = 0;
    std::priority_queue<std::pair<T, int>> prio_queue;

    for (int i=0;i<(int)g.size();i++) {
        prio_queue.push(std::make_pair(-distance[i], i));
    }

    while (!prio_queue.empty()) {
        auto [dist, node] = prio_queue.top();
        prio_queue.pop();

        if (node == target) break;

        if (visited[node]) continue;
        visited[node] = true;

        for (auto [neighbor, weight] : g[node]) {
            if (distance[neighbor] > distance[node] + weight) {
                distance[neighbor] = distance[node] + weight;
                prio_queue.push(std::make_pair(-distance[neighbor], neighbor));
            }
        }
    }

    return distance[target];
}