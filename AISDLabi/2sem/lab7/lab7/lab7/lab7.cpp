#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void findLongestIncreasingSubsequence(const vector<int>& sequence) {
    int n = sequence.size();
    vector<int> dp(n, 1);
    vector<int> previous(n, -1);

    int maxLength = 1, lastIndex = 0;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (sequence[i] > sequence[j] &&
                (dp[i] < dp[j] + 1 || (dp[i] == dp[j] + 1 && sequence[i] < sequence[lastIndex]))) {
                dp[i] = dp[j] + 1;
                previous[i] = j;
            }
        }
        if (dp[i] > maxLength || (dp[i] == maxLength && sequence[i] < sequence[lastIndex])) {
            maxLength = dp[i];
            lastIndex = i;
        }
    }

    vector<int> longestSubsequence;
    for (int i = lastIndex; i != -1; i = previous[i]) {
        longestSubsequence.push_back(sequence[i]);
    }
    reverse(longestSubsequence.begin(), longestSubsequence.end());

    cout << maxLength << endl;
    for (size_t i = 0; i < longestSubsequence.size(); ++i) {
        cout << longestSubsequence[i];
        if (i < longestSubsequence.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Rus");
    int N;
    cout << "Введите количество элементов: ";
    cin >> N;

    vector<int> sequence(N);
    cout << "Введите последовательность: ";
    for (int i = 0; i < N; ++i) {
        cin >> sequence[i];
    }

    findLongestIncreasingSubsequence(sequence);
    return 0;
}
