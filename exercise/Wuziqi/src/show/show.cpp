#include "show.h"
#include "board.h"
#include <graphics.h>

void game()
{
    Board board(19);

    const int size = board.getSize(); // 棋盘列数和行数
    const int w = length * (size + 1);
    const int h = length * (size + 1);
    const int x0 = length; // 棋盘的左上角的x
    const int y0 = length; // 棋盘的左上角的y

    int player = 1;  // 1为黑子，2为白子，黑子先下

    ExMessage msg;

    initgraph(w, h, SHOWCONSOLE);
    setbkcolor(WHITE);
    cleardevice();
    setlinecolor(BLACK);

    // 画棋盘
    for (int i = 0; i < size; i++)
    {
        line(x0, y0 + length * i, x0 + length * (size - 1), y0 + length * i); // 横线
        line(x0 + length * i, y0, x0 + length * i, y0 + length * (size - 1)); // 竖线
    }

    while (true)
    {
        if(peekmessage(&msg, EM_MOUSE))
        {
            if(msg.message == WM_LBUTTONDOWN)  // 鼠标左键
            {
                int x = msg.x;
                int y = msg.y;
                if(x >= x0 - length/2 && x <= x0 + length * (size - 1) + length/2 &&
                   y >= y0 - length/2 && y <= y0 + length * (size - 1) + length/2)
                {
                    int i = (x - x0 + length/2) / length; // 列号
                    int j = (y - y0 + length/2) / length; // 行号
                    if(board.placeChess(i, j, player)) // 放置棋子
                    {
                        // 画棋子
                        setfillcolor(player == 1 ? BLACK : WHITE);
                        fillcircle(x0 + i * length, y0 + j * length, length / 2 - 2);
                        setlinecolor(BLACK);
                        circle(x0 + i * length, y0 + j * length, length / 2 - 2);
                        // 判断游戏是否结束
                        if(board.isOver())
                        {
                            const char* str = (board.isOver() == 3) ? "Draw!" : (board.isOver() == 1) ? "Black wins!" : "White wins!";
                            MessageBox(GetHWnd(), str, "GameOver", MB_OK);
                            break;
                        }
                        // 交换下棋玩家
                        player = 3 - player;
                    }
                }
            }
        }
    }
}