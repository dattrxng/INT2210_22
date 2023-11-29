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

int findSet(vector<int> &parent, int i) {
    if (parent[i] == -1) {
        return i;
    }
    return findSet(parent, parent[i]);
}

void unionSets(vector<int> &parent, int x, int y) {
    int rootX = findSet(parent, x);
    int rootY = findSet(parent, y);
    parent[rootX] = rootY;
}

void boruvkaMST(vector<Edge> &edges, int numVertices) {
    vector<int> parent(numVertices, -1);
    vector<Edge> minimumSpanningTree;
    int numTrees = numVertices;

    while (numTrees > 1) {
        vector<int> cheapest(numVertices, -1);

        for (const Edge &edge : edges) {
            int rootU = findSet(parent, edge.u);
            int rootV = findSet(parent, edge.v);

            if (rootU != rootV) {
                if (cheapest[rootU] == -1 || edges[cheapest[rootU]].weight > edge.weight) {
                    cheapest[rootU] = edge.u;
                }

                if (cheapest[rootV] == -1 || edges[cheapest[rootV]].weight > edge.weight) {
                    cheapest[rootV] = edge.v;
                }
            }
        }

        for (int i = 0; i < numVertices; ++i) {
            if (cheapest[i] != -1) {
                int rootU = findSet(parent, edges[cheapest[i]].u);
                int rootV = findSet(parent, edges[cheapest[i]].v);

                if (rootU != rootV) {
                    minimumSpanningTree.push_back(edges[cheapest[i]]);
                    unionSets(parent, rootU, rootV);
                    --numTrees;
                }
            }
        }
    }

    for (const Edge &edge : minimumSpanningTree) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }
}

int main() {
    int numVertices, numEdges;
    cin >> numVertices;

    vector<Edge> edges;

    cin >> numEdges;

    for (int i = 0; i < numEdges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        edges.emplace_back(u, v, weight);
    }

    boruvkaMST(edges, numVertices);

    return 0;
}
