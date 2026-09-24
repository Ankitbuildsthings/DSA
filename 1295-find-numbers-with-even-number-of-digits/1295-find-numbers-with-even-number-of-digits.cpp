class Solution {
public:

    bool numberHasEvenDigits(int num) {
        int digits = 0;

        while (num != 0) {
            num = num / 10;
            digits++;
        }

        return digits % 2 == 0;
    }

    int findNumbers(vector<int>& nums) {
        int evencount = 0;

        for (int i = 0; i < nums.size(); i++) {
            if (numberHasEvenDigits(nums[i])) {
                evencount++;
            }
        }

        return evencount;
    }
};