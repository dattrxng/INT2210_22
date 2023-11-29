#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge {
public:
    int u, v, weight;

    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}

    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
};

class Node {
public:
    int parent;
    int rank;

    Node() {}
};

class BoruvkaGraph {
public:
    int numVertices;
    vector<Node> nodes;
    vector<Edge> edges;

    BoruvkaGraph(int V) : numVertices(V), nodes(V), edges() {
        for (int i = 0; i < V; ++i) {
            nodes[i].parent = i;
            nodes[i].rank = 0;
        }
    }

    void addEdge(int u, int v, int weight) {
        edges.emplace_back(u, v, weight);
    }

    void updateSets(int u, int v) {
        int rootU = findSet(u);
        int rootV = findSet(v);

        if (rootU != rootV) {
            if (nodes[rootU].rank < nodes[rootV].rank) {
                nodes[rootU].parent = rootV;
            } else if (nodes[rootU].rank > nodes[rootV].rank) {
                nodes[rootV].parent = rootU;
            } else {
                nodes[rootU].parent = rootV;
                nodes[rootV].rank++;
            }
        }
    }

    int findSet(int i) {
        if (i != nodes[i].parent) {
            nodes[i].parent = findSet(nodes[i].parent);
        }
        return nodes[i].parent;
    }

    void boruvkaMST() {
        vector<int> cheapest(numVertices, -1);

        while (true) {
            for (int i = 0; i < numVertices; ++i) {
                cheapest[i] = -1;
            }

            for (const Edge &edge : edges) {
                int rootU = findSet(edge.u);
                int rootV = findSet(edge.v);

                if (rootU != rootV) {
                    if (cheapest[rootU] == -1 || edges[cheapest[rootU]].weight > edge.weight) {
                        cheapest[rootU] = edge.u;
                    }

                    if (cheapest[rootV] == -1 || edges[cheapest[rootV]].weight > edge.weight) {
                        cheapest[rootV] = edge.v;
                    }
                }
            }

            bool anyTreeMerged = false;

            for (int i = 0; i < numVertices; ++i) {
                if (cheapest[i] != -1) {
                    int rootU = findSet(edges[cheapest[i]].u);
                    int rootV = findSet(edges[cheapest[i]].v);

                    if (rootU != rootV) {
                        cout << edges[cheapest[i]].u << " - " << edges[cheapest[i]].v << " : "
                             << edges[cheapest[i]].weight << endl;

                        updateSets(edges[cheapest[i]].u, edges[cheapest[i]].v);
                        anyTreeMerged = true;
                    }
                }
            }

            if (!anyTreeMerged) {
                break;
            }
        }
    }
};

int main() {
    int numVertices, numEdges;
    cin >> numVertices;

    BoruvkaGraph graph(numVertices);

    cin >> numEdges;

    for (int i = 0; i < numEdges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph.addEdge(u, v, weight);
    }

    graph.boruvkaMST();

    return 0;
}
