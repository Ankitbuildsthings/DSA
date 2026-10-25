
class Solution {
public:
    string simplifyPath(string path) {
        stack<string> st;
        string s;
        stringstream ss(path);

        while (getline(ss, s, '/')) {
            if (s == "" || s == ".") {
                continue;
            }
            else if (s == "..") {
                if (!st.empty()) {
                    st.pop();
                }
            }
            else {
                st.push(s);
            }
        }

        string ans = "";

        while (!st.empty()) {
            ans = "/" + st.top() + ans;
            st.pop();
        }

        return ans.empty() ? "/" : ans;
    }
};
