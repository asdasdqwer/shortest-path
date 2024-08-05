// a compilation of algorithms for finding good landmarks in large graphs

#include <vector>
#include <queue>

// the following algorithm first executes a dijkstra 
// starting from an arbitrary node, and then selects the farthest node
// and adds it to the set, executes a dijkstra from the node again and so on...
template<typename T>
std::vector<int> basic_greedy(std::vector<std::vector<std::pair<int, T>>> &graph, int startNode, int number_nodes_in_landmark, T infinity) {
    std::vector<T> distance(graph.size(), infinity);
    std::vector<int> nodes_of_landmark;

    for (int i=0;i<number_nodes_in_landmark;i++) {
        int node_in_this_iteration;
        if (i == 0) node_in_this_iteration = startNode;
        else {
            T maxValue = 0;
            for (int j = 0;j<(int)graph.size();j++) {
                if (distance[j] > maxValue) {
                    maxValue = distance[j];
                    node_in_this_iteration = j;
                }
            }
        }

        nodes_of_landmark.push_back(node_in_this_iteration);

        std::priority_queue<std::pair<T, int>> prio_queue;
        distance[node_in_this_iteration] = 0;
        prio_queue.insert({0, node_in_this_iteration});
        
        std::vector<bool> visited(graph.size(), false);

        while (!prio_queue.empty()) {
            auto [dist, node] = prio_queue.top();
            prio_queue.pop();

            if (visited[node]) continue;
            visited[node] = true;

            for (auto [neighbor, weight] : graph[node]) {
                if (distance[node] + weight < distance[neighbor]) {
                    distance[neighbor] = distance[node] + weight;
                    pq.push({-distance[neighbor], neighbor});
                }
            }
        }
    }
}