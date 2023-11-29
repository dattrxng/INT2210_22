#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void addEdge(vector<vector<int>> &adjList, int u, int v) {
    adjList[u].push_back(v);
}

void dfs(vector<vector<int>> &adjList, int v, vector<bool> &visited, vector<int> &stronglyConnectedComponent) {
    visited[v] = true;
    stronglyConnectedComponent.push_back(v);

    for (int neighbor : adjList[v]) {
        if (!visited[neighbor]) {
            dfs(adjList, neighbor, visited, stronglyConnectedComponent);
        }
    }
}

vector<int> getStronglyConnectedComponent(vector<vector<int>> &adjList, int v) {
    int numVertices = adjList.size();
    vector<bool> visited(numVertices, false);
    vector<int> stronglyConnectedComponent;

    dfs(adjList, v, visited, stronglyConnectedComponent);

    return stronglyConnectedComponent;
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

    int startVertex;
    cin >> startVertex;

    vector<int> scc = getStronglyConnectedComponent(graph, startVertex);

    for (int vertex : scc) {
        cout << vertex << " ";
    }

    return 0;
}
