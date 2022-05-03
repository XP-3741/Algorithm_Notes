/*
  题目描述：
    给你一个正整数数组 values，其中 values[i] 表示第 i 个观光景点的评分，并且两个景点 i 和 j 之间的 距离 为 j - i。
    一对景点（i < j）组成的观光组合的得分为 values[i] + values[j] + i - j ，也就是景点的评分之和 减去 它们两者之间的距离。
    返回一对观光景点能取得的最高分。
    
  提示：
    2 <= values.length <= 5 * 104
    1 <= values[i] <= 1000
*/

/*
  总结：
     题目给出得分公式，就应更多注意力在这个公式上
     而不是一直想着动态规划的解题步骤试图自己设想出递推式
     备忘录也不一定是所有子问题的最优解
     可能只是一两个变量值，如本题的 mx
*/

// 官方解答
class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int maxScore = -1 * INT_MAX;    // 最高得分初始化最小值
        /* 
            将得分拆分成 values[i] + i 和 values[j] - j
            j 为当前遍历索引,所以 values[j] - j 为确定值
            所以求取 j 在 [0..j-1] 中的最高得分景点 i
            即求 i 属于 [0..j-1] 中 values[i] + i 的最大值 mx
        */
        int mx = values[0];             // 初始化 mx: values[0] + 0
        for(int j = 1; j < values.size(); j++){             // 从 j = 1 开始遍历
            maxScore = max(mx + values[j] - j, maxScore);   // 求取更高得分 maxScore
            mx = max(values[j] + j, mx);                    // 求取更大 mx
        }
        return maxScore;
    }
};
