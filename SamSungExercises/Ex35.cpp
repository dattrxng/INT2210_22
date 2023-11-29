#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Vertex {
    int id, weight;
    Vertex(int _id, int _weight) : id(_id), weight(_weight) {}
};

struct Edge {
    int to, weight;
    Edge(int _to, int _weight) : to(_to), weight(_weight) {}
};

struct Compare {
    bool operator()(const Vertex& v1, const Vertex& v2) {
        return v1.weight > v2.weight;
    }
};

vector<int> dijkstra(const vector<vector<Edge>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INF);
    priority_queue<Vertex, vector<Vertex>, Compare> pq;

    dist[start] = 0;
    pq.push(Vertex(start, 0));

    while (!pq.empty()) {
        Vertex current = pq.top();
        pq.pop();

        for (const Edge& e : graph[current.id]) {
            if (dist[e.to] > dist[current.id] + e.weight) {
                dist[e.to] = dist[current.id] + e.weight;
                pq.push(Vertex(e.to, dist[e.to]));
            }
        }
    }

    return dist;
}

vector<int> bitonicShortestPath(const vector<vector<Edge>>& graph, int start) {
    int n = graph.size();
    vector<int> increasingDist = dijkstra(graph, start);

    vector<int> bitonicDist(n, INF);

    for (int i = 0; i < n; ++i) {
        if (increasingDist[i] != INF) {
            vector<vector<Edge>> reversedGraph(n);
            for (int u = 0; u < n; ++u) {
                for (const Edge& e : graph[u]) {
                    reversedGraph[e.to].emplace_back(u, e.weight);
                }
            }

            vector<int> decreasingDist = dijkstra(reversedGraph, i);

            for (int j = 0; j < n; ++j) {
                if (decreasingDist[j] != INF) {
                    bitonicDist[j] = min(bitonicDist[j], increasingDist[i] + decreasingDist[j]);
                }
            }
        }
    }

    return bitonicDist;
}

int main() {
    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<Edge>> graph(n);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
    }

    vector<int> result = bitonicShortestPath(graph, s);

    // In ra kết quả
    for (int i = 0; i < n; ++i) {
        if (result[i] == INF) {
            cout << "Khong co duong di tu " << s << " den " << i << endl;
        } else {
            cout << "Duong di ngan nhat bitonic tu " << s << " den " << i << " la: " << result[i] << endl;
        }
    }

    return 0;
}
