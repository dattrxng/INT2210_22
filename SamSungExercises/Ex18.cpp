#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Subset {
    int parent, rank;
};

class Graph {
private:
    int V, E;
    vector<Edge> edges;

public:
    Graph(int vertices, int edges);
    void addEdge(int src, int dest, int weight);
    int find(Subset subsets[], int i);
    void Union(Subset subsets[], int x, int y);
    void boruvkaMST();
};

Graph::Graph(int vertices, int edges) {
    V = vertices;
    E = edges;
}

void Graph::addEdge(int src, int dest, int weight) {
    Edge edge = {src, dest, weight};
    edges.push_back(edge);
}

int Graph::find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void Graph::Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

void Graph::boruvkaMST() {
    Subset* subsets = new Subset[V];
    vector<Edge> result;

    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int numTrees = V;

    while (numTrees > 1) {
        vector<int> cheapest(V, -1);

        for (int i = 0; i < E; i++) {
            int set1 = find(subsets, edges[i].src);
            int set2 = find(subsets, edges[i].dest);

            if (set1 != set2) {
                if (cheapest[set1] == -1 || edges[cheapest[set1]].weight > edges[i].weight)
                    cheapest[set1] = i;

                if (cheapest[set2] == -1 || edges[cheapest[set2]].weight > edges[i].weight)
                    cheapest[set2] = i;
            }
        }

        for (int i = 0; i < V; i++) {
            if (cheapest[i] != -1) {
                int set1 = find(subsets, edges[cheapest[i]].src);
                int set2 = find(subsets, edges[cheapest[i]].dest);

                if (set1 != set2) {
                    result.push_back(edges[cheapest[i]]);
                    Union(subsets, set1, set2);
                    numTrees--;
                }
            }
        }
    }

    for (Edge edge : result) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
    }

    delete[] subsets;
}

int main() {
    int numVertices, numEdge;
    cin >> numVertices >> numEdge;

    Graph graph(numVertices, numEdge);

    for (int i = 0; i < numEdge; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }

    graph.boruvkaMST();

    return 0;
}

