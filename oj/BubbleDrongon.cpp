#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>
using namespace std;

double final = 0;
typedef struct TNode *BinTree;
struct TNode
{
    unsigned short v;
    BinTree l;
    BinTree r;
    TNode() : v(0), l(NULL), r(NULL) {};
};

BinTree Build(unsigned short *pre, unsigned short *v, unsigned short *in, unsigned short n)
{
    stack<BinTree> st;
    stack<unsigned short> num;
    unsigned short i;
    BinTree root = new TNode;
    root->v = v[0];
    st.push(root);
    num.push(pre[0]);
    unsigned short index = 0;
    for (i = 1; i < n; ++i)
    {
        BinTree node = st.top();
        if (num.top() != in[index])
        {
            node->l = new TNode;
            node->l->v = v[i];
            st.push(node->l);
            num.push(pre[i]);
        }
        else
        {
            while (!st.empty() && num.top() == in[index])
            {
                node = st.top();
                st.pop();
                num.pop();
                ++index;
            }
            node->r = new TNode;
            node->r->v = v[i];
            st.push(node->r);
            num.push(pre[i]);
        }
    }
    return root;
}

unsigned short NodeCount(BinTree tree)
{
    if (!tree)
        return 0;
    int count = 1;
    std::queue<BinTree> q;
    q.push(tree);
    while (!q.empty())
    {
        BinTree node = q.front();
        q.pop();
        if (node->l)
        {
            q.push(node->l);
            count++;
        }
        if (node->r)
        {
            q.push(node->r);
            count++;
        }
    }
    return count;
}

unsigned int TotalWeight(BinTree tree)
{
    if (!tree)
        return 0;
    unsigned int sum = tree->v;
    queue<BinTree> q;
    q.push(tree);
    while (!q.empty())
    {
        BinTree node = q.front();
        q.pop();
        if (node->l)
        {
            q.push(node->l);
            sum += node->l->v;
        }
        if (node->r)
        {
            q.push(node->r);
            sum += node->r->v;
        }
    }
    return sum;
}

void FindMax(BinTree tree, int n)
{
    double current;
    if (!tree)
        return;
    queue<BinTree> q;
    q.push(tree);
    current = TotalWeight(tree) * (1 - (double)NodeCount(tree)/n);
    final = current > final ? current : final;
    while (!q.empty())
    {
        BinTree node = q.front();
        q.pop();
        if (node->l)
        {
            q.push(node->l);
            current = TotalWeight(node->l) * (1 - (double)NodeCount(node->l)/n);
            final = current > final ? current : final;
        }
        if (node->r)
        {
            q.push(node->r);
            current = TotalWeight(node->r) * (1 - (double)NodeCount(node->r)/n);
            final = current > final ? current : final;
        }
    }
    return;
}

int main()
{
    unsigned short N, *a, *b, *v, i;
    scanf("%hu", &N);
    a = new unsigned short[N];
    b = new unsigned short[N];
    v = new unsigned short[N];
    for (i = 0; i < N; i++)
        scanf("%hu", a + i);
    for (i = 0; i < N; i++)
        scanf("%hu", v + i);
    for (i = 0; i < N; i++)
        scanf("%hu", b + i);
    BinTree root = Build(a, v, b, N);
    FindMax(root, N);
    printf("%.2lf\n", final);
    //printf("%d\n", TotalWeight(root));
}