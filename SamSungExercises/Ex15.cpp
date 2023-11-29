#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void addEdge(vector<vector<int>> &adjList, vector<int> &indegree, int u, int v) {
    adjList[u].push_back(v);
    indegree[v]++;
}

void topologicalSort(vector<vector<int>> &adjList, vector<int> &indegree) {
    int numVertices = adjList.size();

    queue<int> q;
    for (int i = 0; i < numVertices; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        cout << u << " ";

        for (int v : adjList[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }
}

int main() {
    int numVertices, numEdges;
    cin >> numVertices;

    vector<vector<int>> graph(numVertices);
    vector<int> indegree(numVertices, 0);

    cin >> numEdges;

    for (int i = 0; i < numEdges; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(graph, indegree, u, v);
    }

    topologicalSort(graph, indegree);

    return 0;
}
