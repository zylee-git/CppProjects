#include <iostream>
#include <limits>
#include "ChessBoard.h"
#include "Player.h"

using std::cin, std::cout, std::endl;
using std::string;

int main()
{
    ChessBoard board;
    Player players[2];
    enum PlayerTurn
    {
        PLAYER1,
        PLAYER2
    };
    PlayerTurn turn = PLAYER1;
    char row_last = 0;
    int col_last = 0;
    bool validInput = false;

    while(true)
    {
        system("cls");
        board.show();
        
        if(row_last != 0 && col_last != 0)
        {
            cout << "Last move: (" << row_last << ", " << col_last << ")" << endl;  // Display last move
        }
        cout << players[turn].name << "'s turn (" << players[turn].chesstype << "). Enter your move (row and column):\n>>> ";
        char row_c;
        int col_c;
        int row, col;

        while(!validInput)
        {
            if(!(cin >> row_c >> col_c))
            {
                system("cls");
                board.show();
                cout << "Invalid input format. Please enter again\n";
                cout << players[turn].name << "'s turn (" << players[turn].chesstype << "). Enter your move (row and column):\n>>> ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            
            if(row_c < 'A' || (row_c > 'A' + board.size - 1 && row_c < 'a') || row_c > 'a' + board.size - 1 || col_c < 1 || col_c > 19)
            {
                system("cls");
                board.show();
                cout << "Input out of range. Please enter again (row A-" << char('A' + board.size - 1) <<  "and column 1-" << board.size << ")\n";
                cout << players[turn].name << "'s turn (" << players[turn].chesstype << "). Enter your move (row and column):\n>>> ";
                continue;
            }

            
            row_last = row_c;
            col_last = col_c;

            row = (row_c >= 'A' && row_c <= 'Z') ? row_c - 'A' : row_c - 'a';
            col = col_c - 1;

            try
            {
                board.move(row, col, players[turn].chesstype);
            }
            catch(const std::exception& e)
            {
                system("cls");
                board.show();
                std::cerr << e.what() << " Please enter again\n";
                cout << players[turn].name << "'s turn (" << players[turn].chesstype << "). Enter your move (row and column):\n>>> ";
                continue;
            }
            

            validInput = true;
        }

        if(board.judgeWin(row, col, players[turn].chesstype))
        {
            system("cls");
            board.show();
            cout << players[turn].name << " wins!" << endl;
            break;
        }
        else
        {
            turn = (turn == PLAYER1) ? PLAYER2 : PLAYER1;
        }

        validInput = false;
    }

    system("pause");
    return 0;
}