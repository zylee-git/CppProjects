#include <stdio.h>
using namespace std;

template <class T>
void swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

void minHeap(int *heap, int size, int root)
{
    int min = root;
    int l = 2 * root + 1;
    int r = 2 * root + 2;
    if (l < size && heap[l] < heap[min])
    {
        min = l;
    }
    if (r < size && heap[r] < heap[min])
    {
        min = r;
    }
    if (min != root)
    {
        swap(heap[root], heap[min]);
        minHeap(heap, size, min);
    }
}

void buildHeap(int *heap, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        minHeap(heap, size, i);
    }
}

int main()
{
    int k, N;
    int *garden = new int[N * N];
    scanf("%d%d", &k, &N);
    for (int i = 0; i < N * N; i++)
    {
        scanf("%d", garden + i);
    }

    buildHeap(garden, N * N);
    for (int i = 0; i < k - 1; i++)
    {
        swap(garden[0], garden[N * N - i-1]);
        minHeap(garden, N * N - i-1, 0);
    }
    printf("%d\n", garden[0]);
}
