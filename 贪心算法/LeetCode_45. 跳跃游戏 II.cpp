/*
  题目描述：
    给你一个非负整数数组 nums ，你最初位于数组的第一个位置。
    数组中的每个元素代表你在该位置可以跳跃的最大长度。
    你的目标是使用最少的跳跃次数到达数组的最后一个位置。
    假设你总是可以到达数组的最后一个位置。
    
  链接：
    https://leetcode.cn/problems/jump-game-ii/
*/

/*
  总结：
    每次寻找涉及最远的点
    本题的贪心算法遍历次数为 n
    比动态规划效果好很多
*/

class Solution {
public:
    int jump(vector<int>& nums) {
        int index = 0;          // 下标索引
        int counts = 0;         // 跳跃次数
        while(index < nums.size()){
            if(index + nums[index] >= nums.size() - 1){     // 当此位置可直接跳到尾元素
                if(index < nums.size() - 1) counts++;       // 当本身就是尾元素，不必加 1
                return counts;
            }
            int add_largest = 1;                            // 下标增加量
            for(int i = 2; i <= nums[index]; i++)           // 寻找涉及最远的下标
                add_largest = (add_largest + nums[index + add_largest] <= i + nums[index + i])? i : add_largest;
            index += add_largest;
            counts++;
        }
        return counts;
    }
};
