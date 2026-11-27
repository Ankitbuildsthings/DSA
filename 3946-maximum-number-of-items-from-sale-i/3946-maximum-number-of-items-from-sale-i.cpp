class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        vector<int> freq(1501, 0);

        for (auto &it : items) {
            freq[it[0]]++;
        }

        vector<int> cnt(1501, 0);

        for (int f = 1; f <= 1500; f++) {
            for (int j = f; j <= 1500; j += f) {
                cnt[f] += freq[j];
            }
        }

        vector<vector<int>> groups(1501);

        for (auto &it : items) {
            groups[it[1]].push_back(cnt[it[0]]);
        }

        const int NEG = -1000000000;

        vector<int> dpPrev(budget + 1, NEG);
        dpPrev[0] = 0;

        int ans = 0;

        for (int m = 1500; m >= 1; m--) {
            if (groups[m].empty()) continue;

            vector<int> dpCur(budget + 1, NEG);

            for (int value : groups[m]) {
                for (int c = budget; c >= m; c--) {

                    if (dpCur[c - m] != NEG) {
                        dpCur[c] = max(
                            dpCur[c],
                            dpCur[c - m] + value
                        );
                    }

                    if (dpPrev[c - m] != NEG) {
                        dpCur[c] = max(
                            dpCur[c],
                            dpPrev[c - m] + value
                        );
                    }
                }
            }

            for (int c = 0; c <= budget; c++) {
                if (dpCur[c] == NEG) continue;

                ans = max(
                    ans,
                    dpCur[c] + (budget - c) / m
                );

                dpPrev[c] = max(dpPrev[c], dpCur[c]);
            }
        }

        return ans;
    }
};