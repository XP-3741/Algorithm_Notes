/*
  题目描述：
    在一个长度 无限 的数轴上，第 i 颗石子的位置为 stones[i]。
    如果一颗石子的位置最小/最大，那么该石子被称作 端点石子 。
    每个回合，你可以将一颗端点石子拿起并移动到一个未占用的位置，使得该石子不再是一颗端点石子。
    值得注意的是，如果石子像 stones = [1,2,5] 这样，你将 无法 移动位于位置 5 的端点石子，因为无论将它移动到任何位置（例如 0 或 3），该石子都仍然会是端点石子。
    当你无法进行任何移动时，即，这些石子的位置连续时，游戏结束。
    要使游戏结束，你可以执行的最小和最大移动次数分别是多少？ 
    以长度为 2 的数组形式返回答案：answer = [minimum_moves, maximum_moves] 。
*/

/*
  总结：
    未懂
*/

class Solution {
private:
    int heap_size=0;
public:
    vector<int> numMovesStonesII(vector<int>& stones) {
        HEAPSORT(stones);
        int n = stones.size();
        int mx = stones[n-1] - stones[0] + 1 - n;
        mx -= min(stones[n-1]-stones[n-2]-1, stones[1]-stones[0]-1);
        int mi = mx;
        int i = 0;
        int j = 0;
        for(i = 0; i < n; ++i)
        {
            while(j + 1 < n && stones[j + 1] - stones[i] + 1 <= n)
                ++j;
            int cost = n - (j - i + 1);
            if(j - i + 1 == n - 1&& stones[j] - stones[i] + 1 == n - 1)
                cost = 2;
            mi = min(mi, cost);
        }
        return vector<int>{mi, mx};
    }
    
    // 堆排序详解见 "LeetCode_1481. 不同整数的最少数目.cpp"
    int PARENT(int i)
    {
        return i/2;
    }
  
    int LEFT(int i)
    {
        return 2*i;
    }
  
    int RIGHT(int i)
    {
        return 2*i+1;
    }
  
    void MAX_HEAPIFY(vector<int>& A,int i)
    {
        int l=LEFT(i+1)-1;
        int r=RIGHT(i+1)-1;
        int largest=i;
        if(l<heap_size&&A[l]>A[i])
            largest=l;
        if(r<heap_size&&A[r]>A[largest])
            largest=r;
        if(largest!=i){
            int temp=A[i];
            A[i]=A[largest];
            A[largest]=temp;
            MAX_HEAPIFY(A,largest);
        }
    }
  
    void BUILD_MAX_HEAP(vector<int>& A)
    {
        heap_size=A.size();
        for(int i=A.size()/2-1;i>=0;i--)
            MAX_HEAPIFY(A,i);
    }
  
    void HEAPSORT(vector<int>& A)
    {
        BUILD_MAX_HEAP(A);
        for(int i=A.size()-1;i>0;i--){
            int temp=A[0];
            A[0]=A[i];
            A[i]=temp;
            heap_size--;
            MAX_HEAPIFY(A,0);
        }
    }
};
