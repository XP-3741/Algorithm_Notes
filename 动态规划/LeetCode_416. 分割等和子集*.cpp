/*
  题目描述：
    给你一个 只包含正整数 的 非空 数组 nums 
    请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等
    
  提示：
    1 <= nums.length <= 200
    1 <= nums[i] <= 100
    
  链接：
    https://leetcode.cn/problems/partition-equal-subset-sum/
*/

/*
  总结：
    此问题属于 0-1背包问题
    每个元素选与不选之中抉择
    二维 dp 数组的运用
    
    递推式：
                    -- dp[i-1][j] | dp[i-1][j-nums[i]]   , nums[i] <= j
    dp[i][j] =  -- |
                    -- dp[i-1][j]                        , nums[i] > j
    
    优化后的递推式：
    
    dp[j] = dp[j] | dp[j-1]
*/

// 官方解答
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        if(nums.size() < 2) return false;       // 数组长度<2无法分割
        
        int sum = 0;
        int _max = 0;
        for(int k: nums){                       // 求和
            sum += k;
            _max = max(_max, k);                // 求最大元素
        }
        if(sum/2.0 != sum/2 || _max > sum/2)   // 总和不是偶数无法等分，最大元素大于 target 不存在子集满足条件
            return false;   

        const int target = sum/2;               // 目标值
        vector<vector<bool>>dp(nums.size(), vector<bool>(target+1, false));
                                                // 二维数组 dp[i][j]
                                                // 表示 [0..i] 是否可以选取其中元素凑出 j

        for(int i = 0; i < nums.size(); i++)    // 任何个数元素都可凑出 0，即一个元素都不选
            dp[i][0] = true;
        dp[0][nums[0]] = true;                  // i = 0 时只有一个元素 nums[i] 可选

        for(int i = 1; i < nums.size(); i++)
            for(int j = 1; j <= target; j++){   // 两种情况
                if(nums[i] > j){                // 1. nums[i] > j 时，为凑出 j, nums[i] 肯定不选 
                    dp[i][j] = dp[i-1][j];      // 所以 dp[i][j] 依赖于 dp[i-1][j]
                    continue;
                }
                dp[i][j] = (dp[i-1][j-nums[i]] || dp[i-1][j]);
                                                // 2. nums[i] <= j 时
                                                // nums[i] 可能选也可能不选，但只要其中一种是 true 就行
                                                // 即依赖于 dp[i-1][j-nums[i]]  (不选nums[i])
                                                // 或 dp[i-1][j]   (选nums[i])
            }
        return dp[nums.size()-1][target];       // 返回结果
    }
};

// 官方解答
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) {
            return false;
        }
        int sum = 0, maxNum = 0;
        for (auto& num : nums) {
            sum += num;
            maxNum = max(maxNum, num);
        }
        if (sum & 1) {                  // 是否为偶数，即 二进制 最后一位是否为 0， 与 1 按位与
            return false;
        }
        int target = sum / 2;
        if (maxNum > target) {
            return false;
        }
        vector<int> dp(target + 1, 0);  // 发现在计算 dp 的过程中，每一行的 dp 值都只与上一行的 dp 值有关
                                        // 因此只需要一个一维数组即可将空间复杂度降到 O(target)
                                        // 此时的转移方程为 dp[j] = dp[j] | dp[j-1]
        dp[0] = true;
        for (int i = 0; i < n; i++) {
            int num = nums[i];
                                        // 且需要注意的是第二层的循环我们需要从大到小计算
                                        // 因为如果我们从小到大更新 dp 值
                                        // 那么在计算 dp[j] 值的时候，dp[j-nums[i]] 已经是被更新过的状态
                                        // 不再是上一行的 dp 值
            for (int j = target; j >= num; --j) {
                dp[j] |= dp[j - num];
            }
        }
        return dp[target];
    }
};
