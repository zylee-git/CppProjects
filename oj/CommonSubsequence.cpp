#include <stdio.h>
#include <vector>
#include <cstring>
#include <string>
using namespace std;

int CommonSubsequence(int n, char **str)
{
    int *len = new int[n];
    for (int i = 0; i < n; i++)
        len[i] = strlen(str[i]);
    if (n < 2)
        return 0;
    else if (n == 2)
    {
        vector<int> pre(len[0] + 1, 0), cur(len[0] + 1, 0);
        for (int i = 1; i <= len[1]; i++)
        {
            for (int j = 1; j <= len[0]; j++)
            {
                if (str[0][j - 1] == str[1][i - 1])
                    cur[j] = pre[j - 1] + 1;
                else
                    cur[j] = max(cur[j - 1], pre[j]);
            }
            pre = cur;
        }
        return cur[len[0]];
    }
    else if (n == 3)
    {
        vector<vector<vector<int>>> dp(len[0] + 1, vector<vector<int>>(len[1] + 1, vector<int>(len[2] + 1, 0)));
        for (int i = 1; i <= len[0]; i++)
        {
            for (int j = 1; j <= len[1]; j++)
            {
                for (int k = 1; k <= len[2]; k++)
                {
                    if (str[0][i - 1] == str[1][j - 1] && str[0][i - 1] == str[2][k - 1])
                        dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                    else
                    {
                        int m1 = max(max(dp[i - 1][j][k], dp[i][j - 1][k]), dp[i][j][k - 1]);
                        int m2 = max(max(dp[i - 1][j - 1][k], dp[i][j - 1][k - 1]), dp[i - 1][j][k - 1]);
                        dp[i][j][k] = max(m1, m2);
                    }
                }
            }
        }
        return dp[len[0]][len[1]][len[2]];
    }
    else if (n == 4)
    {
        vector<vector<vector<vector<int>>>> dp(len[0] + 1, vector<vector<vector<int>>>(len[1] + 1, vector<vector<int>>(len[2] + 1, vector<int>(len[3] + 1, 0))));
        for (int i = 1; i <= len[0]; i++)
        {
            for (int j = 1; j <= len[1]; j++)
            {
                for (int k = 1; k <= len[2]; k++)
                {
                    for (int l = 1; l <= len[3]; l++)
                    {
                        if (str[0][i - 1] == str[1][j - 1] && str[0][i - 1] == str[2][k - 1] && str[0][i - 1] == str[3][l - 1])
                            dp[i][j][k][l] = dp[i - 1][j - 1][k - 1][l - 1] + 1;
                        else
                        {
                            int m1 = max(max(dp[i - 1][j][k][l], dp[i][j - 1][k][l]), max(dp[i][j][k - 1][l], dp[i][j][k][l - 1]));
                            int m2 = max(max(dp[i - 1][j - 1][k][l], dp[i][j - 1][k - 1][l]), dp[i][j][k - 1][l - 1]);
                            int m3 = max(max(dp[i - 1][j][k - 1][l], dp[i][j - 1][k][l - 1]), dp[i - 1][j][k][l - 1]);
                            int m4 = max(max(dp[i - 1][j - 1][k - 1][l], dp[i][j - 1][k - 1][l - 1]), max(dp[i - 1][j][k - 1][l - 1], dp[i - 1][j - 1][k][l - 1]));
                            dp[i][j][k][l] = max(max(m1, m2), max(m3, m4));
                        }
                    }
                }
            }
        }
        return dp[len[0]][len[1]][len[2]][len[3]];
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int *length = new int[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &length[i]);
    char **str = new char *[n];
    for (int i = 0; i < n; i++)
    {
        str[i] = new char[length[i] + 1];
        scanf("%s", str[i]);
    }
    int result = CommonSubsequence(n, str);
    printf("%d\n", result);
}