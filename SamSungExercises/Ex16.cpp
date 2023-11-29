#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Edge {
public:
    int u, v, weight;

    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}

    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
};

int findSet(vector<int> &parent, int i) {
    if (parent[i] == -1) {
        return i;
    }
    return findSet(parent, parent[i]);
}

void unionSets(vector<int> &parent, int x, int y) {
    int rootX = findSet(parent, x);
    int rootY = findSet(parent, y);
    parent[rootX] = rootY;
}

void kruskalMST(vector<Edge> &edges, int numVertices) {
    vector<int> parent(numVertices, -1);
    vector<Edge> minimumSpanningTree;

    sort(edges.begin(), edges.end());

    for (const Edge &edge : edges) {
        int rootU = findSet(parent, edge.u);
        int rootV = findSet(parent, edge.v);

        if (rootU != rootV) {
            minimumSpanningTree.push_back(edge);
            unionSets(parent, rootU, rootV);
        }
    }

    for (const Edge &edge : minimumSpanningTree) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }
}

void primMST(vector<vector<pair<int, int>>> &adjList, int numVertices) {
    vector<bool> visited(numVertices, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int startVertex = 0;
    pq.push({0, startVertex});

    while (!pq.empty()) {
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        for (const auto &neighbor : adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (!visited[v]) {
                pq.push({weight, v});
            }
        }
    }
}

int main() {
    int numVertices, numEdges;
    cin >> numVertices;

    vector<vector<pair<int, int>>> graph(numVertices);
    vector<Edge> edges;

    cin >> numEdges;

    for (int i = 0; i < numEdges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph[u].emplace_back(v, weight);
        graph[v].emplace_back(u, weight);
        edges.emplace_back(u, v, weight);
    }

    primMST(graph, numVertices);

    kruskalMST(edges, numVertices);

    return 0;
}
