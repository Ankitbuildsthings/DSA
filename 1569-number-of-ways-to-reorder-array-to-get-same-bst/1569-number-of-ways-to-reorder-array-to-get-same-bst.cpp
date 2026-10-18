class Solution {
public:
    const long long MOD = 1000000007;
    vector<vector<long long>> comb;

    int ways(vector<int>& nums) {
        int n = nums.size();

        if (n <= 2)
            return 1;

        vector<int> left, right;
        int root = nums[0];

        for (int i = 1; i < n; i++) {
            if (nums[i] < root)
                left.push_back(nums[i]);
            else
                right.push_back(nums[i]);
        }

        long long leftWays = ways(left);
        long long rightWays = ways(right);

        long long interleavings =
            comb[left.size() + right.size()][left.size()];

        long long ans = interleavings * leftWays % MOD;
        ans = ans * rightWays % MOD;

        return ans;
    }

    int numOfWays(vector<int>& nums) {
        int n = nums.size();

        comb.assign(n + 1, vector<long long>(n + 1, 0));

        for (int i = 0; i <= n; i++)
            comb[i][0] = comb[i][i] = 1;

        for (int i = 2; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                comb[i][j] =
                    (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
            }
        }

        return (ways(nums) - 1 + MOD) % MOD;
    }
};