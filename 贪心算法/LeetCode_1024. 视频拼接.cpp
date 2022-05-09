/*
  题目描述：
    你将会获得一系列视频片段，这些片段来自于一项持续时长为 time 秒的体育赛事。这些片段可能有所重叠，也可能长度不一。
    使用数组 clips 描述所有的视频片段，其中 clips[i] = [starti, endi] 表示：某个视频片段开始于 starti 并于 endi 结束。
    甚至可以对这些片段自由地再剪辑：
    例如，片段 [0, 7] 可以剪切成 [0, 1] + [1, 3] + [3, 7] 三部分。
    我们需要将这些片段进行再剪辑，并将剪辑后的内容拼接成覆盖整个运动过程的片段（[0, time]）。
    返回所需片段的最小数目，如果无法完成该任务，则返回 -1 。
  
  提示：
    1 <= clips.length <= 100
    0 <= starti <= endi <= 100
    1 <= time <= 100
    
  链接：
    https://leetcode.cn/problems/video-stitching/
*/

/*
    总结：
      与《算法导论》的 ‘16.1 活动选择问题’ 思想相同，方法相反
      本题是以开始时间为关键字排序，并且求取满足要求的最长片段
      《算法导论》的是以结尾时间为关键字排序，并且求取满足要求的最短片段
      
      官方解答，牛逼
      只要又满足的片段组合，[0..time] 作为开始时间的片段(可剪辑)必存在
      所以遍历 time 次即可
*/

class Solution {
public:
    static bool sort_first(vector<int>& s1, vector<int>& s2)
    {
        if(s1[0] < s2[0])
            return true;
        return false;
    }

    int videoStitching(vector<vector<int>>& clips, int time) {
        sort(clips.begin(), clips.end(), sort_first);   // 以开始时间为关键字升序

        int counts = 0;     // 所需片段个数
        int index_cur = 0;  // clips 数组索引
        int pre_end = 0;    // 上一片段的结束时间
        while(index_cur < clips.size()){
            int longest_end = pre_end;  // 求能与上一片段结合并且最长的片段，初始值为上一片段结束时间
            while(index_cur < clips.size() && clips[index_cur][0] <= pre_end){  // 遍历查找满足要求片段
                if(clips[index_cur][1] > longest_end)       
                    longest_end = clips[index_cur][1];      // 最长片段结束时间
                index_cur++;
            }

            if(longest_end > pre_end){  // 检查是否还是初始值
                counts++;               // 值改变说明满足有要求片段，个数加 1
                pre_end = longest_end;  // 上一片段结尾时间赋值为当前片段结尾时间为下个循环使用
            }else
                return -1;              // 值未改变说明无可衔接片段，返回 -1

            if(pre_end >= time) return counts;  // 检查是否已满足 time 要求
        }
        if(pre_end < time)  return -1;  // 当满足的最长片段未能达到 time 要求
        return counts;
    }
};

// 官方解答
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        vector<int>maxn(time);          // 下标代表视频开始时间，记录对应的最长结束时间
        for(vector<int>& it: clips)     // 初始化 maxn
            if(it[0] < time)
                maxn[it[0]] = max(maxn[it[0]], it[1]);

        int last = 0;       // 当前片段和上一片段结束时间的较大值
        int pre = 0;        // 上一片段的结束时间
        int counts = 0;     // 所需片段数量

        for(int i = 0; i < time; i++){
            last = max(maxn[i], last);

            if(i == last)   // 当开始时间等于结束时间，表示无法衔接
                return -1;

            if(i == pre){   // 当到达上一最长时间片段结尾
                counts++;   // 片段数加 1
                pre = last; // 上一最长时间片段结束时间赋值为当前片段结束时间
            }
        }
        return counts;
    }
};
