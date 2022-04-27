/*
  题目描述：
    给你一个整数 mass ，它表示一颗行星的初始质量。
    再给你一个整数数组 asteroids ，其中 asteroids[i] 是第 i 颗小行星的质量。
    你可以按 任意顺序 重新安排小行星的顺序，然后让行星跟它们发生碰撞。
    如果行星碰撞时的质量 大于等于 小行星的质量，那么小行星被 摧毁 ，并且行星会 获得 这颗小行星的质量。否则，行星将被摧毁。
    如果所有小行星 都 能被摧毁，请返回 true ，否则返回 false 。
*/

/*
  总结：
    需考虑情况选择排序算法
    此题初始用的快速排序但超过时间上限
*/

class Solution {
private:
    int heap_size=0;
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        //QUICKSORT(asteroids,0,asteroids.size()-1);    // 快速排序
        HEAPSORT(asteroids);    // 堆排序
        for(int i=0;i<asteroids.size();i++)
            if(mass>=asteroids[i]){     // 当行星质量大
                if(mass+asteroids[i]>=100000)    return true;   // 当和超过小行星质量上界
                mass+=asteroids[i];     // 质量叠加
            }
            else   return false;        // 当行星质量小
        return true;
    }

    // 快速排序
    int PARTITION(vector<int>& A,int p,int r)
    {
        int x=A[r];             // 将数组尾元素作为数组分界值
        int i=p-1;              // 比分界值小的元素最后下标
        for(int j=p;j<r;j++)    // 遍历
            if(A[j]<x){         // 当此元素小于分界值
                i++;            // 比分界值小的元素最后下标 i 加1
                int temp=A[j];  // 交换当前元素 j 和 i 的值
                A[j]=A[i];
                A[i]=temp;
            }
        int temp=A[i+1];        // 将分界值从尾元素转至分界点
        A[i+1]=A[r];
        A[r]=temp;
        return i+1;             // 返回分界点
    }

    void QUICKSORT(vector<int>& A,int p,int r)
    {// 快速排序
        if(p<r){    // 递归条件
            int q=PARTITION(A,p,r); // 按照分界值分界数组并获得分界值
            QUICKSORT(A,p,q-1);     // 递归调用前半界
            QUICKSORT(A,q+1,r);     // 递归调用后半界
        }
    }

    // 堆排序
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
