/*
  题目描述：
    给定一个区间的集合 intervals ，其中 intervals[i] = [starti, endi] 。返回 需要移除区间的最小数量，使剩余区间互不重叠 。

  提示:
    1 <= intervals.length <= 105
    intervals[i].length == 2
    -5 * 104 <= starti < endi <= 5 * 104
*/

/*
  总结：
    本题思路于《算法导论》贪心算法章节的第一个问题,活动选择问题,相同
    每次选取最早结束并且于之前选取区间兼容的区间
*/

class Solution {
public:
    static bool sortSecondOne(vector<int>& S1, vector<int>& S2)
    {
        return S1[1] < S2[1];
    }

    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), sortSecondOne);    // 基于 intervals[i][1] 的升序排序
        int leftSum = 1;    // 剩余的区间数 
        int index_pre = 0;  // 剩余区间最后一个区间的索引
        for(int i = 1; i < intervals.size(); i++)
            if(intervals[i][0] >= intervals[index_pre][1]){     
                            // 当 i 是满足 start(i) 小于 end(index_pre)
                            // 则 i 是兼容的最早结束区间(end[i]最小)
                leftSum++;      // 剩余区间数累加
                index_pre = i;  // 索引指向当前区间最为兼容区间的尾元素
            }
        return intervals.size() - leftSum;      // 减去的区间数
    }
};
