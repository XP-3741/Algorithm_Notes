/*
  题目描述：
    给你一个由 不同 整数组成的数组 nums ，和一个目标整数 target 。请你从 nums 中找出并返回总和为 target 的元素组合的个数。
    题目数据保证答案符合 32 位整数范围。
    
  提示：
    1 <= nums.length <= 200
    1 <= nums[i] <= 1000
    nums 中的所有元素 互不相同
    1 <= target <= 1000
*/

/*
  总结：
    最优子问题的递归元素不一定是各个组合数的组合方式
    本体为target(总和)
    它依赖于总和为target-num[i]的元素个数
*/

/* 官方答案 */
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> Kinds(target+1);    // 备忘录
                                        // kind[i] 记录总和为 i 的元素组合个数
        Kinds[0]=1;     // i = 0(总和为 0) 的情况只有一种: 一个元素也不选(元素值>=1)

        for(int i=1;i<=target;i++)      // 总和值[1..target]遍历
            for(int num:nums)           // 对于每个总和值 i,遍历数组 nums 每个元素逐个尝试
                if(num<=i && Kinds[i]<INT_MAX-Kinds[i-num])
                                        // 因为 i = (i - num) + num
                                        // 所以 下标为 i(总和值为 i) 的个数依赖于 下标为 i-num 的个数
                    Kinds[i]+=Kinds[i-num];
        return Kinds[target];
    }
};
