#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void topologicalSort(vector<vector<int>> &graph, vector<int> &order, vector<bool> &visited, int node) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            topologicalSort(graph, order, visited, neighbor);
        }
    }
    order.push_back(node);
}

bool isHamiltonianPath(vector<vector<int>> &graph) {
    vector<int> order;
    vector<bool> visited(graph.size(), false);

    for (int i = 0; i < graph.size(); i++) {
        if (!visited[i]) {
            topologicalSort(graph, order, visited, i);
        }
    }

    reverse(order.begin(), order.end());

    for (int i = 0; i < order.size() - 1; i++) {
        int u = order[i];
        int v = order[i + 1];

        bool found = false;
        for (int neighbor : graph[u]) {
            if (neighbor == v) {
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    if (isHamiltonianPath(graph)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
