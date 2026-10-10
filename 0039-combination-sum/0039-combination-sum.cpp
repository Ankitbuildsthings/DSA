
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> path;

    void solve(vector<int>& candidates, int target, int index) {
        if (target == 0) {
            ans.push_back(path);
            return;
        }

        for (int i = index; i < candidates.size(); i++) {
            if (candidates[i] > target)
                continue;

            path.push_back(candidates[i]);

            // Same number can be reused
            solve(candidates, target - candidates[i], i);

            path.pop_back(); // Backtrack
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates,
                                       int target) {
        ans.clear();
        path.clear();

        solve(candidates, target, 0);
        return ans;
    }
};
