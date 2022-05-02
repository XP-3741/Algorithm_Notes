/*
  题目描述：
    给定一个长度为 n 的整数数组 nums 。
    假设 arrk 是数组 nums 顺时针旋转 k 个位置后的数组，我们定义 nums 的 旋转函数  F 为：
    F(k) = 0 * arrk[0] + 1 * arrk[1] + ... + (n - 1) * arrk[n - 1]
    返回 F(0), F(1), ..., F(n-1)中的最大值 。
    生成的测试用例让答案符合 32 位 整数。
    
  提示:
    n == nums.length
    1 <= n <= 105
    -100 <= nums[i] <= 100
*/

/*
  数学+动态规划
  未能找出数学递推式
  遇到类似存在规律的题目应多列几项寻找其中的规律
*/

/* 官方解答 */
class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        vector<int>Fk(nums.size());         // 备忘录
        int sums_nums = 0;                  // 数组 nums 所有元素和
        for(int i=0;i<nums.size();i++){     // 求出 k = 0 时的 F(k) 和数组 nums 的元素和
            Fk[0]+=i*nums[i];
            sums_nums+=nums[i];
        }
        int Max = Fk[0];                    // 最大值
        for(int k=1;k<nums.size();k++){     // 利用递推式迭代
                        // 递推式：
                        // F(k) = F(k-1) + nums.sum - n * nums[n - k]
            Fk[k] = Fk[k-1] + sums_nums - nums.size() * nums[nums.size() - k];
            Max = max(Max, Fk[k]); 
        }
        return Max;
    }
};
