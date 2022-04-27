/*
  题目描述：
    给定数组 people 。people[i]表示第 i 个人的体重 ，船的数量不限，每艘船可以承载的最大重量为 limit。
    每艘船最多可同时载两人，但条件是这些人的重量之和最多为 limit。
    返回 承载所有人所需的最小船数 。
*/

class Solution {
private:
    int heap_size=0;
public:
    int numRescueBoats(vector<int>& people, int limit) {
        HEAPSORT(people);      // 堆排序,升序
        int sums=0;            // 所需小船数量
        int head=0;            // 数组头指针
        int tail=people.size()-1;   // 数组尾指针

        while(head<tail){   // 双指针双向奔赴
            if(people[head]+people[tail]<=limit){   // 将最重的和最轻的放在一艘船
                                                    // 的情况才需要最少数量的船
                head++;     // 头指针后移
                tail--;     // 尾指针前移
                sums++;     // 船数加1
            }else{
                tail--;     // 当不能和剩下最轻的坐一艘船
                            // 则当前最胖的无人可和他拼船
                sums++;     // 船数加1
            }
        }

        if(head==tail)  sums++;     // 当头指针和尾指针相同,表明还剩下一人

        return sums;        // 返回所需最小船数
    }  

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
