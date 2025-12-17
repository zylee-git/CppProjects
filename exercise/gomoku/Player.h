#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using std::string, std::to_string;

class Player
{
public:
    Player() : name("player " + to_string(count)), chesstype(count == 0 ? 'O' : 'X') { count++; };
    Player(string name) : name(name), chesstype(count == 0 ? 'O' : 'X'){count++;};
    Player(const char* name) : name(name), chesstype(count == 0 ? 'O' : 'X'){count++;};
    static int count;

    string name;
    char chesstype;
};

#endif