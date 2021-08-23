#include <bits/stdc++.h>
#include <set>
#include<ctype.h>


class Easy_strings_Solution {
public:

    // ex. 1 - Reverse String
    /**
     * Runtime complexity - O(n)
     * Space complexity - O(1)
     **/
    void reverseString(vector<char>& s)
    {
        int n = s.size();

        for (int i = 0; i < n / 2; i++)
        {
            swapChars(s[i], s[n - (1 + i)]);
        }
    }

    void swapChars(char& a, char& b)
    {
        char t = a;
        a = b;
        b = t;
    }

    // ex. 2 - Reverse Integer
    /**
     * Runtime complexity - O(n) [n - input digit length]
     * Space complexity - O(n)
     **/
    int reverse(int x)
    {
        string s = to_string(x);
        vector<char> c(s.begin(), s.end());
        reverseString(c);
        string sr(c.begin(), c.end());
        long l = (c[c.size() - 1] == '-') ?
            -1 * stol(sr.substr(0, c.size() - 1)) :
            stol(sr);
        return (-pow(2, 31) <= l && l <= pow(2, 31) - 1) ? (int) l : 0;
    }

    // ex. 3 - First Unique Character in a String
    /**
     * This solution optimizes on theoretical runtime. for short strings,
     * it would probably be more eficient to just use a nest loop and re-iterate the string for each char.
     * Runtime complexity - O(n)
     * Space complexity - O(n)
     **/
    int firstUniqChar(string s)
    {
        int res = -1;
        map<char, int> m;
        for (int i = 0; i < s.size(); i++)
        {
            char c = s.at(i);
            if (m.find(c) == m.end())
            {
                m[c] = i;
            }
            else
            {
                m[c] = -1;
            }
        }
        for (int i = 0; i < s.size(); i++)
        {
            char c = s.at(i);
            if (m.find(c) != m.end() && m[c] != -1)
            {
                return m[c];
            }
        }
        return -1;
    }

    // ex. 4 - Valid Anagram
    /**
      * here are 3 imp.s using sorted vectors, a multiset and a map(unordered) respectively.
      * surprisingly, the vector-based implementation executed the fastest, although the map-based
      * solution has a better runtime complexity (O(n)).
      * Runtime complexity - O(n * log n)
      * Space complexity - O(n)
      **/
    bool isAnagram(string s, string t)
    {
        if (s.size() != t.size())
        {
            return false;
        }
        vector<char> a(s.begin(), s.end());
        vector<char> b(t.begin(), t.end());
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        for (int i = 0; i < a.size(); i ++)
        {
            if (a[i] != b[i]) return false;
        }
        return true;
    }

    bool isAnagram_v2(string s, string t)
    {
        multiset<char> m(s.begin(), s.end());
        for (char c : t)
        {
            if (m.find(c) == m.end())
            {
                return false;
            }
            m.erase(m.find(c));
        }
        return m.empty();
    }

    bool isAnagram_v3(string s, string t)
    {
        unordered_map<char, int> m;
        for  (char c : s)
        {
        m[c] = (m.find(c) != m.end()) ? m[c] + 1 : 1;
        }

        for (char c : t)
        {
            if (m.find(c) == m.end())
            {
                return false;
            }
            m[c]--;
            if (m[c] == 0)
            {
                m.erase(c);
            }
        }
        return m.empty();
    }

    // ex. 5 -   Valid Palindrome
    bool isPalindrome(string s)
    {
        int r = 0; l = s.size() - 1;
        while (true)
        {
            while (!isalpha(s.at(r)) r++;
            while (!isalpha(s.at(l)) l--;
            if (r >= l) break;
            if (tolower(s.at(r)) != tolower(s.at(r))) return false;
        }
        return true;
    }


}
