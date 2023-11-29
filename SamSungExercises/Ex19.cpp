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
    Subset* subsets;

public:
    Graph(int vertices, int edges);
    void addEdge(int src, int dest, int weight);
    int find(int i);
    void Union(int x, int y);
    void kruskalMST();
    void dfs(int u, vector<bool>& visited, vector<vector<int>>& adjList);
    void findCriticalEdges();
};

Graph::Graph(int vertices, int edges) {
    V = vertices;
    E = edges;
    subsets = new Subset[V];
}

void Graph::addEdge(int src, int dest, int weight) {
    Edge edge = {src, dest, weight};
    edges.push_back(edge);
}

int Graph::find(int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets[i].parent);

    return subsets[i].parent;
}

void Graph::Union(int x, int y) {
    int xroot = find(x);
    int yroot = find(y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

void Graph::kruskalMST() {
    vector<Edge> result;

    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    int i = 0, e = 0;

    while (e < V - 1 && i < E) {
        Edge next_edge = edges[i++];
        int x = find(next_edge.src);
        int y = find(next_edge.dest);

        if (x != y) {
            result.push_back(next_edge);
            Union(x, y);
            e++;
        }
    }

    for (Edge edge : result) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
    }
}

void Graph::dfs(int u, vector<bool>& visited, vector<vector<int>>& adjList) {
    visited[u] = true;

    for (int v : adjList[u]) {
        if (!visited[v]) {
            dfs(v, visited, adjList);
        }
    }
}

void Graph::findCriticalEdges() {
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    // Tạo cây bao trùm và lưu lại cạnh có cùng trọng số
    vector<int> lastEdgeIndex(V, -1);
    for (int i = 0; i < E; i++) {
        int set1 = find(edges[i].src);
        int set2 = find(edges[i].dest);

        if (set1 != set2) {
            lastEdgeIndex[set1] = i;
            lastEdgeIndex[set2] = i;
            Union(set1, set2);
        }
    }

    vector<vector<int>> adjList(V);
    for (Edge edge : edges) {
        adjList[edge.src].push_back(edge.dest);
        adjList[edge.dest].push_back(edge.src);
    }

    for (int i = 0; i < E; i++) {
        if (i == lastEdgeIndex[i]) {
            vector<bool> visited(V, false);
            dfs(edges[i].src, visited, adjList);

            if (!visited[edges[i].dest]) {
                cout << edges[i].src << " - " << edges[i].dest << " : " << edges[i].weight << endl;
            }
        }
    }
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

    graph.kruskalMST();
    graph.findCriticalEdges();

    return 0;
}
