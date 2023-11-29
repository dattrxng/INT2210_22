#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void addEdge(vector<vector<int>> &adjList, int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

void removeEdge(vector<vector<int>> &adjList, int u, int v) {
    adjList[u].erase(remove(adjList[u].begin(), adjList[u].end(), v), adjList[u].end());
    adjList[v].erase(remove(adjList[v].begin(), adjList[v].end(), u), adjList[v].end());
}

void dfs(int node, vector<bool> &visited, const vector<vector<int>> &adjList) {
    visited[node] = true;
    for (int neighbor : adjList[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, visited, adjList);
        }
    }
}

bool isGraphConnected(const vector<vector<int>> &adjList) {
    vector<bool> visited(adjList.size(), false);
    dfs(0, visited, adjList);

    for (bool isVisited : visited) {
        if (!isVisited) {
            return false;
        }
    }

    return true;
}

bool isEdgeConnected(vector<vector<int>> &adjList) {
    for (int u = 0; u < adjList.size(); ++u) {
        for (int v : adjList[u]) {
            removeEdge(adjList, u, v);
            bool connected = isGraphConnected(adjList);
            addEdge(adjList, u, v);

            if (!connected) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    int numVertices, numEdges;
    cin >> numVertices;

    vector<vector<int>> graph(numVertices);

    cin >> numEdges;

    for (int i = 0; i < numEdges; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(graph, u, v);
    }

    if (isEdgeConnected(graph)) {
        cout << "The graph is edge-connected." << endl;
    } else {
        cout << "The graph is not edge-connected." << endl;
    }

    return 0;
}
