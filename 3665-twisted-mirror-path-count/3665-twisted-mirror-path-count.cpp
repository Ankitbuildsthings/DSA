class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        vector<vector<array<int, 2>>> memo(
            m, vector<array<int, 2>>(n, {-2, -2})
        );

        function<int(int, int, int)> solve =
        [&](int i, int j, int dir) -> int {

            if (i >= m || j >= n)
                return -1;

            if (grid[i][j] == 0)
                return i * n + j;

            if (memo[i][j][dir] != -2)
                return memo[i][j][dir];

            int ans;

            if (dir == 0)
                ans = solve(i + 1, j, 1);
            else
                ans = solve(i, j + 1, 0);

            return memo[i][j][dir] = ans;
        };

        vector<vector<long long>> dp(
            m, vector<long long>(n, 0)
        );

        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (dp[i][j] == 0 || grid[i][j] == 1)
                    continue;

                int right = solve(i, j + 1, 0);

                if (right != -1) {
                    int x = right / n;
                    int y = right % n;

                    dp[x][y] = (dp[x][y] + dp[i][j]) % MOD;
                }

                int down = solve(i + 1, j, 1);

                if (down != -1) {
                    int x = down / n;
                    int y = down % n;

                    dp[x][y] = (dp[x][y] + dp[i][j]) % MOD;
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};