#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    unordered_map<int, int> num_count;
    long long count = 0;

    for (int i = 0; i < n; i++) {

        count += num_count[arr[i]];

        num_count[arr[i]]++;
    }

    cout << count << endl;

    return 0;
}
