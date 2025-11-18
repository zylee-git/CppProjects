//
// Created by 22411 on 2025/10/31.
//

#include <iostream>
#include <ostream>
#include <vector>
using namespace std;

class Solution
{
    public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[i] + nums[j] == target)
                    return vector<int>{i, j};
            }
        }
    }
};

int main()
{
    Solution s;
    vector<int> nums = {1,2,3,4,5,6,7,8,9};
    vector<int> a = s.twoSum(nums, 9);
    cout << a[0] << " " << a[1] << endl;
}
