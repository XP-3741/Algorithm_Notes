/*
  你是一个专业的小偷，计划偷窃沿街的房屋。
  每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
  给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
  
  提示：
    1 <= nums.length <= 100
    0 <= nums[i] <= 400
*/

/*
  总结：
    在备忘录中，不需要将i从0到nums.size()-1的最优解全部记录下来
    只需要当前元素的前驱和前前驱的最优解即可
    以及无需判断前驱是否被偷
    因为当前元素的最优解始终是在 前驱最优解 和 前前驱最优解+当前遍历元素金额 的较大值
    况且，每个元素最优解和挨着遍历是否偷取是两回事
    所以不需要进行前驱是否被偷的判断
*/

class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> Subarrays_max;          // 备忘录
                                            // Subarrays_max[i]记录偷取nums[0..i]的最高金额
        Subarrays_max.push_back(nums[0]);   // 当 i = 0, 只有一家, 只能偷它
        bool front_stoled=true;             // 当前元素的前驱是否被偷的标志
                                            // true:被偷    false:未被偷
        if(nums.size()>=2)                  // 当nums数组长度超过2,判断i=1时的Subarrays_max[i]
            if(nums[1]>nums[0])             // 第 1 家超过第 0 家,压入num[1]
                Subarrays_max.push_back(nums[1]);
            else{                           // 第 0 家超过第 1 家,压入num[0]
                Subarrays_max.push_back(nums[0]);
                front_stoled=false;         // 标记前驱未被偷,即 2 的前驱
            }

        for(int i=2;i<nums.size();i++){     // 从第 2 家开始遍历数组
            if(front_stoled)    // 当前 i 的前驱被偷
                if(nums[i]+Subarrays_max[i-2]>Subarrays_max[i-1])
                                // 当前元素 nums[i] 加上上上个最高金额是否超过上个最高金额
                    Subarrays_max.push_back(nums[i]+Subarrays_max[i-2]);
                else{
                    Subarrays_max.push_back(Subarrays_max[i-1]);
                    front_stoled=false;     // 标记前驱未被偷
                }
            else{               // 当前 i 的前驱未被偷
                if(nums[i]+Subarrays_max[i-2]<Subarrays_max[i-1])
                    Subarrays_max.push_back(Subarrays_max[i-1]);
                else{
                    Subarrays_max.push_back(nums[i]+Subarrays_max[i-2]);
                    front_stoled=true;
                }
            }
        }
        return Subarrays_max[Subarrays_max.size()-1];   // 返回尾元素的最高金额
    }
};

/*
  评论区方法
*/

class Solution {
public:
    int rob(vector<int>& nums) {
    int prev = 0;
    int curr = 0;

    // 每次循环，计算“偷到当前房子为止的最大金额”
    for (int i : nums) {
        // 循环开始时，curr 表示 dp[k-1]，prev 表示 dp[k-2]
        // dp[k] = max{ dp[k-1], dp[k-2] + i }
        int temp = max(curr, prev + i);
        prev = curr;
        curr = temp;
        // 循环结束时，curr 表示 dp[k]，prev 表示 dp[k-1]
    }

    return curr;
}
};
