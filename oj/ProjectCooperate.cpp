#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct eg
{
    int v, w;
    int weight;
} edge;

int Find(vector<int> &parent, int i)
{
    while (i != parent[i])
        i = parent[i];
    return i;
}

bool CompareEdge(const edge &a, const edge &b)
{
    return a.weight < b.weight;
}

int kruskal(int X, vector<edge> &Edge, int Z)
{
    int vparent, wparent;
    int currentZ = X;
    int result = 0;
    vector<int> parent(X);
    vector<int> rank(X, 0);
    for (int i = 0; i < X; i++)
        parent[i] = i;
    sort(Edge.begin(), Edge.end(), CompareEdge);
    for (int i = 0; i < Edge.size(); i++)
    {
        if ((vparent=Find(parent, Edge[i].v)) != (wparent=Find(parent, Edge[i].w)))
        {
            if (vparent != wparent)
            {
                if (rank[vparent] < rank[wparent])
                    parent[vparent] = wparent;
                else if (rank[vparent] > rank[wparent])
                    parent[wparent] = vparent;
                else
                {
                    parent[wparent] = vparent;
                    rank[vparent]++;
                }
                result += Edge[i].weight;
                currentZ--;
                if (currentZ == Z)
                    break;
            }
        }
    }
    return currentZ == Z ? result : -1;
}

int main()
{
    int X, Y, Z; // 同学数，关系数，分组数
    int A, B, L; // 同学A，同学B，沟通成本L
    int i, j;
    scanf("%d%d%d", &X, &Y, &Z);
    vector<edge> Edge(Y);
    for (i = 0; i < Y; i++)
    {
        scanf("%d%d%d", &A, &B, &L);
        Edge[i].v = A;
        Edge[i].w = B;
        Edge[i].weight = L;
    }
    int result = kruskal(X, Edge, Z);
    if (result < 0)
        printf("false\n");
    else
        printf("%d\n", result);
    return 0;
}