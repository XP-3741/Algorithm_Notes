/*
  题目描述：
    给你一个整数数组 arr 和一个整数 k 。
    现需要从数组中恰好移除 k 个元素，请找出移除后数组中不同整数的最少数目。
*/

class Solution {
private:
    int heap_size=0;        // 堆长度
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        HEAPSORT(arr);      // 堆排序,升序
        int rest=1;         // 不同整数的个数
        vector<int> sums;   // 记录相同整数的个数
        sums.push_back(0);
        for(int i=0,temp=arr[0],index=0;i<arr.size();i++){  // 遍历排序后的数组 arr
                                                            // 记录每个相同整数的个数
            if(temp!=arr[i]){       // 一种数字结束
                temp=arr[i];        // 当前数 temp 改为新的当前整数
                sums.push_back(1);  // sums 数组压入新数初始个数1
                index++;            // sums 数组下标加1
                rest++;             // 不同数字个数加1
            }else{
                sums[index]++;      // 当前数字个数加1
            }
        }
        HEAPSORT(sums);     // 堆排序,升序
        int index=0;
        while(1){
            k-=sums[index++];   // 移除个数减去 index 下标数的个数
            if(k>0)             // k 还有剩下
                rest--;
            else if(k==0){      // k 刚好完全减掉
                rest--;
                break;
            }else               // k 小于 0,当前 index 下标代表整数不能完全移除
                break;
        }
        return rest;
    }

    int PARENT(int i)
    {// 返回双亲结点下标
        return i/2;
    }

    int LEFT(int i)
    {// 返回左孩子下标
        return 2*i;
    }

    int RIGHT(int i)
    {// 返回右孩子下标
        return 2*i+1;
    }

    void MAX_HEAPIFY(vector<int>& A,int i)
    {// 维护最大堆性质
        int l=LEFT(i+1)-1;  // 下标 i 的左孩子下标
        int r=RIGHT(i+1)-1; // 下标 i 的右孩子下标
        int largest=i;      // 三者中最大值的下标

        if(l<heap_size&&A[l]>A[i])      // 寻找三者最大值的下标并保存在 largest
            largest=l;
        if(r<heap_size&&A[r]>A[largest])
            largest=r;

        if(largest!=i){     // 当最大者不是双亲结点 i
            int temp=A[i];  // 交换 i 和最大值结点的值
            A[i]=A[largest];
            A[largest]=temp;
            MAX_HEAPIFY(A,largest);     // 递归的调用前最大者下标
        }
    }

    void BUILD_MAX_HEAP(vector<int>& A)
    {// 建立最大堆
        heap_size=A.size();
        for(int i=A.size()/2-1;i>=0;i--)    // 从第一个非叶子结点开始向上遍历二叉树
            MAX_HEAPIFY(A,i);               // 挨个维护最大堆性质
    }

    void HEAPSORT(vector<int>& A)
    {// 堆排序
        BUILD_MAX_HEAP(A);                  // 创建最大堆
        for(int i=A.size()-1;i>0;i--){      // 倒叙遍历数组,在最大堆情况下数组首元素为最大值
            int temp=A[0];                  // 交换数组首元素和尾元素的值
            A[0]=A[i];
            A[i]=temp;
            heap_size--;                    // 堆长度减1
            MAX_HEAPIFY(A,0);               // 递归调用堆排序
        }
    }
};
