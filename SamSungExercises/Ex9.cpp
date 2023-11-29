#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void addEdge(vector<vector<int>> &adjList, int u, int v) {
    adjList[u].push_back(v);
}

bool isEulerianCycle(vector<vector<int>> &adjList, int numVertices) {
    vector<bool> visited(numVertices, false);
    dfs(adjList, 0, visited);
    for (bool v : visited) {
        if (!v) {
            cout << "Do thi khong lien thong" << endl;
            return false;
        }
    }

    for (int i = 0; i < numVertices; ++i) {
        int inDegree = 0, outDegree = adjList[i].size();
        for (int neighbor : adjList[i]) {
            ++inDegree;
        }
        if (inDegree != outDegree) {
            return false;
        }
    }

    return true;
}

void dfs(vector<vector<int>> &adjList, int start, vector<bool> &visited) {
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int u = s.top();
        s.pop();

        if (!visited[u]) {
            visited[u] = true;

            for (int v : adjList[u]) {
                s.push(v);
            }
        }
    }
}

void eulerianCycle(vector<vector<int>> &adjList, int numVertices) {
    if (!isEulerianCycle(adjList, numVertices)) {
        return;
    }

    stack<int> path;
    vector<int> circuit;

    path.push(0);

    while (!path.empty()) {
        int u = path.top();

        if (adjList[u].empty()) {
            circuit.push_back(u);
            path.pop();
        } else {
            int v = adjList[u].back();
            adjList[u].pop_back();
            path.push(v);
        }
    }

    for (int i = circuit.size() - 1; i >= 0; --i) {
        cout << circuit[i] << " ";
    }
    cout << endl;
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

    eulerianCycle(graph, numVertices);

    return 0;
}
