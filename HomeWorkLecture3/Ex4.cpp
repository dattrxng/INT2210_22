#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;

    queue<int> q;

    for (int i = 0; i < n; i++) {
        string operation;
        cin >> operation;

        if (operation == "enqueue") {
            int x;
            cin >> x;

            q.push(x);
        } else if (operation == "dequeue") {
            if (!q.empty()) {
                q.pop();
            }
        }
    }

    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    return 0;
}
