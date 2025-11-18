#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;
#define PI 3.14
typedef complex<double> Complex;
struct Component
{
    char type;        // 'R', 'C', 'L', 'V', 'I'
    int node1, node2; // 节点编号
    double value;     // 元件值
};
Complex impedance(char type, double value, double frequency)
{
    if (type == 'C')
    {
        return Complex(0, -1.0 / (2 * PI * frequency * value));
    }
    else if (type == 'L')
    {
        return Complex(0, 2 * PI * frequency * value);
    }
    else
    {
        return Complex(1.0 / value, 0);
    }
}
void add_to_matrix(vector<vector<Complex>> &A, int row, int col, Complex value)
{
    if (row >= 0 && col >= 0)
    {
        A[row][col] += value;
    }
}
int main()
{
    int numNodes = 3;          // 节点数
    int numVoltageSources = 1; // 电压源数
    double frequency = 60.0;   // 频率
    vector<Component> components = {
        {'R', 1, 2, 10.0},
        {'C', 2, 3, 0.001},
        {'L', 1, 3, 0.01},
        {'V', 1, 0, 10.0}, // 假设节点0是参考节点（GND）
        {'I', 2, 3, 1.0}   // 电流源
    };
    int dim = numNodes + numVoltageSources;
    vector<vector<Complex>> A(dim, vector<Complex>(dim, 0));
    vector<Complex> b(dim, 0);
    // 构建MNA矩阵
    for (const auto &comp : components)
    {
        Complex Y;
        if (comp.type == 'R' || comp.type == 'C' || comp.type == 'L')
        {
            Y = 1.0 / impedance(comp.type, comp.value, frequency);
            add_to_matrix(A, comp.node1 - 1, comp.node1 - 1, Y);
            add_to_matrix(A, comp.node2 - 1, comp.node2 - 1, Y);
            if (comp.node1 != 0 && comp.node2 != 0)
            {
                add_to_matrix(A, comp.node1 - 1, comp.node2 - 1, -Y);
                add_to_matrix(A, comp.node2 - 1, comp.node1 - 1, -Y);
            }
        }
        else if (comp.type == 'V')
        {
            int n = numNodes + comp.node1 - 1;
            add_to_matrix(A, comp.node1 - 1, n, 1);
            add_to_matrix(A, comp.node2 - 1, n, -1);
            add_to_matrix(A, n, comp.node1 - 1, 1);
            add_to_matrix(A, n, comp.node2 - 1, -1);
            b[n] = comp.value;
        }
        else if (comp.type == 'I')
        {
            if (comp.node1 != 0)
                b[comp.node1 - 1] -= comp.value;
            if (comp.node2 != 0)
                b[comp.node2 - 1] += comp.value;
        }
    }
    // Gaussian elimination (这里只展示了一个非常基础的实现)
    for (int i = 0; i < dim; ++i)
    {
        // Find pivot
        int maxRow = i;
        for (int k = i + 1; k < dim; ++k)
        {
            if (abs(A[k][i]) > abs(A[maxRow][i]))
            {
                maxRow = k;
            }
        }
        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);
        // Eliminate column
        for (int k = i + 1; k < dim; ++k)
        {
            Complex c = A[k][i] / A[i][i];
            for (int j = i; j < dim; ++j)
            {
                A[k][j] -= c * A[i][j];
            }
            b[k] -= c * b[i];
        }
    }
    // Back substitution
    vector<Complex> x(dim);
    for (int i = dim - 1; i >= 0; --i)
    {
        x[i] = b[i];
        for (int k = i + 1; k < dim; ++k)
        {
            x[i] -= A[i][k] * x[k];
        }
        x[i] /= A[i][i];
    }

    // 输出节点电压
    for (int i = 0; i < numNodes; ++i)
    {
        cout << "Node " << i + 1 << " voltage: " << x[i] << endl;
    }

    // 输出支路电流（可选）
    for (const auto &comp : components)
    {
        if (comp.type == 'R' || comp.type == 'C' || comp.type == 'L')
        {
            Complex voltageDrop = x[comp.node1 - 1] - x[comp.node2 - 1];
            Complex current = voltageDrop / impedance(comp.type, comp.value, frequency);
            cout << "Current through " << comp.type << " " << comp.value << ": " << current << endl;
        }
    }

    return 0;
}
