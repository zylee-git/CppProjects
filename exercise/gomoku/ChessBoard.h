#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>

using std::vector;

class ChessBoard
{
public:
    ChessBoard() : size(19) { board.assign(size, vector<char>(size, 0)); };
    ChessBoard(int size) : size(size) { board.assign(size, vector<char>(size, 0)); };
    ~ChessBoard(){};
    void show();
    void move(int row, int col, char chesstype);
    bool judgeWin(int row, int col, char chesstype);
    
    int size;

private:
    vector<vector<char>> board;
};

#endif