
class Solution {
public:
    int totalNQueens(int n) {
        int fullMask = (1 << n) - 1;
        return solve(fullMask, 0, 0, 0);
    }

    int solve(int fullMask, int cols, int diag1, int diag2) {
        if (cols == fullMask)
            return 1;

        int count = 0;
        int available = fullMask & ~(cols | diag1 | diag2);

        while (available) {
            int bit = available & -available;
            available -= bit;

            count += solve(
                fullMask,
                cols | bit,
                ((diag1 | bit) << 1) & fullMask,
                (diag2 | bit) >> 1
            );
        }

        return count;
    }
};
