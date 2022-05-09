/*
  题目描述：
    你将会获得一系列视频片段，这些片段来自于一项持续时长为 time 秒的体育赛事。这些片段可能有所重叠，也可能长度不一。
    使用数组 clips 描述所有的视频片段，其中 clips[i] = [starti, endi] 表示：某个视频片段开始于 starti 并于 endi 结束。
    甚至可以对这些片段自由地再剪辑：
    例如，片段 [0, 7] 可以剪切成 [0, 1] + [1, 3] + [3, 7] 三部分。
    我们需要将这些片段进行再剪辑，并将剪辑后的内容拼接成覆盖整个运动过程的片段（[0, time]）。
    返回所需片段的最小数目，如果无法完成该任务，则返回 -1 。
  
  提示：
    1 <= clips.length <= 100
    0 <= starti <= endi <= 100
    1 <= time <= 100
    
  链接：
    https://leetcode.cn/problems/video-stitching/
*/

/*
    总结：
      未能求出递推式
      dp[i] 不一定只会对 dp[i+1] 或 dp[i-1] 产生影响从而推出它们
*/

// 官方解答
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        vector<int>dp(time+1, INT_MAX-1);   // dp数组，存储 (0, i] 区间所需最小片段数
        dp[0] = 0;                          // 空区间，初始为 0
        for(int i = 1; i <= time; i++)      // 自底向上
            for(auto& it: clips)            // 遍历寻找区间 [ai, aj]，满足 ai < i 并且 aj >= i
                if(it[0] < i && it[1] >= i)
                    dp[i] = min(dp[i], dp[it[0]]+1);    // 递推式 dp[i] = dp[ai] + 1
        return (dp[time] == INT_MAX - 1)? -1 : dp[time];
    }
};
