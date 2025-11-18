#include <easyx.h>
#include <iostream>

using std::cin, std::cout, std::endl;

void drawShape()
{
    // 点
    putpixel(30, 50, RED);

    // 线
    setlinecolor(BLUE);  // 设置线条颜色
    setlinestyle(PS_SOLID, 2);  // 设置线条样式(实线，宽度2)
    /**
     * 线条样式参数说明：
     * PS_SOLID：实线
     * PS_DASH：虚线
     * PS_DOT：点线
     * PS_DASHDOT：点划线
     * PS_DASHDOTDOT：双点划线
     */
    line(50, 50, 150, 150);

    // 矩形
    rectangle(200, 50, 300, 150);
    setfillcolor(GREEN);  // 设置填充颜色
    fillrectangle(350, 50, 450, 150);  // 填充矩形
    solidrectangle(500, 50, 600, 150);  // 无边框填充矩形

    // 圆角矩形
    roundrect(200, 200, 300, 300, 20, 20);
    fillroundrect(350, 200, 450, 300, 30, 30);
    solidroundrect(500, 200, 600, 300, 40, 40);

    // 圆
    circle(100, 250, 50);
    fillcircle(100, 400, 50);
    solidcircle(250, 400, 50);

    // 椭圆
    ellipse(350, 350, 550, 450);
}

void drawText()
{
    // 设置文字样式
    settextstyle(48, 0, "微软雅黑");
    /**
     * 第一个参数为nHeight，表示字体高度
     * 第二个参数为nWidth，表示字体宽度，0表示自适应
     * 第三个参数为字体
     */

    // 设置文字颜色
    settextcolor(BROWN);

    //设置背景模式
    setbkmode(TRANSPARENT);
    /**
     * TRANSPARENT表示文字背景透明
     */

    // 绘制文字
    outtextxy(10, 10, _T("Hello Easyx"));

    /**
     * 字符集问题的解决方法
     * 1. 字符串前面使用L进行强制转换
     * 2. 用带参宏(_T(), _TEXT())把字符串包裹起来自适应转换
     */

    // 显示数字，要先转换为字符串
    int score = 66;
    char str[50];
    sprintf(str, "Score: %d", score);

    settextstyle(24, 0, "微软雅黑");
    outtextxy(getwidth()-150, 10, _T(str));
}

void centerText()
{
    /**
     * 将文字居中显示在指定区域
     */

    // 指定区域
    int rx = 100;
    int ry = 100;
    int rw = 400;
    int rh = 200;

    setfillcolor(LIGHTGRAY);
    fillrectangle(rx, ry, rx + rw, ry + rh);

    // 计算文字位置
    settextstyle(24, 0, "微软雅黑");
    settextcolor(RED);
    setbkmode(TRANSPARENT);
    const TCHAR* center_str = _T("This text is centered");
    int hSpace = (rw - textwidth(center_str)) / 2;
    int vSpace = (rh - textheight(center_str)) / 2;

    // 绘制文字
    outtextxy(rx + hSpace, ry + vSpace, center_str);
}

int main()
{
    // 创建窗口
    initgraph(640, 480, EX_SHOWCONSOLE);
    /*可用getwidth()和getheight()获取窗口参数*/
    /**
     * 第三个参数：
     * 1, EX_SHOWCONSOLE：保持控制台
     * 2, EX_NOCLOSE：禁用关闭按钮
     * 4, EX_NOMINIMIZE：禁用最小化按钮
     * 8, EX_DBLCLKS：支持双击事件
     * 可以通过按位或（|）组合使用多个选项
     */

    // 设置窗口的背景颜色，也可以用RGB(R, G, B)自定义颜色
    setbkcolor(GREEN);

    // 清空窗口并用背景色填充
    cleardevice();

    /**
     * 坐标系说明：
     * 默认情况下，窗口的左上角是坐标原点(0, 0)，
     * x轴向右延伸，y轴向下延伸。
     */

    // drawShape();

    // drawText();

    centerText();

    system("pause");
    return 0;
}