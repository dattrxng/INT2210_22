#include <iostream>

using namespace std;

int* longestIncreasingSubsequence(int nums1[], int m, int nums2[], int n, int& len) {
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (nums1[i - 1] == nums2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    len = dp[m][n];
    int* result = new int[len];
    int i = m, j = n, index = len - 1;

    while (i > 0 && j > 0) {
        if (nums1[i - 1] == nums2[j - 1]) {
            result[index] = nums1[i - 1];
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return result;
}

int main() {
    int m, n;
    cin >> m;
    int nums1[m];

    for (int i = 0; i < m; i++) {
        cin >> nums1[i];
    }

    cin >> n;
    int nums2[n];

    for (int i = 0; i < n; i++) {
        cin >> nums2[i];
    }

    int len;
    int* result = longestIncreasingSubsequence(nums1, m, nums2, n, len);

    for (int i = 0; i < len; i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    delete[] result;

    return 0;
}
