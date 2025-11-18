#include <stdio.h>
#include <algorithm>
using namespace std;

int main()
{
    int k, n;
    scanf("%d%d",&k,&n);
    int *garden = new int[n * n];
    for (int i = 0; i < n * n; i++)
    {
        scanf("%d", garden + i);
    }
    sort(garden, garden + n * n);
    printf("%d\n", *(garden + k-1));
}