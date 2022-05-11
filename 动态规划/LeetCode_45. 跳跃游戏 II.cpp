/*
  题目描述：
    给你一个非负整数数组 nums ，你最初位于数组的第一个位置。
    数组中的每个元素代表你在该位置可以跳跃的最大长度。
    你的目标是使用最少的跳跃次数到达数组的最后一个位置。
    假设你总是可以到达数组的最后一个位置。
    
  链接：
    https://leetcode.cn/problems/jump-game-ii/
*/

class Solution {
public:
    int jump(vector<int>& nums) {
        vector<int> dp(nums.size(), -1);    // dp 数组，存放每个下标所需的最少次数，默认 -1
        dp[nums.size()-1] = 0;              // 最后一位默认为 0
        return DP(nums, dp, 0);
    }

    int DP(vector<int>& nums, vector<int>& dp, int index)
    {
        if(dp[index] != -1) return dp[index];       // 当已被 dp 数组记录
        if(index + nums[index] >= nums.size() - 1){ // 当可直接跳到尾元素
            dp[index] = 1;
            return 1;
        }

        int smallest_step = INT_MAX - 1;            // 当前位置后跳到尾元素的最小次数
        int index_cur = index + 1;                  
        for(int i = 1; i <= nums[index]; i++)       // 遍历查找最小次数
              smallest_step = min(smallest_step, DP(nums, dp, index + i));
        dp[index] = smallest_step + 1;              // dp 数组赋值
        return dp[index];
    }
};
