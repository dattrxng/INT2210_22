#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void printPath(vector<int> &parent, int v) {
    if (parent[v] == -1) {
        cout << v;
        return;
    }
    printPath(parent, parent[v]);
    cout << " " << v;
}

void shortestPath(vector<vector<pair<int, int>>> &graph, int source, int C) {
    vector<int> distance(graph.size(), INT_MAX);
    vector<int> parent(graph.size(), -1);
    vector<vector<int>> bucket(C + 1);
    distance[source] = 0;
    bucket[0].push_back(source);
    int index = 0;
    while (true) {
        while (index <= C && bucket[index].empty()) {
            index++;
        }
        if (index > C) {
            break;
        }
        int u = bucket[index].back();
        bucket[index].pop_back();
        for (auto &edge: graph[u]) {
            int v = edge.first;
            int w = edge.second;
            if (distance[v] > distance[u] + w) {
                distance[v] = distance[u] + w;
                parent[v] = u;
                bucket[distance[v]].push_back(v);
            }
        }
    }
    for (int i = 0; i < graph.size(); i++) {
        if (i != source) {
            printPath(parent, i);
            cout << "\n";
        }
    }
}

int main() {
    int V, E, C;
    cin >> V;
    cin >> E;

    vector<vector<pair<int, int>>> graph(V);

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    int source;
    cin >> source;

    cin >> C;

    shortestPath(graph, source, C);

    return 0;
}
