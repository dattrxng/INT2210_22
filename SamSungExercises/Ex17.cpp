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

void vyssotskyMST(vector<Edge> &edges, int numVertices) {
    vector<int> parent(numVertices, -1);
    vector<Edge> minimumSpanningTree;

    sort(edges.begin(), edges.end());

    int addedEdges = 0;
    for (const Edge &edge : edges) {
        minimumSpanningTree.push_back(edge);
        addedEdges++;

        vector<int> componentParent(numVertices, -1);
        bool cycle = false;
        for (const Edge &treeEdge : minimumSpanningTree) {
            int rootU = findSet(componentParent, treeEdge.u);
            int rootV = findSet(componentParent, treeEdge.v);

            if (rootU == rootV) {
                cycle = true;
                break;
            }

            unionSets(componentParent, rootU, rootV);
        }

        if (cycle) {
            int maxWeight = 0;
            int maxWeightIndex = -1;

            for (int i = 0; i < addedEdges; i++) {
                if (minimumSpanningTree[i].weight > maxWeight) {
                    maxWeight = minimumSpanningTree[i].weight;
                    maxWeightIndex = i;
                }
            }

            minimumSpanningTree.erase(minimumSpanningTree.begin() + maxWeightIndex);
        }

        if (addedEdges == numVertices - 1) {
            break;
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

    vyssotskyMST(edges, numVertices);

    return 0;
}
