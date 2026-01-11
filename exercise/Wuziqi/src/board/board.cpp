#include "board.h"

Board::Board(int s)
{
    size = s;
    board = vector<vector<int>>(size, vector<int>(size, 0));
    count = 0;
}

bool Board::placeChess(int i, int j, int color)
{
    if (i < 0 || i >= size || j < 0 || j >= size)
        return false;
    if (board[i][j] != 0)
        return false;

    board[i][j] = color;
    count++;
    return true;
}

int Board::isOver()
{
    if (isFull())
        return 3; // 平局

    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}}; // 横、竖、斜右、斜左

    for (auto &dir : directions)
    {
        int di = dir[0];
        int dj = dir[1];
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                int color = board[i][j];
                if (color == 0)
                {
                    continue;
                }
                int count = 1;
                for (int k = 1; k < 5; k++)
                {
                    int ii = i + di * k;
                    int jj = j + dj * k;
                    if (ii < 0 || ii >= size || jj < 0 || jj >= size || board[ii][jj] != color) // 超出边界或者颜色不匹配
                    {
                        break;
                    }
                    count++;
                }
                if (count >= 5)
                {
                    return color; // 返回胜利的颜色编号
                }
            }
        }
    }

    return 0; // 未结束
}