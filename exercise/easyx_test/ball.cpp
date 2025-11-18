#include <easyx.h>
#include <iostream>
#include <time.h>

int main()
{
    initgraph(800, 600);
    setbkcolor(WHITE);

    // FPS 60Hz
    const int FPS = 60;
    const clock_t frameDelay = 1000 / FPS;

    int x = 100;
    int y = 100;
    int r = 20;

    int speed = 180 / FPS;  // 球的速度
    int dx = 0;  // x方向是否运动
    int dy = 0;  // y方向是否运动

    ExMessage msg;

    while(true)
    {
        clock_t frameStart = clock();  // 记录帧开始时间

        if(peekmessage(&msg, EX_KEY | EX_MOUSE))  // 检测键盘或鼠标消息
        {
            if(msg.message == WM_KEYDOWN)  // 键盘按下
            {
                switch(msg.vkcode)
                {
                case VK_LEFT:
                    dx = -1;
                    break;
                case VK_RIGHT:
                    dx = 1;
                    break;
                case VK_UP:
                    dy = -1;
                    break;
                case VK_DOWN:
                    dy = 1;
                    break;
                default:
                    break;
                }
            }
            else if(msg.message == WM_KEYUP)  // 键盘释放
            {
                switch(msg.vkcode)
                {
                case VK_LEFT:
                    dx = 0;
                    break;
                case VK_RIGHT:
                    dx = 0;
                    break;
                case VK_UP:
                    dy = 0;
                    break;
                case VK_DOWN:
                    dy = 0;
                    break;
                default:
                    break;
                }
            }
        }
        BeginBatchDraw();  // 开始批量绘图(双缓冲防止闪屏)

        cleardevice();

        // 更新球的位置
        x += dx * speed;
        y += dy * speed;

        // 边界检测
        if(x - r < 0) x = r;
        if(x + r > getwidth()) x = getwidth() - r;
        if(y - r < 0) y = r;
        if(y + r > getheight()) y = getheight() - r;

        // 画球
        setfillcolor(RED);
        fillellipse(x, y, x + r, y + r);

        EndBatchDraw();  // 结束批量绘图

        // 控制帧率
        clock_t frameTime = clock() - frameStart;  // 计算帧耗时
        if(frameTime < frameDelay)
            Sleep(frameDelay - frameTime);

        msg.message = 0;  // 重置消息
    }
}