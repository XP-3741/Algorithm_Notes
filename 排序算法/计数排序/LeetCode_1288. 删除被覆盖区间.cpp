/*
  题目描述：
    给你一个区间列表，请你删除列表中被其他区间所覆盖的区间。
    只有当 c <= a 且 b <= d 时，我们才认为区间 [a,b) 被区间 [c,d) 覆盖。
    在完成所有删除操作后，请你返回列表中剩余区间的数目。
    
    提示：
      1 <= intervals.length <= 1000
      0 <= intervals[i][0] < intervals[i][1] <= 10^5
      对于所有的 i != j：intervals[i] != intervals[j]
*/

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {

        int length=intervals.size();        // 数组 intervals 长度
                                            // 即区间个数
        if(length==1)   return 1;

        int max=0;                          // 数组 intervals[][1] 最大值
        for(int i=0;i<length;i++)           // 寻找最大值
            if(max<intervals[i][1])
                max=intervals[i][1];

        vector<vector<int>> result(length+1,vector<int>(2));    // 存放排序结果
        COUNTING_SORT(intervals,result,max);    // 计数排序
        return rest_num(result,length);         // 返回剩余区间数目
    }

    void COUNTING_SORT(vector<vector<int>>& A,vector<vector<int>>& B,int max)
    {// 计数排序    
     // A：原数组   B：排序后的数组   max：数组A的最大值

        vector<int> C(max+1);           // 申请数组 C[1..max]

        for(int i=0;i<=max;i++)         // 初始化数组 C,全部赋 0
            C[i]=0;

        for(int j=0;j<A.size();j++)     // 基于 A 元素值为数组 C 下标,统计 A 每个元素个数
            C[A[j][1]]++;

        for(int i=1;i<=max;i++)         // 遍历数组 C,当前元素加上前驱元素
            C[i]+=C[i-1];               // 用以表示每个元素应当在排序后的位置

        for(int j=A.size()-1;j>=0;j--){ // 倒叙遍历数组 A
            B[C[A[j][1]]][1]=A[j][1];   // 将 A[i] 作为 C 下标的 C[A[i]] 作为数组 B 的下标进行赋值
            B[C[A[j][1]]][0]=A[j][0];
            C[A[j][1]]--;               // 当前元素在 B 中的下标向前移动一位
                                        // 即如果出现相同元素
                                        // 此元素的位置在当前元素前一位
        }
    }

    int rest_num(vector<vector<int>>& B,int length)
    {
        int arrow=B[B.size()-1][0];     // 区间头
        int tow=B[B.size()-1][1];       // 区间尾

        for(int i=B.size()-2;i>0;i--){  // 倒叙遍历
            if(B[i][0]!=-1&&B[i][1]==tow){  // 当区间尾重叠
                if(B[i][0]<=arrow){     // 将较大的区间头作为 arrow 值
                    arrow=B[i][0];
                }
                length--;               // 区间尾重叠,其中必有一个区间被覆盖
            }else if(B[i][0]!=-1&&B[i][0]>=arrow){  // 当不重叠,即当前区间尾小于 tow
                                                    // 并且当前区间头大于等于 arrow
                                                    // 即当前区间被 arrow/tow 覆盖
                length--;               // 区间数减1
                B[i][0]=-1;             // 将被覆盖的区间头赋值-1,作为被删除标志
            }else if(B[i][0]!=-1){      // 当都不满足,即并没有被 arrow/tow 覆盖
                arrow=B[i][0];          // arrow 赋值当前区间头
                tow=B[i][1];            // tow 赋值当前区间尾
            }
        }
        return length;                  // 返回剩余区间数
    }
};
