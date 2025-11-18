#include <stdio.h>

typedef struct
{
    int five;
    int ten;
    int twenty;
} VouchersCount;

VouchersCount vouchersCount = {0, 0, 0};

int main()
{
    int n, i, money, sellCount = 0;
    int able = 1;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &money);
        if (money == 5)
        {
            vouchersCount.five++;
            sellCount++;
        }
        else if (money == 10)
        {
            if (vouchersCount.five > 0)
            {
                vouchersCount.five--;
                vouchersCount.ten++;
                sellCount++;
            }
            else
            {
                able = 0;
                break;
            }
        }
        else if (money == 20)
        {
            if (vouchersCount.five == 0)
            {
                able = 0;
                break;
            }
            else if (vouchersCount.ten > 0)
            {
                vouchersCount.five--;
                vouchersCount.ten--;
                vouchersCount.twenty++;
                sellCount++;
            }
            else if (vouchersCount.five > 2)
            {
                vouchersCount.five -= 3;
                vouchersCount.twenty++;
                sellCount++;
            }
            else
            {
                able = 0;
                break;
            }
        }
    }
    if (able)
    {
        printf("1 %d\n", sellCount * 5);
    }
    else
    {
        printf("0 %d\n", sellCount * 5);
    }
}