class Solution {
public:
    int minMoves(vector<int>& nums) {
        int n = nums.size();

        sort(begin(nums),end(nums));

        int mid = nums[n-1];

        int Moves = 0;
        for(int i = 0;i<n; i++){
            Moves +=  (mid - nums[i]);

        }
        return Moves ;
        
    }
};