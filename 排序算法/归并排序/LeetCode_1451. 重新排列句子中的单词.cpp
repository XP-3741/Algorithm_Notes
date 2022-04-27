/*
  题目描述：
    「句子」是一个用空格分隔单词的字符串。给你一个满足下述格式的句子 text :
    句子的首字母大写
    text 中的每个单词都用单个空格分隔。
    请你重新排列 text 中的单词，使所有单词按其长度的升序排列。如果两个单词的长度相同，则保留其在原句子中的相对顺序。
    请同样按上述格式返回新的句子。
*/

class Solution {
public:
    string arrangeWords(string text) {
        text[0]+='a'-'A';       // 将字符串首字母改成小写
        vector<vector<int>> SortString;     // 存放每个单词的首字母下标和长度
        int Index_string=0;     // 单词首字母下标
        int Length_word=0;      // 单词长度
        for(int i=0;i<text.length();i++){
            if(text[i]==' '|| i + 1 == text.length()){  // 当遇到空格或者字符串 text 结尾,表明一个单一结束
                SortString.push_back({Length_word,Index_string});   // 将此单词长度和首字母下标压入数组
                Index_string=i+1;       // 下标加1
                Length_word=0;          // 单词长度重置为0
                continue;
            }
            Length_word++;              // 未到单词结尾,单词长度累加
        }
        SortString[SortString.size()-1][0]++;
        MERGE_SORT(SortString,0,SortString.size()-1);       // 按照每个单词长度归并排序
        string result;                  // 结果字符串
        for(int i=SortString.size()-1;i>=0;i--){            // 遍历数组将结果保存至 result
            for(int j=0;j<SortString[i][0];j++)
                result+=text[SortString[i][1]+j];
            if(i!=0) result+=' ';
        }
        result[0]-='a'-'A';             // 首字母大写
        return result;
    }

    // 归并排序详解见 "LeetCode_2165. 重排数字的最小值.cpp"
    void MERGE(vector<vector<int>>& A,int p,int q,int r)
    {
        int n1=q-p+1;
        int n2=r-q;

        vector<vector<int>>L;
        for(int i=0;i<n1;i++)
            L.push_back({A[p+i][0],A[p+i][1]});
        L.push_back({-1,-1});

        vector<vector<int>>R;
        for(int i=1;i<=n2;i++)
            R.push_back({A[q+i][0],A[q+i][1]});
        R.push_back({-1,-1});

        int L_index=0;
        int R_index=0;
        
        for(int i=p;i<=r;i++){
            if(L[L_index]>R[R_index]){
                A[i][0]=L[L_index][0];
                A[i][1]=L[L_index][1];
                L_index++;
            }else{
                A[i][0]=R[R_index][0];
                A[i][1]=R[R_index][1];
                R_index++;
            }
        }
    }

    void MERGE_SORT(vector<vector<int>>& A,int p,int r)
    {
        if(p<r){
            int q=(p+r)/2;
            MERGE_SORT(A,p,q);
            MERGE_SORT(A,q+1,r);
            MERGE(A,p,q,r);
        }
    }
};
