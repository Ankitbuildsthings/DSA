class Solution {
public:
    string count_sort(string s)
{
    vector<int> t(26,0);
    for (auto& c:s){
        t[c - 'a']++;
    }
    string res;
    for(int i=0; i<26; i++){
        res += string(t[i],char(i+'a'));
    }
    return res;
}  
  bool checkInclusion(string s1, string s2) {
    s1 = count_sort (s1);
    int i = s1.size ();
    for(int i = 0; i + s1.size() <= s2.size(); ++i) {
    string t = count_sort(s2.substr(i, s1.size()));
    if(t == s1)
        return true;
}

return false;
        
    }
};