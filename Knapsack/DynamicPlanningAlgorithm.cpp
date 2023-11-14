#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int weight;
    int value;
};

int knapsackDynamic(vector<Item> items, int capacity) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w], items[i - 1].value + dp[i - 1][w - items[i - 1].weight]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

int main() {
    int numItems, capacity;
    cin >> numItems;

    cin >> capacity;

    vector<Item> items(numItems);
    for (int i = 0; i < numItems; ++i) {
        cin >> items[i].weight >> items[i].value;
    }

    int result = knapsackDynamic(items, capacity);

    cout <<  result << endl;

    return 0;
}
