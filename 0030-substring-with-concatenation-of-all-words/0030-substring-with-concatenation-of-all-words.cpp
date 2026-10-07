class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ans;

        int wordLen = words[0].size();
        int wordCount = words.size();
        int totalLen = wordLen * wordCount;

        if (totalLen > s.size())
            return ans;

        unordered_map<string, int> need;

        for (string word : words)
            need[word]++;

        for (int start = 0; start < wordLen; start++) {
            int left = start;
            int count = 0;
            unordered_map<string, int> have;

            for (int right = start; right + wordLen <= s.size(); right += wordLen) {
                string word = s.substr(right, wordLen);

                if (need.find(word) == need.end()) {
                    have.clear();
                    count = 0;
                    left = right + wordLen;
                    continue;
                }

                have[word]++;
                count++;

                while (have[word] > need[word]) {
                    string removeWord = s.substr(left, wordLen);
                    have[removeWord]--;
                    left += wordLen;
                    count--;
                }

                if (count == wordCount) {
                    ans.push_back(left);

                    string removeWord = s.substr(left, wordLen);
                    have[removeWord]--;
                    left += wordLen;
                    count--;
                }
            }
        }

        return ans;
    }
};