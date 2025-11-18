#include <easyx.h>
#include <iostream>

void mouseTest(ExMessage msg)
{
    while(true)
    {
        if(peekmessage(&msg, EX_MOUSE)) // 只获取鼠标消息
        {
            switch(msg.message)
            {
            case WM_LBUTTONDOWN:  // 左键按下
                std::cout << "Left mouse button clicked at (" 
                          << msg.x << ", " << msg.y << ")" << std::endl;
                break;
            case WM_RBUTTONDOWN:  // 右键按下
                std::cout << "Right mouse button clicked at (" 
                          << msg.x << ", " << msg.y << ")" << std::endl;
                break;
            case WM_MBUTTONDOWN:  // 中键按下
                std::cout << "Middle mouse button clicked at (" 
                          << msg.x << ", " << msg.y << ")" << std::endl;
                break;
            case WM_MOUSEWHEEL:  // 鼠标滚轮
                if(msg.wheel > 0)
                    std::cout << "Mouse wheel scrolled up at (" 
                              << msg.x << ", " << msg.y << ")" << std::endl;
                else
                    std::cout << "Mouse wheel scrolled down at (" 
                              << msg.x << ", " << msg.y << ")" << std::endl;
                break;
            case WM_LBUTTONDBLCLK:  // 左键双击
                std::cout << "Left mouse button double-clicked at (" 
                          << msg.x << ", " << msg.y << ")" << std::endl;
                break;
            case WM_MOUSEMOVE:  // 鼠标移动
                std::cout << "Mouse moved to (" 
                          << msg.x << ", " << msg.y << ")" << std::endl;
                break;
            default:
                break;
            }
        }
    }
}

void keyTest(ExMessage msg)
{
    while (true)
    {
        if(peekmessage(&msg, EX_KEY))  // 只获取键盘消息, msg.vkcode为虚拟键码
        {
            if(msg.message == WM_KEYDOWN)  // 键盘按下消息
            {
                switch(msg.vkcode)
                {
                case VK_UP:
                    std::cout << "Up arrow key pressed" << std::endl;
                    break;
                case VK_DOWN:
                    std::cout << "Down arrow key pressed" << std::endl;
                    break;
                case VK_LEFT:
                    std::cout << "Left arrow key pressed" << std::endl;
                    break;
                case VK_RIGHT:
                    std::cout << "Right arrow key pressed" << std::endl;
                    break;
                case VK_ESCAPE:
                    std::cout << "Escape key pressed" << std::endl;
                    break;
                case 'A':
                    std::cout << "A key pressed" << std::endl;
                    break;
                }
            }
            else if(msg.message == WM_KEYUP)  // 键盘释放消息
            {
            }
        }
    }
    
}

int main()
{
    initgraph(640, 480, EX_SHOWCONSOLE | EX_DBLCLKS);

    // 定义消息结构体变量
    ExMessage msg;

    // 获取消息  peekmessage(&msg, EX_MOUSE)
    /**
     * 消息类型参数说明：
     * EX_MOUSE：鼠标消息
     * EX_KEY：键盘消息
     */

    // mouseTest(msg);

    // keyTest(msg);

    return 0;
}