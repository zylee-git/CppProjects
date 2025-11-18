#include <stdio.h>
#include <complex>
#include <math.h>
using namespace std;

#define pi M_PI
#define MaxVoltageSourceCount 10 // 电压源最大个数
typedef complex<double> dc;

int main()
{
    int num_nodes, num_components, target_node; // 结点数，元件数，待求电压的结点
    double freq;                                // 频率
    scanf("%d%d%lf%d", &num_nodes, &num_components, &freq, &target_node);
    int n = num_nodes;                                      // 改进的结点电压法的矩阵行数（列数）
    dc **mat = new dc *[num_nodes + MaxVoltageSourceCount]; // 矩阵，预定义为最大的大小
    dc *r = new dc[num_nodes + MaxVoltageSourceCount];      // 右侧列向量，预定义为最大的大小
    for (int i = 0; i < num_nodes + MaxVoltageSourceCount; i++)
        mat[i] = new dc[num_nodes + MaxVoltageSourceCount];
    for (int i = 0; i < num_nodes + MaxVoltageSourceCount; i++)
        for (int j = 0; j < num_nodes + MaxVoltageSourceCount; j++)
            mat[i][j] = 0;
    for (int i = 0; i < num_nodes + MaxVoltageSourceCount; i++)
        r[i] = 0; // 初始化矩阵和右侧列向量为0

    for (int i = 0; i < num_components; i++)
    {
        char type;
        int node1, node2;
        double value;
        scanf(" %c%d%d%lf", &type, &node1, &node2, &value); // 元件类型，正结点，负结点，元件数值
        switch (type)
        {
        case 'R': // 电阻
            if (node1)
                mat[node1 - 1][node1 - 1] += 1 / value;
            if (node2)
                mat[node2 - 1][node2 - 1] += 1 / value;
            if (node1 && node2)
                mat[node1 - 1][node2 - 1] += mat[node2 - 1][node1 - 1] = -1 / value;
            break;
        case 'V': // 电压源
            n++;
            r[n - 1] = value;
            if (node1)
            {
                mat[node1 - 1][n - 1] = 1;
                mat[n - 1][node1 - 1] = 1;
            }
            if (node2)
            {
                mat[node2 - 1][n - 1] = -1;
                mat[n - 1][node2 - 1] = -1;
            }
            break;
        case 'I': // 电流源
            if (node1)
                r[node1 - 1] += value;
            if (node2)
                r[node2 - 1] -= value;
            break;
        case 'C': // 电容
            if (node1)
                mat[node1 - 1][node1 - 1] += dc(0, 2 * pi * freq * value);
            if (node2)
                mat[node2 - 1][node2 - 1] += dc(0, 2 * pi * freq * value);
            if (node1 && node2)
                mat[node1 - 1][node2 - 1] = mat[node2 - 1][node1 - 1] += -dc(0, 2 * pi * freq * value);
            break;
        case 'L': // 电感
            if (node1)
                mat[node1 - 1][node1 - 1] -= dc(0, 1 / (2 * pi * freq * value));
            if (node2)
                mat[node2 - 1][node2 - 1] -= dc(0, 1 / (2 * pi * freq * value));
            if (node1 && node2)
                mat[node1 - 1][node2 - 1] = mat[node2 - 1][node1 - 1] += dc(0, 1 / (2 * pi * freq * value));
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        // 寻找主元
        int mainrow = i;
        for (int j = i + 1; j < n; j++)
            if (abs(mat[j][i]) > abs(mat[mainrow][i]))
                mainrow = j;
        // 交换第i行和第mainrow行
        if (mainrow != i)
        {
            for (int j = 0; j < n; j++)
                swap(mat[i][j], mat[mainrow][j]);
            swap(r[i], r[mainrow]);
        }
        if (mat[i][i] == dc(0))
            mat[i][i] = 1;
        for (int j = i + 1; j < n; j++)
        {
            dc c = mat[j][i] / mat[i][i];
            for (int k = i; k < n; k++)
                mat[j][k] -= c * mat[i][k];
            r[j] -= c * r[i];
        }
    }
    dc l[n];
    for (int i = n - 1; i >= 0; i--)
    {
        l[i] = r[i];
        for (int j = i + 1; j < n; j++)
            l[i] -= mat[i][j] * l[j];
        l[i] /= mat[i][i];
    }
    printf("%.2lf", abs(l[target_node - 1]));
}