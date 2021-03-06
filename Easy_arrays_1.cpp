class Easy_arrays_Solution {
public:

    // ex. 1 - Remove Duplicates from Sorted Array
        /**
         * Runtime complexity - O(n)
         * Space complexity - O(1)
         **/
    int removeDuplicates(vector<int>& nums) 
    {
        if (nums.size() == 0)
        {
            return 0;
        }
        int n = nums.size();
        int k = 1;
        for (int i = 1; i < n; i++)
        {
            if (nums[i] != nums[i - 1])
            {
                nums[k] = nums[i];
                k++;
            }                                  
        }
        return k; 
    }

    // ex. 2 - Best Time to buy and sell stock
        /**
         * Runtime complexity - O(n)
         * Space complexity - O(1)
         **/
        int maxProfit(vector<int>& prices) 
    {
        if (prices.size() == 0)
        {
            return 0;
        }
        bool holding = false;
        int profit = 0;
        int profitBeforeLastSell = 0;
        int n = prices.size();
        for (int i = 0; i < n; i++)
        {
            if (isLocalMin(prices, i) && !holding)
            {
                holding = true;
                profit -= prices[i];
            }
            else if (isLocalMax(prices, i) && holding)
            {
                profit += prices[i];
                profitBeforeLastSell = profit;
                holding = false;
            }
        }
        return (profit > profitBeforeLastSell) ? profit : profitBeforeLastSell;
    }

    /**
     * helper for ex2, answers element i is local max in array.
     **/    
    bool isLocalMax(vector<int>& arr, int i)
    {
        if(arr.size() == 1 && i == 0)
        {
            return true;
        }
        
        if (i == 0)
        {
            return (arr[i] >= arr[i + 1]);
        }
        else if(i == arr.size() - 1)
        {
            return (arr[i] >= arr[i - 1]);
        }
        return (arr[i] >= arr[i - 1] && arr[i] >= arr[i + 1]);
    }
    

    /**
     * helper for ex2, answers element i is local min in array.
     **/

    bool isLocalMin(vector<int>& arr, int i)
    {
        if(arr.size() == 1 && i == 0)
        {
            return true;
        }
        
        if (i == 0)
        {
            return (arr[i] <= arr[i + 1]);
        }
        else if(i == arr.size() - 1)
        {
            return (arr[i] <= arr[i - 1]);
        }
        return (arr[i] <= arr[i - 1] && arr[i] <= arr[i + 1]);
    }

    // ex. 3 - Rotate Array

        /**
         * Runtime complexity - O(n)
         * Space complexity - O(1)
         **/
    void rotate(vector<int>& nums, int k) 
    {
        if (nums.empty())    
        {
            return;
        }
        int n = nums.size();
        if (k >= n)
        {
            if (k % n == 0)
            {
                return;
            }
            k = k % n;
        }
        reverseVector(nums, 0, n - 1);
        reverseVector(nums, 0, k - 1);
        reverseVector(nums, k, n - 1);
    }
    
    /**
    * reverses vector array from index "start" to index "end".
    **/
    void reverseVector(vector<int>& a, int start, int end)
    {
        float n = end - start;
        int temp;
        for (int i = 0; i < n / 2; i++)
        {
            temp = a[start + i];
            a[start + i] = a[end - i];
            a[end - i] = temp;
        }
    }

    // ex. 4 - Contains Duplicate

        /**
         * note - this solution is not optimal for runtime, since not using a Hash set.
         * Runtime complexity - O(n*log n) - ruled by sort.
         * Space complexity - O(n)
         **/
        bool containsDuplicate(vector<int>& nums) 
    {
        vector<int> nums2(nums);
        sort(nums2.begin(), nums2.end());
        int prev = nums2[0];
        int n = nums2.size();
        for (int i = 1; i < n; i++)
        {
            if (nums2[i] == prev)
            {
                return true;
            }
            prev = nums2[i];
        }
        return false;
    }

    // ex. 5 - Single Number

        /**
         * this solution is not optimal, yet it is unique and holds for the given restrictions:
         * Runtime complexity - O(n)
         * Space complexity - O(1)
         **/

    int singleNumber(vector<int>& nums) 
    {
        auto minmax = minmax_element(nums.begin(), nums.end());
        int min = *minmax.first;
        int max = *minmax.second;
        int c_under, c_over;
        float avg;
        while (true)
        {   
            c_under = 0; // includes equal to avg.
            c_over = 0;
            avg = (float) (min + max) / 2;
            for (int e : nums)
            {
                if (e > avg)
                {
                    c_over++;
                }
                else if (e < avg)
                {
                    c_under++;
                }
            }
            if (abs(min - max) <= 1)
            {
                return (c_over % 2 == 0) ? min : max;
            }
            if (c_over % 2 == 0)
            {
                max = ceil(avg);
            }
            else
            {
                min = floor(avg);
            }
        }
    }

    // ex. 6 - Intersection of Two Arrays II

        /**
        * Runtime complexity - O(n)
        * Space complexity - O(k), k := elements range;
        **/

        vector<int> intersect(vector<int>& nums1, vector<int>& nums2) 
    {
        map<int, pair<int, int>> m;
        vector<int> *shortNums, *longNums;
        if (nums1.size() > nums2.size())
        {
            shortNums = &nums2;
            longNums = &nums1;
        }
        else
        {
            shortNums = &nums1;
            longNums = &nums2;
        }
        for (int e : *shortNums)
        {
            if (m.find(e) == m.end())
            {
                // m.insert(pair<int, pair<int, int>>(e, (1, 0)));
                m[e] = pair<int, int>(1, 0);
            }
            else
            {
                m[e].first++;
            }
        }
        for (int e : *longNums)
        {
            if (m.find(e) != m.end())
            {
                m[e].second++;
            }
        }
        vector<int> result;
        for (pair<int, pair<int, int>> kv : m)
        {
            int times = min(kv.second.first, kv.second.second);
            while(times--)
            {
                result.push_back(kv.first);
            }
        }
        return result;
    }


    // ex. 7 - PlusOne

        /**
        * Runtime complexity - O(n)
        * Space complexity - O(k), k := elements range;
        **/
        vector<int> plusOne(vector<int>& digits) 
        {
            int i = digits.size() - 1;
            while (i >= 0)
            {
                if (digits[i] < 9)
                {
                    ++digits[i];
                    return digits;
                }
                digits[i] = 0;
                i--;
            }
            digits.insert(digits.begin(), 1);
            return digits;
    }


    // ex. 8 -  Move Zeroes

        /**
        * Runtime complexity - O(n)
        * Space complexity - O(1)
        **/
        void moveZeroes(vector<int>& nums) 
        {
             int n = nums.size();
             int nonZero = 0;
             int temp;
             for (int i = 0; i < n; i++)   
             {
                 if (nums[i] != 0)
                 {
                     temp = nums[i];
                     nums[i] = 0;
                     nums[nonZero] = temp;
                     nonZero++;
                 }
             }
        }


    //ex.9 - Two Sum
        /**
        * Runtime complexity - O(n)
        * Space complexity - O(n + m) m - values range
        **/
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        map<int, int> m;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            if (m.find(target - nums[i]) != m.end())
            {
              return vector<int>{m[target - nums[i]], i};   
            }
            m[nums[i]] = i;
        }
        return vector<int>();
    }


    /**
     * This was my first solution. Although not optimal, it has a theoretical runtime complexity
     * of O(n log n). In reality, it exceeded the site's time limit.
     * */
    vector<int> twoSumDraft1(vector<int>& nums, int target) 
    {
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());
        int l = 0, r = nums.size() - 1;
        int n = nums.size(), q, mid;
        for (int i = 0; i < n; i++)
        {
            q = target - sorted[i];
            l = i;
            r = sorted.size() -1;
            while (l < r)
            {
                int mid = (l + r) / 2;
                if (sorted[mid] == q)
                {
                    vector<int> res;
                    for(int j = 0; j < n; j++)
                    {
                        if (nums[j] == sorted[i] || nums[j] == sorted[mid])
                        {
                            res.push_back(j);
                            if (res.size() == 2)
                            {
                                return res;
                            }
                        }
                    }
                }
                else if (sorted[mid] > q)
                {
                    r = mid;
                }
                else
                {
                    l = mid;
                }
            }
        }
        return vector<int>();
    }


    // ex. 10 - Valid Sudoku
        /**
        * Runtime complexity - O(n)
        * Space complexity - O(n) - because hashSet value entries are bounded, each one is O(9) = O(1) - the number of required
        * is then dictated by the input (board) size - n.
        **/
    bool isValidSudoku(vector<vector<char>>& board) 
    {
        vector<set<int>> rows(9);
        vector<set<int>> cols(9);
        vector<set<int>> cubes(9);
        int cube, e;
        for(int i = 0; i < 9; i++)
        {
             for(int j = 0; j < 9; j++)
            {
                e = board[i][j];
                if (e != '.')
                {
                    
                    cube = (i / 3)  * 3 + (j / 3);
                    cout << cube << endl;
                    if (rows[i].find(e) != rows[i].end() ||
                        (cols[j].find(e) != cols[j].end() ||
                        cubes[cube].find(e) != cubes[cube].end()))
                    {
                        return false;
                    }
                    rows[i].insert(e);
                    cols[j].insert(e);
                    cubes[cube].insert(e);
                }
                
            }   
        }
        return true;
    }

    ex. 11 - Rotate Image
    /**
        * Runtime complexity - O(n)
        * Space complexity - O(1) - done in place.
        **/
    void rotate(vector<vector<int>>& matrix) 
    {
        int n = matrix[0].size();
        float q = (float) n / 2;
        n--;
        int t;
        for (int i = 0; i < floor(q); i++)
        {
            for (int j = 0; j < ceil(q); j++)
            {
                t = matrix[n - j][i];
                matrix[n - j][i] = matrix[n - i][n - j];
                matrix[n - i][n - j] = matrix[j][n - i];
                matrix[j][n - i] =  matrix[i][j];
                matrix[i][j] = t;
            }
        }
    }


};