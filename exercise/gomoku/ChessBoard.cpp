#include "ChessBoard.h"
#include <iostream>
#include <string>
#include <iomanip>

using std::cin, std::cout, std::endl, std::setw;

void ChessBoard::show()
{
    cout << endl;
    cout << "     ";
    for (int i = 0; i < size; i++)
    {
        cout << (i < 9 ? "  " : " ") << i + 1 << "  ";
    }
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        cout << endl;
        cout << "  " << char('A' + i) << "  ";
        for (int j = 0; j < size; j++)
        {
            if(board[i][j] == 0)
                cout << "  .  ";
            else
                cout << "  " << board[i][j] << "  ";
        }
        cout << endl;
    }
}

void ChessBoard::move(int row, int col, char chesstype)
{
    if(row < 0 || row >= size || col < 0 || col >= size)
    {
        throw std::out_of_range("Move out of board range.");
    }
    else if(board[row][col] != 0)
    {
        throw std::invalid_argument("Cell already occupied.");
    }
    else
    {
        board[row][col] = chesstype;
    }
}

bool ChessBoard::judgeWin(int row, int col, char chesstype)
{
    int directions[8][2] = {
        {0, 1}, {0, -1},
        {1, 0}, {-1, 0},
        {1, 1}, {-1, -1},
        {1, -1}, {-1, 1}
    };
    int chessCount[8] = {0};
    for(int i = 0; i < 8; i++)
    {
        int dx = directions[i][0];
        int dy = directions[i][1];
        int x = row + dx;
        int y = col + dy;
        while(x >= 0 && x < size && y >= 0 && y < size && board[x][y] == chesstype)
        {
            chessCount[i]++;
            x += dx;
            y += dy;
        }
    }
    for(int i = 0; i < 4; i++)
    {
        if(chessCount[2*i] + chessCount[2*i + 1] + 1 >= 5)
            return true;
    }
    return false;
}