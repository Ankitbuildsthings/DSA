
class Solution {
public:
    vector<int> answer;
    vector<int> last;
    vector<vector<int>> adj;

    void dfs1(int node, vector<int>& parent, string& s) {
        int c = s[node] - 'a';

        int old = last[c];
        if (old != -1) {
            answer[node] = old;
        } else {
            answer[node] = parent[node];
        }

        last[c] = node;

        for (int child : adj[node]) {
            dfs1(child, parent, s);
        }

        last[c] = old;
    }

    int dfs2(int node, vector<vector<int>>& tree) {
        int size = 1;

        for (int child : tree[node]) {
            size += dfs2(child, tree);
        }

        answer[node] = size;
        return size;
    }

    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        answer.resize(n);
        last.assign(26, -1);

        adj.resize(n);

        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        dfs1(0, parent, s);

        vector<vector<int>> tree(n);

        for (int i = 1; i < n; i++) {
            tree[answer[i]].push_back(i);
        }

        dfs2(0, tree);

        return answer;
    }
};
