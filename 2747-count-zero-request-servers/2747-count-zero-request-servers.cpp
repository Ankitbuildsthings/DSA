
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        sort(logs.begin(), logs.end(), [](auto &a, auto &b) {
            return a[1] < b[1];
        });

        vector<pair<int,int>> q;

        for(int i = 0; i < queries.size(); i++) {
            q.push_back({queries[i], i});
        }

        sort(q.begin(), q.end());

        vector<int> ans(queries.size());
        unordered_map<int,int> mp;

        int l = 0, r = 0;
        int m = logs.size();

        for(auto [time, idx] : q) {

            while(r < m && logs[r][1] <= time) {
                mp[logs[r][0]]++;
                r++;
            }

            while(l < r && logs[l][1] < time - x) {
                mp[logs[l][0]]--;

                if(mp[logs[l][0]] == 0) {
                    mp.erase(logs[l][0]);
                }

                l++;
            }

            ans[idx] = n - mp.size();
        }

        return ans;
    }
};
