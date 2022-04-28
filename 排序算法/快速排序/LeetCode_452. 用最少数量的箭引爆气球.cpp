/*
  题目描述：
     有一些球形气球贴在一堵用 XY 平面表示的墙面上。
     墙面上的气球记录在整数数组 points ，其中points[i] = [xstart, xend] 表示水平直径在 xstart 和 xend之间的气球。你不知道气球的确切 y 坐标。
     一支弓箭可以沿着 x 轴从不同点 完全垂直 地射出。
     在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被 引爆 。
     可以射出的弓箭的数量 没有限制 。 弓箭一旦被射出之后，可以无限地前进。
     给你一个数组 points ，返回引爆所有气球所必须射出的 最小 弓箭数 。
*/

/*
  总结：
    应根据情况合理使用快速排序
    否则容易超时
    
    对于本题，起初基于 Xstart 进行排序
    导致计算弓箭数时计多
*/

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if(points.size()==0)    return 0;

        // 基于 Xend 的升序排序
        sort(points.begin(), points.end(), [](const vector<int>& u, const vector<int>& v) {
            return u[1] < v[1];
        });

        int sum=1;                          // 弓箭数
        int arrow_index=points[0][1];       // 基于 Xend 的弓箭坐标 x
        for(int i=1;i<points.size();i++)
        {
            if(points[i][0]>arrow_index){   // 当 Xstart 超过 x,不能射穿
                sum++;                      // 弓箭数加1
                arrow_index=points[i][1];   // 弓箭坐标 x 移至当前不能射穿气球的 Xend 处
            }
        }
        return sum;                         // 返回最小弓箭数
    }

    // 快速排序详解见 ""
    int PARTITION(vector<vector<int>>& A, int p, int r)
    {
	    int x = A[r][1];
    	int i = p - 1;
	    for (int j = p; j <= r - 1; j++)
		    if ((A[j][1] < x)) {
		    	i++;
			    int temp = A[j][0];
			    A[j][0] = A[i][0];
			    A[i][0] = temp;
                temp = A[j][1];
			    A[j][1] = A[i][1];
			    A[i][1] = temp;
		    }
	    int temp = A[r][0];
	    A[r][0] = A[i + 1][0];
	    A[i + 1][0] = temp;
        temp = A[r][1];
	    A[r][1] = A[i + 1][1];
	    A[i + 1][1] = temp;
	    return i + 1;
    }

    void QUICKSORT(vector<vector<int>>& A, int p, int r)
    {
    	while (p < r) {
	    	int q = PARTITION(A, p, r);
	    	QUICKSORT(A, p, q - 1);
		    p = q+1;
	    }
    }
};
