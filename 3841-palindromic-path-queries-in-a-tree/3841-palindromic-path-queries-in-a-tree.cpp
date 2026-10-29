class Solution {
    int n, timer, LOG;
    vector<vector<int>> adj, up;
    vector<int> tin, tout, bit, fenwick;

    void add(int i, int val) {
        for (; i <= n; i += i & -i)
            fenwick[i] ^= val;
    }

    int get(int i) {
        int ans = 0;
        for (; i > 0; i -= i & -i)
            ans ^= fenwick[i];
        return ans;
    }

    void dfs(int u, int p) {
        tin[u] = ++timer;
        up[u][0] = p;

        for (int j = 1; j < LOG; j++)
            up[u][j] = up[up[u][j - 1]][j - 1];

        for (int v : adj[u]) {
            if (v == p) continue;
            dfs(v, u);
        }

        tout[u] = timer;
    }

    bool isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    int lca(int u, int v) {
        if (isAncestor(u, v)) return u;
        if (isAncestor(v, u)) return v;

        for (int j = LOG - 1; j >= 0; j--) {
            if (!isAncestor(up[u][j], v))
                u = up[u][j];
        }

        return up[u][0];
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        this->n = n;
        timer = 0;

        adj.assign(n, {});
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        up.assign(n, vector<int>(LOG));
        tin.assign(n, 0);
        tout.assign(n, 0);
        bit.resize(n);
        fenwick.assign(n + 2, 0);

        for (int i = 0; i < n; i++)
            bit[i] = 1 << (s[i] - 'a');

        dfs(0, 0);

        for (int u = 0; u < n; u++) {
            add(tin[u], bit[u]);
            add(tout[u] + 1, bit[u]);
        }

        vector<bool> ans;

        for (string &q : queries) {
            string type;
            int u;
            stringstream ss(q);
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int newBit = 1 << (c - 'a');
                int change = bit[u] ^ newBit;

                add(tin[u], change);
                add(tout[u] + 1, change);

                bit[u] = newBit;
            } else {
                int v;
                ss >> v;

                int w = lca(u, v);
                int mask = get(tin[u]) ^ get(tin[v]) ^ bit[w];

                ans.push_back(mask == 0 || (mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};