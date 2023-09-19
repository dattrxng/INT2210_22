#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    list<int> linkedList;

    for (int i = 0; i < n; i++) {
        string operation;
        cin >> operation;

        if (operation == "insert") {
            int p, x;
            cin >> p >> x;

            list<int>::iterator it = linkedList.begin();
            advance(it, p);

            linkedList.insert(it, x);
        } else if (operation == "delete") {
            int p;
            cin >> p;

            list<int>::iterator it = linkedList.begin();
            advance(it, p);

            linkedList.erase(it);
        }
    }

    for (const int& num : linkedList) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
