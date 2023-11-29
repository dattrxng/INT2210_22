#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;

class Graph {
private:
	vector<vector<pair<int,int>>> adj;
	int V;
public:
	Graph() {}
	Graph(int n) {
		V = n;
		while (n--) {
			vector<pair<int,int>> tmp;
			adj.push_back(tmp);
		}
 	}

 	void addEdge(int u, int v, int w) {
 		adj[u].push_back({v,w});
 		adj[v].push_back({u,w});
 	}

 	void dijkstra(int start) {
 		vector<int> dist(V, INT_MAX);
 		vector<int> parent(V, INT_MIN);
 		dist[start] = 0;
 		priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

 		pq.push({0, start});
 		while (!pq.empty()) {
 			pair<int, int> cur = pq.top();
 			pq.pop();
 			int u = cur.second;
 			for (auto next : adj[u]) {
 				int v = next.first;
 				int uv = next.second;
 				if (dist[v] > (dist[u]+uv)) {
 					dist[v] = dist[u] + uv;
 					parent[v] = u;
 					pq.push({dist[v], v});
 				} 
 			}
 		}

 		for (int i = 0; i < V; i++) {
            cout << "Distance from " << start << " to " << i << " is " << dist[i] << " : ";
            stack<int> s;
            int j = i;
            while (j != start) {
            	s.push(j);
            	j = parent[j];
            }
            s.push(j);
            while (!s.empty()) {
            	cout << s.top() << " ";
            	s.pop();
            }
            cout << endl;
        }
 	}
};

int main() {
    int V = 9;
    Graph g(V);
 
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    int start = 0;

    cout << "Dijkstra:" << endl;
    g.dijkstra(start);

}