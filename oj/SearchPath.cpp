#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Person // 人所处的状态(位置，方向，时间)
{
    short x, y, dir, time;
    Person() : x(0), y(0), dir(0), time(0) {};
    Person(short x, short y, short dir, short time) : x(x), y(y), dir(dir), time(time) {};
};

struct cmp // 自定义排序
{
    bool operator()(const Person &pa, const Person &pb)
    {
        return pa.time > pb.time;
    }
};

short Lx, Ly;         // 古墓的长和宽
short a, b;           // 宝物的坐标
short c, d, face;     // 初始位置和初始面向
short T, q, p;        // T: 机关切换周期，q: 刀山时间，p: 火海时间
short tomb[500][500]; // 地图

// visited数组用于记录每个位置、方向和时间下是否被访问
bool visited[500][500][4];

short bfs()
{
    priority_queue<Person, vector<Person>, cmp> pq; // 优先级队列，以time排序的最小堆
    pq.push(Person(c, d, face, 0));                 // 初始状态入队
    visited[c][d][face] = true;

    while (!pq.empty())
    {
        Person cur = pq.top(); // 队列中时间最短的状态
        pq.pop();
        short cx = cur.x, cy = cur.y, cd = cur.dir, ct = cur.time; // 当前状态

        // 到达宝物位置
        if (cx == a && cy == b)
        {
            return ct;
        }

        short phase = ct % (3 * T); // 判断当前时间对应的机关状态
        short nx, ny;               // 下一状态的坐标

        // 前进一格
        switch (cd)
        {
        case 0: // 上
            nx = cx - 1;
            ny = cy;
            break;
        case 1: // 左
            nx = cx;
            ny = cy - 1;
            break;
        case 2: // 下
            nx = cx + 1;
            ny = cy;
            break;
        case 3: // 右
            nx = cx;
            ny = cy + 1;
            break;
        }
        if (nx >= 0 && ny >= 0 && nx < Lx && ny < Ly && tomb[nx][ny] != 1) // 判断前进一格的位置可以通行
        {
            if (tomb[nx][ny] == 0) // 空地
            {
                if (!visited[nx][ny][cd])
                {
                    visited[nx][ny][cd] = true;
                    pq.push(Person(nx, ny, cd, ct + 1));
                }
            }
            else if (tomb[nx][ny] == 2) // 机关
            {
                if (phase < T) // 刀山
                {
                    if (phase + q <= T && !visited[nx][ny][cd]) // 判断不会切换
                    {
                        visited[nx][ny][cd] = true;
                        pq.push(Person(nx, ny, cd, ct + q)); // 需要花费 q 秒才能通过刀山
                    }
                }
                else if (phase < 2 * T) // 火海
                {
                    if (phase + p <= 2 * T && !visited[nx][ny][cd]) // 判断不会切换
                    {
                        visited[nx][ny][cd] = true;
                        pq.push(Person(nx, ny, cd, ct + p)); // 需要花费 p 秒才能通过火海
                    }
                }
                else // 空地
                {
                    if (!visited[nx][ny][cd])
                    {
                        visited[nx][ny][cd] = true;
                        pq.push(Person(nx, ny, cd, ct + 1)); // 空地，直接通过，消耗 1 秒
                    }
                }
            }
        }

        // 向左转
        short nd = (cd + 1) % 4;
        if (!visited[cx][cy][nd])
        {
            visited[cx][cy][nd] = true;
            pq.push(Person(cx, cy, nd, ct + 1));
        }

        // 向右转
        nd = (cd + 3) % 4;
        if (!visited[cx][cy][nd])
        {
            visited[cx][cy][nd] = true;
            pq.push(Person(cx, cy, nd, ct + 1));
        }
        // 原地等待
        if (nx >= 0 && ny >= 0 && nx < Lx && ny < Ly && tomb[nx][ny] == 2)
        {
            if (phase < T) // 刀山
            {
                if (phase + q <= T) // 不会切换
                {
                    continue;
                }
                else // 只在会切换时考虑等待
                {
                    pq.push(Person(cx, cy, cd, ct + 1));
                }
            }
            else if (phase < 2 * T) // 火海
            {
                if (phase + p <= 2 * T) // 不会切换
                {
                    continue;
                }
                else // 只在会切换时考虑等待
                {
                    pq.push(Person(cx, cy, cd, ct + 1));
                }
            }
            else // 空地可以直接通行，不考虑等待
            {
                continue;
            }
        }
    }

    return -1; // 无法到达宝物位置
}

int main()
{
    cin >> Lx >> Ly;
    cin >> a >> b;
    cin >> c >> d >> face;
    cin >> T >> q >> p;

    for (short i = 0; i < Lx; i++)
    {
        for (short j = 0; j < Ly; j++)
        {
            cin >> tomb[i][j];
        }
    }

    short result = bfs();
    if (result == -1)
    {
        cout << "Error" << endl; // 无法到达宝物
    }
    else
    {
        cout << result << endl; // 输出最短时间
    }

    return 0;
}