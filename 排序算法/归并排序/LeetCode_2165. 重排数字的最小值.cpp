/*
  题目描述：
	给你一个整数 num 。重排 num 中的各位数字，使其值 最小化 且不含 任何 前导零。
	返回不含前导零且值最小的重排数字。
	注意，重排各位数字后，num 的符号不会改变。
*/

class Solution {
public:
	long long smallestNumber(long long num) {
		if (num > -10 && num < 10) return num;     // 当 num 只有一位时,无需重排
		vector<int>decompose_array;         // 存放拆解 num 各位的数组
		int symbol = Decompose(decompose_array, num);      // 拆解 num ,并返回 num 正负 
		MEGRE_SORT(decompose_array, 0, decompose_array.size() - 1);     // 归并排序
		return Conformity(decompose_array, symbol);      // 返回合并后的结果
	}

	int Decompose(vector<int>& array, long long num)
	{
		int symbol = 0;                   // num 正负
		if (num > 0)  symbol = 1;
		else { symbol = -1; num *= -1; }
		while (num > 0) {
			array.push_back(num % 10);    // 拆解 num
			num /= 10;
		}
		return symbol;
	}

	void MERGE(vector<int>& array, int p, int q, int r)
	{
		int n1 = q - p + 1;       // 数组前半部分长度
		int n2 = r - q;         // 数组后半部分长度

		vector<int>L;       // 将前半部分放入数组 L
		for (int i = 0; i < n1; i++)
			L.push_back(array[p + i]);

		vector<int>R;       // 将后半部分放入数组 R
		for (int i = 0; i < n2; i++)
			R.push_back(array[q + i + 1]);

		L.push_back(10);    // 作为哨兵位,单个位数值不超过9
		R.push_back(10);

		for (int k = p, i = 0, j = 0; k <= r; k++)
			if (L[i] < R[j]) {  // 比较两数组按升序存入 array
				array[k] = L[i];
				i++;
			}
			else {
				array[k] = R[j];
				j++;
			}
	}

	void MEGRE_SORT(vector<int>& array, int p, int r)
	{
		if (p < r) {    // 递归满足条件
			int q = (p + r) / 2;              // 平均拆分数组成两份
			MEGRE_SORT(array, p, q);      // 递归排序前部分 
			MEGRE_SORT(array, q + 1, r);    // 递归排序后部分
			MERGE(array, p, q, r);         // 整合两分已排序好的数组
		}
	}

	long long Conformity(vector<int>& array, int symbol)
	{
		long long result = 0;
		if (symbol == 1) { // num 为正
			int index = 0;
			while (array[index] == 0)  // 按升序排序后存在前导零
				index++;
			if (array[0] == 0) {        // 当存在前导零,将第一个不是前导零的位放到数组首位
				array[0] = array[index];
				array[index] = 0;
			}
			result = array[0];        // 合并数组各位保存在 result 中
			for (int i = 1; i < array.size(); i++) {
				result *= 10;
				result += array[i];
			}
		}
		else {  // num 为负
			result = array[array.size() - 1];      // 负数时求最小应各位降序
			for (int i = array.size() - 2; i >= 0; i--) {// 从后向前合并结果
				result *= 10;
				result += array[i];
			}
			result *= -1;
		}
		return result;              // 返回结果
	}
};
