//
// Created by 22411 on 2025/10/31.
//
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s)
    {
        int length = 0;
        int i, j = 0;
        for (i=0; i<s.length(); i++)  // start of substring
        {
            short characters[128] = {0};
            for (j=i; j<s.length(); j++)  // end of substring
            {
                char c = s[j];
                if (characters[c]) break;
                else characters[c] = 1;
            }
            if (j - i > length) length = j - i;
        }
        return length;
    }
};

int main()
{
    Solution s;
    string str = "pwwkew";
    cout<<s.lengthOfLongestSubstring(str)<<endl;
}