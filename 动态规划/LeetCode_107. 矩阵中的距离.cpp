/*
  题目描述：
    给定一个由 0 和 1 组成的矩阵 mat ，请输出一个大小相同的矩阵，其中每一个格子是 mat 中对应位置元素到最近的 0 的距离。
    两个相邻元素间的距离为 1 。
    
  提示：
    m == mat.length
    n == mat[i].length
    1 <= m, n <= 104
    1 <= m * n <= 104
    mat[i][j] is either 0 or 1.
    mat 中至少有一个 0 
*/

/*
  总结：
    要思考最有子问题存在哪几种可能，按照不同的可能列写递推式
    
    在矩阵中寻找距离不一定要如同DFS或BFS一样一直延申到头
		每个元素取左上向右下遍历，右下向左上遍历
		取与本身比较较小值，也可以做出此效果
*/


/* 官方答案 */
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m=mat.size();       // 矩阵宽
        int n=mat[0].size();    // 矩阵长
        vector<vector<int>>result(m,vector<int>(n,INT_MAX/2));
                                // 初始化 m*n 结果矩阵,默认值为 INT_MAX/2
                                // 除以 2 的原因是防止超过 int 上界

        for(int i=0;i<m;i++)    // 遍历矩阵,将结果矩阵[原矩阵为 0 的位置]赋值 0
            for(int j=0;j<n;j++)
                if(mat[i][j]==0)
                    result[i][j]=0;
        
        // 向左，向上 方向遍历矩阵
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++){
                if(i-1>=0)  result[i][j]=min(result[i][j],result[i-1][j]+1);
                if(j-1>=0)  result[i][j]=min(result[i][j],result[i][j-1]+1);
            }

        /*  只需左上和右下即可
        
        // 向左，向下 方向遍历矩阵
        for(int i=m-1;i>=0;i--)
            for(int j=0;j<n;j++){
                if(i+1<m)   result[i][j]=min(result[i][j],result[i+1][j]+1);
                if(j-1>=0)  result[i][j]=min(result[i][j],result[i][j-1]+1);
            }
            
        */

        /*  只需左上和右下即可
        
        // 向右，向上 方向遍历矩阵
        for(int i=0;i<m;i++)
            for(int j=n-1;j>=0;j--){
                if(i-1>=0)  result[i][j]=min(result[i][j],result[i-1][j]+1);
                if(j+1<n)   result[i][j]=min(result[i][j],result[i][j+1]+1);
            }
            
        */

        // 向右，向下 方向遍历矩阵
        for(int i=m-1;i>=0;i--)
            for(int j=n-1;j>=0;j--){
                if(i+1<m)   result[i][j]=min(result[i][j],result[i+1][j]+1);
                if(j+1<n)   result[i][j]=min(result[i][j],result[i][j+1]+1);
            }
    
        return result;      // 返回结果矩阵
    }
};
