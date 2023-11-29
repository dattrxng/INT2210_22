#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

class Edge {
public:
    int u, v, weight;

    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}

    bool operator>(const Edge &other) const {
        return weight > other.weight;
    }
};

void addEdge(vector<vector<pair<int, int>>> &adjList, int u, int v, int weight) {
    adjList[u].emplace_back(v, weight);
    adjList[v].emplace_back(u, weight);
}

void primMST(vector<vector<pair<int, int>>> &adjList, int numVertices, int numEdgesToKeep) {
    vector<bool> visited(numVertices, false);
    priority_queue<Edge, vector<Edge>, greater<Edge>> minHeap;

    int startVertex = 0;

    visited[startVertex] = true;
    for (const auto &neighbor : adjList[startVertex]) {
        minHeap.push({startVertex, neighbor.first, neighbor.second});
    }

    int edgesKept = 0;

    while (edgesKept < numEdgesToKeep && !minHeap.empty()) {
        Edge edge = minHeap.top();
        minHeap.pop();

        int u = edge.u;
        int v = edge.v;
        int weight = edge.weight;

        if (visited[u] && visited[v]) {
            continue;
        }


        if (!visited[u]) {
            visited[u] = true;
            for (const auto &neighbor : adjList[u]) {
                if (!visited[neighbor.first]) {
                    minHeap.push({u, neighbor.first, neighbor.second});
                }
            }
        }

        if (!visited[v]) {
            visited[v] = true;
            for (const auto &neighbor : adjList[v]) {
                if (!visited[neighbor.first]) {
                    minHeap.push({v, neighbor.first, neighbor.second});
                }
            }
        }

        edgesKept++;
    }
}

int main() {
    int numVertices, numEdges;
    cin >> numVertices;

    vector<vector<pair<int, int>>> graph(numVertices);

    cin >> numEdges;

    for (int i = 0; i < numEdges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        addEdge(graph, u, v, weight);
    }

    int numEdgesToKeep;
    cin >> numEdgesToKeep;

    primMST(graph, numVertices, numEdgesToKeep);

    return 0;
}
