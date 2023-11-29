#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

class Graph {
private:
    int V;
    vector<vector<int>> distance;

public:
    Graph(int vertices) : V(vertices) {
        distance.resize(V, vector<int>(V, INF));
    }

    void addEdge(int u, int v, int w) {
        distance[u][v] = distance[v][u] = w;
    }

    void preprocessGraph() {
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (distance[i][k] != INF && distance[k][j] != INF &&
                        distance[i][k] + distance[k][j] < distance[i][j]) {
                        distance[i][j] = distance[i][k] + distance[k][j];
                    }
                }
            }
        }
    }

    int getShortestDistance(int u, int v) {
        return distance[u][v];
    }
};

int main() {
    int vertices = 4;
    Graph graph(vertices);

    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 3);
    graph.addEdge(3, 0, 4);

    graph.preprocessGraph();

    int u = 0, v = 2;
    int shortestDistance = graph.getShortestDistance(u, v);

    if (shortestDistance != INF) {
        cout << "Khoang cach ngan nhat giua dinh " << u << " va dinh " << v << " la: " << shortestDistance << endl;
    } else {
        cout << "Khong co duong di giua " << u << " va " << v << endl;
    }

    return 0;
}
