#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;

    stack<int> stk;

    for (int i = 0; i < n; i++) {
        string operation;
        cin >> operation;

        if (operation == "push") {
            int x;
            cin >> x;
            stk.push(x);
        } else if (operation == "pop") {
            if (!stk.empty()) {
                stk.pop();
            }
        }
    }

    stack<int> temp;

    while (!stk.empty()) {
        temp.push(stk.top());
        stk.pop();
    }

    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;

    return 0;
}
