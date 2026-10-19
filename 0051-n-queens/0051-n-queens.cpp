class Solution {
public:
    vector<vector<string>> ans;

    void solve(int row, int n, vector<string>& board) {
        if (row == n) {
            ans.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++) {
            bool safe = true;

            for (int i = 0; i < row; i++) {
                if (board[i][col] == 'Q') {
                    safe = false;
                    break;
                }

                if (abs(row - i) == abs(col - (int)board[i].find('Q'))) {
                    safe = false;
                    break;
                }
            }

            if (safe) {
                board[row][col] = 'Q';
                solve(row + 1, n, board);
                board[row][col] = '.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        ans.clear();
        vector<string> board(n, string(n, '.'));
        solve(0, n, board);
        return ans;
    }
};