#include <iostream>
#include <vector>
#include <stack>
#include <limits>
#include <algorithm>

using namespace std;

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }

    void longestPath(int src) {
        stack<int> s;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, s);
            }
        }

        vector<int> dist(V, INT_MIN);
        dist[src] = 0;

        while (!s.empty()) {
            int u = s.top();
            s.pop();

            if (dist[u] != INT_MIN) {
                for (const auto& neighbor : adj[u]) {
                    int v = neighbor.first;
                    int w = neighbor.second;

                    if (dist[u] + w > dist[v]) {
                        dist[v] = dist[u] + w;
                    }
                }
            }
        }

        for (int i = 0; i < V; ++i) {
            cout << i << ": ";
            if (dist[i] == INT_MIN) {
                cout << "INF" << endl;
            } else {
                cout << dist[i] << endl;
            }
        }
        cout << endl;
    }

private:
    void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& s) {
        visited[v] = true;

        for (const auto& neighbor : adj[v]) {
            int u = neighbor.first;
            if (!visited[u]) {
                topologicalSortUtil(u, visited, s);
            }
        }

        s.push(v);
    }
};

int main() {
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 1);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);

    int src = 1;
    cout << "The longest path from " << src << " to \n";
    g.longestPath(src);

    return 0;
}
