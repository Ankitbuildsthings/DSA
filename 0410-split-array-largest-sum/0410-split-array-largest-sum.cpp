class Solution {
public:
    int splitArray(vector<int>& nums, int k) {

        int start = 0, end = 0, mid, ans;

        for (int i = 0; i < nums.size(); i++) {
            start = max(start, nums[i]);
            end += nums[i];
        }

        while (start <= end) {

            mid = start + (end - start) / 2;

            int page = 0;
            int count = 1;

            for (int i = 0; i < nums.size(); i++) {

                page += nums[i];

                if (page > mid) {
                    count++;
                    page = nums[i];
                }
            }

            if (count <= k) {
                ans = mid;
                end = mid - 1;
            }
            else {
                start = mid + 1;
            }
        }

        return ans;
    }
};