
class Solution {
    using ull = unsigned long long;

    ull splitmix64(ull x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }

public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> sortedNums = nums;
        sort(sortedNums.begin(), sortedNums.end());

        // Random-looking hash for each possible value
        vector<ull> h(100001);
        for (int x = 1; x <= 100000; x++)
            h[x] = splitmix64(x);

        // Prefix sums of multiset hashes
        vector<ull> prefA(n + 1, 0), prefB(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefA[i + 1] = prefA[i] + h[nums[i]];
            prefB[i + 1] = prefB[i] + h[sortedNums[i]];
        }

        // prefDesc[t] counts descents on edges j -> j+1,
        // where j < t.
        vector<int> prefDesc(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefDesc[i + 1] = prefDesc[i];
            if (i + 1 < n && nums[i] > nums[i + 1])
                prefDesc[i + 1]++;
        }

        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0)
                continue;

            bool ok = true;

            for (int start = 0; start < n; start += k) {
                int end = start + k;

                // Check whether the block has the correct multiset
                ull hashA = prefA[end] - prefA[start];
                ull hashB = prefB[end] - prefB[start];

                if (hashA != hashB) {
                    ok = false;
                    break;
                }

                // Count descents inside the block
                int descents =
                    prefDesc[end - 1] - prefDesc[start];

                // Include the circular edge: last -> first
                if (nums[end - 1] > nums[start])
                    descents++;

                if (descents > 1) {
                    ok = false;
                    break;
                }
            }

            if (ok)
                ans += k;
        }

        return ans;
    }
};
