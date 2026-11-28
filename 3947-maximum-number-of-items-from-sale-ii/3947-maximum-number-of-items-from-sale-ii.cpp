
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        int minPrice = INT_MAX;
        int maxFactor = 0;

        vector<int> freq(n + 1, 0);

        for (auto& item : items) {
            int factor = item[0];
            int price = item[1];

            freq[factor]++;
            minPrice = min(minPrice, price);
            maxFactor = max(maxFactor, factor);
        }

        for (int i = 1; i <= maxFactor; i++) {
            for (int j = 2 * i; j <= maxFactor; j += i) {
                freq[i] += freq[j];
            }
        }

        vector<pair<int, long long>> deals;

        for (auto& item : items) {
            int factor = item[0];
            int price = item[1];

            long long gain = freq[factor] - 1;

            if (gain > 0 && price <= 2LL * minPrice) {
                deals.push_back({price, gain});
            }
        }

        sort(deals.begin(), deals.end());

        long long ans = 0;
        long long remaining = budget;

        for (auto& deal : deals) {
            long long price = deal.first;
            long long count = deal.second;

            long long buy = min(count, remaining / price);

            ans += 2 * buy;
            remaining -= buy * price;
        }

        ans += remaining / minPrice;

        return (int)ans;
    }
};
