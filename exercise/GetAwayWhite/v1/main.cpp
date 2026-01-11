#include <graphics.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using std::cin, std::cout, std::endl, std::vector, std::string;


int main()
{
	// 创建界面
	initgraph(500, 480);

	// 参数设置
	const int block_w = 100; // 块宽
	const int block_h = 120; // 块高
	const int rows = 4;     // 行数
	const int cols = 5;     // 列数

	// 块初始化，每行有一个黑块
	srand(time(nullptr));
	vector<int> blacks(rows);
	for (int i = 0;i<rows;i++)
	{
		blacks[i] = rand() % cols;
	}

	// 其他变量
	ExMessage msg;
	int x, y;  // 鼠标点击坐标
	bool over = false;  // 是否结束
	int score = 0;  // 分数

	// 线条颜色
	setlinecolor(BLACK);
	while (!over)
	{
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)  // 左键按下
			{
				x = msg.x;
				y = msg.y;
				int row = y / block_h ;
				int col = x / block_w;
				// 结束条件
				if (row != rows - 1 || blacks[row] != col)
				{
					over = true;
				}
				// 更新黑块位置
				else
				{
					score++;
					for (int i = rows-1;i >0;i--)
					{
						blacks[i] = blacks[i - 1];
					}
					blacks[0] = rand() % cols;
				}
			}
		}

		// 绘制界面和黑块
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (blacks[i] == j)
					setfillcolor(BLACK);
				else
					setfillcolor(WHITE);
				fillrectangle(j * block_w, i * block_h, (j + 1) * block_w, (i + 1) * block_h);
			}
		}
	}

	char str[256];
	sprintf(str, "游戏得分: %d", score);
	MessageBox(GetHWnd(), TEXT(str), TEXT("游戏结束"), MB_OK | MB_ICONINFORMATION);
	getchar();

	return 0;
}