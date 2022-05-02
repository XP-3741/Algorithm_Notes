/*
  题目描述：
    给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m-1] 。
    请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？
    例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
    
  提示：
    2 <= n <= 58
*/

/*
  总结：
    第一次自己独立完成动态规划类题目；
    回想起《算法导论》寻找两字符串最长公共子串题目
    对于长度为 n 的绳子切成多少段即
    在 [1..n-1] 每个结点切还是不切的问题，于《算法导论》题目思想一致；
    并且回想起《算法导论》的解题思路：
    假设已近知道一点，这个点被切掉，那最优解即为切割点两边绳子的最优解乘积
    的这种假设思想，从而求得递推式。
*/

class Solution {
public:
    int cuttingRope(int n) {
        vector<int>memary(n);       // 备忘录,用于保存 [1..n-1] 绳子长度切割最大乘积
                                    // [1..n-1] 可以不进行切割
        memary[1] = 1;              // 初始绳子长度为 1 的最大切割乘积为 1
        for(int i = 2; i < n; i++){ // 遍历 [2..n-1] 从底向上求最优解
            int max_cur = i;        // 默认最长为当前绳长
            for(int j = 1; j < i; j++)  
                    // 长度为 i 的绳子最优解 = 长度为 j 的绳子最优解 * 长度为 (i - j) 的绳子最优解
                    // 0 <= j < i
                max_cur = max(max_cur, memary[j]*memary[i-j]);  // 求最大值
            memary[i] =  max_cur;   // 赋值 i 最优解
        }
        
        int max_n = 0;              // 绳长为 n 的最优解
        for(int i = 1; i < n; i++)  // 按照上述递归思想寻找
                                    // 不过此时最优解可能集合不包括本身,即 n
                                    // 因为 m > 1
            max_n = max(max_n, memary[i]*memary[n-i]);

        return max_n;
    }
};

/* 评论区方法 */
/*
  数学知识的重要
  恐怖如斯
*/
class Solution {
public:
    int cuttingRope(int n) {
        if(n<=3)        // n = 2: 1
                        // n = 3: 2  
            return n-1;

        int sum=1;
        while (n>4){
            /*
             绳子段切分的越多，乘积越大，且 3 做因数比 2 更优
             不断剪去长度3 并用 sum 累乘
             把绳子切为多个长度为 3 的片段，则留下的最后一段绳子的长度可能为 0,1,2 三种情况：
             1. n=n-3==2 
                n长度剩下2，因 n > 4 跳出循环，return 乘积为sum*2
             2. n=n-3==3 
                长度刚好可以被剪完，因 n > 4 跳出循环，return 乘积为sum*3
             3.  n=n-3==4
                再剪一次的话，长度剩下1，则最后一段绳子长度为 1
                需要把最后的 3 和 1 替换为 2 和 2，因为 2 * 2 > 3 * 1
                因 n > 4 跳出循环，return 乘积 sum*4 即可
            */
            sum*=3;
            n-=3;
        }
        return sum*n;
    }
};

