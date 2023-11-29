#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

struct Edge {
    int src, dest, weight;
};

class Graph {
public:
    int V, E;
    vector<Edge> edges;

    Graph(int V, int E) : V(V), E(E) {}

    void addEdge(int src, int dest, int weight) {
        Edge edge = {src, dest, weight};
        edges.push_back(edge);
    }

    void bellmanFord(vector<int>& pi) {
        pi.assign(V, INT_MAX);
        pi[0] = 0;

        for (int i = 1; i <= V - 1; ++i) {
            for (const auto& edge : edges) {
                int u = edge.src;
                int v = edge.dest;
                int weight = edge.weight;

                if (pi[u] != INT_MAX && pi[u] + weight < pi[v]) {
                    pi[v] = pi[u] + weight;
                }
            }
        }
    }

    void reweightGraph(vector<int>& pi) {
        for (auto& edge : edges) {
            edge.weight = edge.weight + pi[edge.src] - pi[edge.dest];
        }
    }

    void dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const auto& edge : edges) {
                int v = edge.dest;
                int weight = edge.weight;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Shortest distances from source " << src << ":\n";
        for (int i = 0; i < V; ++i) {
            cout << "To vertex " << i << ": " << dist[i] << endl;
        }
    }
};

int main() {
    int V = 5;
    int E = 8;

    Graph graph(V, E);

    graph.addEdge(0, 1, -1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 2);
    graph.addEdge(3, 2, 5);
    graph.addEdge(3, 1, 1);
    graph.addEdge(4, 3, -3);

    vector<int> pi;
    graph.bellmanFord(pi);

    graph.reweightGraph(pi);

    graph.dijkstra(0);

    return 0;
}
