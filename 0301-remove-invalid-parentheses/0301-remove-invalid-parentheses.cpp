class Solution {
public:
    vector<string> ans;
    unordered_set<string> st;

    void solve(string &s, int index, int left, int right, int balance, string curr) {
        if (index == s.size()) {
            if (left == 0 && right == 0 && balance == 0)
                st.insert(curr);
            return;
        }

        char ch = s[index];

        if (ch == '(') {
            if (left > 0)
                solve(s, index + 1, left - 1, right, balance, curr);

            solve(s, index + 1, left, right, balance + 1, curr + ch);
        }
        else if (ch == ')') {
            if (right > 0)
                solve(s, index + 1, left, right - 1, balance, curr);

            if (balance > 0)
                solve(s, index + 1, left, right, balance - 1, curr + ch);
        }
        else {
            solve(s, index + 1, left, right, balance, curr + ch);
        }
    }

    vector<string> removeInvalidParentheses(string s) {
        int left = 0, right = 0;

        for (char ch : s) {
            if (ch == '(')
                left++;
            else if (ch == ')') {
                if (left > 0)
                    left--;
                else
                    right++;
            }
        }

        solve(s, 0, left, right, 0, "");

        for (auto x : st)
            ans.push_back(x);

        return ans;
    }
};