/*
  题目描述：
    给你一个整数数组 nums，请你找出并返回能被三整除的元素最大和。
    
  提示：
   1 <= nums.length <= 4 * 10^4
   1 <= nums[i] <= 10^4
*/

/*
  总结：
    更具特殊情况进行记忆
    被评论区方法惊到
*/

/* 评论区方法 */
class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
         int N = nums.size();       // N:数组长度
        int remainder[3] = {0};     // 初始长度为 3 的数组,默认全赋 0
                                    // (x % 3) 的结果只有三种
                                    // 下标0，1，2 分别代表取余结果为 0，1，2 的三种情况 
        for(int i = 0; i < N; i++){
            int a,b,c;

            // 分别展示保存三种情况原有最大值+当前元素的值
            a = remainder[0] + nums[i];
            b = remainder[1] + nums[i];
            c = remainder[2] + nums[i];

            // 通过 (x % 3) 分别确定不同总和的下标
            // 取和原值的较大者
            remainder[a%3] = max(remainder[a%3], a);
            remainder[b%3] = max(remainder[b%3], b);
            remainder[c%3] = max(remainder[c%3], c);
        }
        return remainder[0];        // 返回结果区域 3 为 0 的最大总和
    }
};
