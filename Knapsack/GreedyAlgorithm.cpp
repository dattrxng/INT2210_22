#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int weight;
    int value;
};

bool compareRatio(const Item &a, const Item &b) {
    return (double)a.value / a.weight > (double)b.value / b.weight;
}

pair<vector<int>, int> knapsackGreedy(vector<Item> items, int capacity) {
    sort(items.begin(), items.end(), compareRatio);

    int n = items.size();
    vector<int> knapsack(n, 0);
    int totalValue = 0;

    for (int i = 0; i < n; ++i) {
        if (items[i].weight <= capacity) {
            knapsack[i] = 1;
            totalValue += items[i].value;
            capacity -= items[i].weight;
        }
    }

    return make_pair(knapsack, totalValue);
}

int main() {
    int numItems, capacity;
    cin >> numItems;

    cin >> capacity;

    vector<Item> items(numItems);
    for (int i = 0; i < numItems; ++i) {
        cin >> items[i].weight >> items[i].value;
    }

    auto result = knapsackGreedy(items, capacity);

    for (int i = 0; i < result.first.size(); ++i) {
        if (result.first[i] == 1) {
            cout << i + 1 << " ";
        }
    }

    cout <<  result.second << endl;

    return 0;
}
