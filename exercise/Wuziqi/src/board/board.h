#ifndef BOARD_H

#define BOARD_H

#include <vector>
using std::vector;

class Board
{
public:
    Board(int s = 19);
    // ~Board();
    int getChess(int i, int j) { return board[i][j]; }
    int getSize() { return size; }
    bool placeChess(int i, int j,int color);
    int isOver();

private:
    int size;
    vector<vector<int>> board;
    int count;  // 棋盘总棋子数 
    bool isFull() {return count == size * size;}
};

#endif // BOARD_H