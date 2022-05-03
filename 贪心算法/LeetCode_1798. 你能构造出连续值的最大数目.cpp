/*
  题目描述：
    给你一个长度为 n 的整数数组 coins ，它代表你拥有的 n 个硬币。
    第 i 个硬币的值为 coins[i] 。如果你从这些硬币中选出一部分硬币，它们的和为 x ，那么称，你可以 构造 出 x 。
    请返回从 0 开始（包括 0 ），你最多能 构造 出多少个连续整数。
    你可能有多个相同值的硬币。
    
  提示：
    coins.length == n
    1 <= n <= 4 * 104
    1 <= coins[i] <= 4 * 104
    
  链接：
    https://leetcode-cn.com/problems/maximum-number-of-consecutive-values-you-can-make/
*/

/*
  总结：
    要思考 dp(N-1) 对 dp(N) 的影响
    即多填一个元素时,可以得到的结果
    可能添元素后的结果和添元素前并无直接关系,需进行判断,如本题
    以及贪心思想：不考虑之后最优解是否与现在的选择有影响，只有一个子问题，单向考虑
*/

// 评论解答
class Solution {
public:
    int getMaximumConsecutive(vector<int>& coins) {
        int x = 0;                              // 初始化最初可以表达的区间尾 [0:0] 
        sort(coins.begin(),coins.end());        // 升序排序
        for(int i = 0; i < coins.size(); i++)
            // 当能够表示 [0:x], 则添加一个数 y 时
            // 就能表示 [y:y+x], 则只需判断 [0:x] 和 [y:y+x] 是否可以拼接
            if(coins[i] <= x + 1)               // 判断两端是否可以拼接
                x = coins[i] + x;               // 可以的话可表示范围即 [0:y+x]
            else
                return x + 1;                   // 不可以时结束遍历,因为数组是升序,此元素不行之后的元素更不行
        return x + 1;
    }  
};
