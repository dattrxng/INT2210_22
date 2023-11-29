#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(int v, vector<vector<int>> &graph, vector<bool> &visited, stack<int> &st) {
    visited[v] = true;
    for (int neighbor: graph[v]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, st);
        }
    }
    st.push(v);
}

void topologicalSort(vector<vector<int>> &graph, vector<int> &res) {
    int v = graph.size() - 1;
    vector<bool> visited(v + 1, false);
    stack<int> st;

    // Duyệt DFS để lấy thứ tự topological
    for (int i = 1; i <= v; i++) {
        if (!visited[i]) {
            dfs(i, graph, visited, st);
        }
    }

    int topo = 1;
    while (!st.empty()) {
        int vertex = st.top();
        st.pop();
        res[vertex] = topo++;
    }
}

int main() {
    int vertices, edges;
    cin >> vertices;
    cin >> edges;

    vector<vector<int>> graph(vertices + 1);
    vector<int> res(vertices + 1, 0);

    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    topologicalSort(graph, res);

    cout << "Thu tu Topo: ";
    for (int i = 1; i <= vertices; i++) {
        cout << res[i] << " ";
    }

    return 0;
}