/*
  题目描述：
    石子游戏中，爱丽丝和鲍勃轮流进行自己的回合，爱丽丝先开始 。
    有 n 块石子排成一排。每个玩家的回合中，可以从行中 移除 最左边的石头或最右边的石头，并获得与该行中剩余石头值之 和 相等的得分。当没有石头可移除时，得分较高者获胜。
    鲍勃发现他总是输掉游戏（可怜的鲍勃，他总是输），所以他决定尽力 减小得分的差值 。爱丽丝的目标是最大限度地 扩大得分的差值 。
    给你一个整数数组 stones ，其中 stones[i] 表示 从左边开始 的第 i 个石头的值，如果爱丽丝和鲍勃都 发挥出最佳水平 ，请返回他们 得分的差值 。
    
  提示：
    n == stones.length
    2 <= n <= 1000
    1 <= stones[i] <= 1000
*/

/*
  总结：
    博弈+动态规划
    当寻找递推式时,不一定是找 dp[i] 对 dp[i+1] 的影响
    也可能是 dp[i] 对 dp[i-1] 的影响
    找规律时在区间内一步一步思考结果
*/

// 评论解答
class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        int n = stones.size();
        int dp[n][n];               // dp[i][j] 表示 [i..j] Alice先拿时的最大差值
        memset(dp, 0, sizeof(dp));  // 初始化全 0
        //通过动态方程,发现i和 >=i的有关系,j和<=j的有关系.
        //所以计算需要i从大到小,j从小到大,这样才能正确.
        for(int i = n - 2; i >= 0; i--)
            for(int j = i + 1; j < n; j++)
                if(j == i + 1)
                    dp[i][j] = max(stones[i], stones[j]);
                else{
                    // 如果 Alice 先选 i,那么 bobo 只能选 i+1 或者 j,这时候差值就是 stones[i+1] 或者 stones[j]
                    // 再加上子区间 dp 的差值就是当前区间的 dp 值
                    // left 和 right 就相当于 bobo 选择后的差值,即为 Alice 的可能得分
                    // bobo 为了减少差距,就会在选择 Alice 选择一端后的较小值,所以用 min
                    // dp 则是 Alice 的差值,为了尽可能大,所以用 max
                    int left = min(stones[j] + dp[i+1][j-1], stones[i+1] + dp[i+2][j]);
                    int right = min(stones[i] + dp[i+1][j-1], stones[j-1] + dp[i][j-2]);
                    dp[i][j] = max(left, right);
                }
        return dp[0][n-1];
    }
};
