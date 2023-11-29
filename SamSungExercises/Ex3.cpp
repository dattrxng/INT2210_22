#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <functional>

using namespace std;

void addEdge(vector<vector<int>> &adjList, int u, int v) {
    adjList[u].push_back(v);
}

int countParallelEdges(vector<vector<int>> &adjList) {
    int parallelEdges = 0;

    for (int u = 0; u < adjList.size(); ++u) {
        vector<int> lowLink(adjList.size(), -1);
        vector<bool> inStack(adjList.size(), false);
        stack<int> stk;
        vector<int> stackMembers;
        int index = 0;

        function<void(int)> tarjan = [&](int v) {
            lowLink[v] = index;
            ++index;
            stk.push(v);
            inStack[v] = true;

            for (int neighbor : adjList[v]) {
                if (lowLink[neighbor] == -1) {
                    tarjan(neighbor);
                    lowLink[v] = min(lowLink[v], lowLink[neighbor]);
                } else if (inStack[neighbor]) {
                    lowLink[v] = min(lowLink[v], lowLink[neighbor]);
                }
            }

            if (lowLink[v] == v) {
                while (!stk.empty()) {
                    int member = stk.top();
                    stk.pop();
                    inStack[member] = false;
                    stackMembers.push_back(member);
                    if (member == v) {
                        break;
                    }
                }

                int componentSize = stackMembers.size();
                if (componentSize > 1) {
                    parallelEdges += (componentSize * (componentSize - 1)) / 2;
                }

                stackMembers.clear();
            }
        };

        tarjan(u);
    }

    return parallelEdges;
}

int main() {
    int numVertices, numEdges;
    cin >> numVertices;

    vector<vector<int>> graph(numVertices);

    cin >> numEdges;

    for (int i = 0; i < numEdges; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(graph, u, v);
    }

    int parallelEdges = countParallelEdges(graph);

    cout <<  parallelEdges << endl;

    return 0;
}
