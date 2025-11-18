#include <stdio.h>
#include <stack>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main()
{
    char *str = (char *)malloc(201);
    char c, op;
    int i, n1, n2;
    bool tmp = false, tmp2 = false;
    stack<int> nums;
    stack<char> ops;
    scanf("%s", str);
    while ((c = str[0]) != '\0')
    {
        if (c == '(') // 进栈
        {
            tmp = false;
            tmp2 = true;
            ops.push(c);
            str++;
            continue;
        }
        else if (c == ')')
        {
            tmp = false;
            tmp2 = false;
            while (ops.top() != '(')
            {
                op = ops.top();
                ops.pop();
                n2 = nums.top();
                nums.pop();
                n1 = nums.top();
                nums.pop();
                switch (op)
                {
                case '+':
                    nums.push(n1 + n2);
                    break;
                case '-':
                    nums.push(n1 - n2);
                    break;
                case '*':
                    nums.push(n1 * n2);
                    break;
                case '/':
                    if (n2 == 0)
                    {
                        printf("Error\n");
                        exit(1);
                    }
                    nums.push(n1 / n2);
                    break;
                case '^':
                    if (n1 == 0 && n2 < 0)
                    {
                        printf("Error\n");
                        exit(1);
                    }
                    nums.push(pow(n1, n2));
                    break;
                }
            }
            ops.pop(); // 出栈右括号
            str++;
            continue;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        {
            if (c == '-' && nums.empty() && ops.empty())
            {
                nums.push(0);
                ops.push(c);
            }
            else if (c == '-' && tmp2)
            {
                ops.push(c);
                nums.push(0);
            }
            else if (ops.empty())
            {
                ops.push(c);
            }
            else
            {
                while (true)
                {
                    if (ops.empty())
                    {
                        ops.push(c);
                        break;
                    }
                    else if (ops.top() == '(')
                    {
                        ops.push(c);
                        break;
                    }
                    else if ((ops.top() == '+' || ops.top() == '-') && c != '+' && c != '-')
                    {
                        ops.push(c);
                        break;
                    }
                    else if ((ops.top() == '*' || ops.top() == '/' || ops.top() == '^') && c == '^')
                    {
                        ops.push(c);
                        break;
                    }
                    else
                    {
                        op = ops.top();
                        ops.pop();
                        n2 = nums.top();
                        nums.pop();
                        n1 = nums.top();
                        nums.pop();
                        switch (op)
                        {
                        case '+':
                            nums.push(n1 + n2);
                            break;
                        case '-':
                            nums.push(n1 - n2);
                            break;
                        case '*':
                            nums.push(n1 * n2);
                            break;
                        case '/':
                            if (n2 == 0)
                            {
                                printf("Error\n");
                                exit(1);
                            }
                            nums.push(n1 / n2);
                            break;
                        case '^':
                            if (n1 == 0 && n2 < 0)
                            {
                                printf("Error\n");
                                exit(1);
                            }
                            nums.push(pow(n1, n2));
                            break;
                        }
                    }
                }
            }
            tmp = false;
            tmp2 = false;
            str++;
            continue;
        }
        else if (c <= '9' && c >= '0')
        {
            tmp2 = false;
            if (tmp)
            {
                i = nums.top();
                nums.pop();
                nums.push(i * 10 + (c - '0'));
            }
            else
            {
                nums.push(c - '0');
                tmp = true;
            }
            str++;
            continue;
        }
        else
        {
            printf("Error\n");
            exit(1);
        }
    }
    while (!ops.empty())
    {
        op = ops.top();
        ops.pop();
        n2 = nums.top();
        nums.pop();
        n1 = nums.top();
        nums.pop();
        switch (op)
        {
        case '+':
            nums.push(n1 + n2);
            break;
        case '-':
            nums.push(n1 - n2);
            break;
        case '*':
            nums.push(n1 * n2);
            break;
        case '/':
            if (n2 == 0)
            {
                printf("Error\n");
                exit(1);
            }
            nums.push(n1 / n2);
            break;
        case '^':
            if (n1 == 0 && n2 < 0)
            {
                printf("Error\n");
                exit(1);
            }
            nums.push(pow(n1, n2));
            break;
        }
    }
    printf("%d\n", nums.top());
}