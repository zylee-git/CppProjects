#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;

void normalSolve(int, int, vector<vector<double>> &, vector<double> &, vector<double> &);

double f(double x)
{
    return x * x;
}

int main()
{
    int num_basis, num_points;
    double c;
    scanf("%d%d%lf", &num_basis, &num_points, &c);

    // double **mat = new double *[num_points];
    // double *a = new double[num_basis];
    // double *b = new double[num_points];
    // double **basic_points = new double *[num_basis];
    vector<vector<double>> mat(num_points, vector<double>(num_basis));
    vector<vector<double>> basic_points(num_points, vector<double>(2));
    vector<double> a(num_basis);
    vector<double> b(num_points);

    for (int i = 0; i < num_basis; i++)
    {
        scanf("%lf%lf", &basic_points[i][0], &basic_points[i][1]);
    }
    for (int i = 0; i < num_points; i++)
    {
        double x, y;
        scanf("%lf%lf%lf", &x, &y, &b[i]);
        for (int j = 0; j < num_basis; j++)
            mat[i][j] = sqrt(f(x - basic_points[j][0]) + f(y - basic_points[j][1]) + f(c));
    }
    normalSolve(num_points, num_basis, mat, a, b);
    for (int i = 0; i < num_basis; i++)
        printf("%lf ", a[i]);
}

void normalSolve(int m, int n, vector<vector<double>> &A, vector<double> &x, vector<double> &b)
{
    vector<vector<double>> ATA(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < m; k++)
                ATA[i][j] += A[k][i] * A[k][j];
    vector<double> ATb(n, 0);
    for (int i = 0; i < n; i++)
        for (int k = 0; k < m; k++)
            ATb[i] += A[k][i] * b[k];
    for (int i = 0; i < n; i++)
    {
        int mainrow = i;
        for (int j = i + 1; j < n; j++)
            if (abs(ATA[j][i]) > abs(ATA[mainrow][i]))
                mainrow = j;
        if (mainrow != i)
        {
            swap(ATA[i], ATA[mainrow]);
            swap(ATb[i], ATb[mainrow]);
        }
        for (int j = i + 1; j < n; j++)
        {
            double tmp = ATA[j][i] / ATA[i][i];
            for (int k = i; k < n; k++)
                ATA[j][k] -= tmp * ATA[i][k];
            ATb[j] -= tmp * ATb[i];
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = ATb[i];
        for (int j = i + 1; j < n; j++)
            x[i] -= ATA[i][j] * x[j];
        x[i] /= ATA[i][i];
    }
}
