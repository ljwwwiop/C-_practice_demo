/*
	title : 2048 手动版 v1.0
	auther : @By Lian
	time : 2020/2/13
	core : 面向过程的思想
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// panel 画一个二维平面矩阵
int panel[4][4];
int score = 0;

// 初始化
void init()
{
	// 随机数种子 , 初始化
	srand((unsigned int)time(0));

	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 4; a++)
			panel[i][a] = 0;
	}
}

// 上移
int canMoveUp()
{
	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 4; a++)
		{
			// 第一行 或者 是0的位子
			if (i == 0 || panel[i][a] == 0)
			{
				continue;
			}
			// 假如上方有空的 ，或者可以组合的
			if (panel[i - 1][a] == 0 || panel[i - 1][a] == panel[i][a])
				return 1;
		}
	}
	return 0;
}

void moveUp()
{
	// 一步一步 一直移动，直到不能移动为止
	while (canMoveUp())
	{
		for (int i = 0; i < 4; i++)
		{
			for (int a = 0; a < 4; a++)
			{
				// 空位子
				if (i == 0 || panel[i][a] == 0)
				{
					continue;
				}
				// 上方为空的
				if (panel[i - 1][a] == 0)
				{
					panel[i - 1][a] = panel[i][a];
					panel[i][a] = 0;
					continue;
				}
				// 可以合并
				if(panel[i-1][a] == panel[i][a])
				{
					score += panel[i][a] * 3;
					panel[i - 1][a] = panel[i][a] * 2;
					panel[i][a] = 0;
				}
			}
		}
	}
}

// 下移
int canMoveDown()
{
	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 4; a++)
		{
			// 同上
			if (i == 3 || panel[i][a] == 0)
			{
				continue;
			}
			if (panel[i + 1][a] == 0 || panel[i + 1][a] == panel[i][a])
				return 1;
		}
	}
	return 0;
}

void moveDown()
{
	while (canMoveDown())
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == 3 || panel[i][j] == 0)
				{
					continue;
				}
				if (panel[i + 1][j] == 0)
				{
					panel[i + 1][j] = panel[i][j];
					panel[i][j] = 0;
					continue;
				}
				if (panel[i + 1][j] == panel[i][j])
				{
					score += panel[i][j] * 3;
					panel[i + 1][j] = panel[i][j] * 2;
					panel[i][j] = 0;
				}

			}
		}
	}
}

// 左移
int canMoveLeft()
{
	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 4; a++)
		{
			// 第一行 或者 是0的位子
			if (a == 0 || panel[i][a] == 0)
			{
				continue;
			}
			// 假如上方有空的 ，或者可以组合的
			if (panel[i][a - 1] == 0 || panel[i][a - 1] == panel[i][a])
				return 1;
		}
	}
	return 0;
}

void moveLeft()
{
	while (canMoveLeft())
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (j == 0 || panel[i][j] == 0)
				{
					continue;
				}
				if (panel[i][j-1] == 0)
				{
					panel[i][j-1] = panel[i][j];
					panel[i][j] = 0;
					continue;
				}
				if (panel[i][j-1] == panel[i][j])
				{
					score += panel[i][j] * 3;
					panel[i][j-1] = panel[i][j] * 2;
					panel[i][j] = 0;
				}

			}
		}
	}
}

// 右移
int canMoveRight()
{
	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 4; a++)
		{
			// 第一行 或者 是0的位子
			if (a == 3 || panel[i][a] == 0)
			{
				continue;
			}
			// 假如上方有空的 ，或者可以组合的
			if (panel[i][a + 1] == 0 || panel[i][a + 1] == panel[i][a])
				return 1;
		}
	}
	return 0;
}

void moveRight()
{
	while (canMoveRight())
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (j == 3 || panel[i][j] == 0)
				{
					continue;
				}
				if (panel[i][j + 1] == 0)
				{
					panel[i][j + 1] = panel[i][j];
					panel[i][j] = 0;
					continue;
				}
				if (panel[i][j + 1] == panel[i][j])
				{
					score += panel[i][j] * 3;
					panel[i][j + 1] = panel[i][j] * 2;
					panel[i][j] = 0;
				}

			}
		}
	}
}

// 每一轮随机生成新的块
int spawnNewBlock()
{
	int i, a;
	int haveBlank = 0;
	for (int i = 0; i < 4; i++)
	{
		for (a = 0; a < 4; a++)
		{
			if (panel[i][a] == 0)
			{
				haveBlank += 1;
			}
		}
	}
	if (haveBlank == 0)
	{
		// 没空余位子死亡
		return 0;
	}
	do
	{
		// 随机生成点
		i = rand() % 4;
		a = rand() % 4;
	} while (panel[i][a] != 0);
	panel[i][a] = 2;
	return 1;
}

// 打印字体颜色 0 2 4 8 16 32..
void printNumber(int number)
{
	int color;
	switch (number)
	{

	case 2:
		color = 32;
		break;
	case 4:
		color = 33;
		break;
	case 8:
		color = 31;
		break;
	case 16:
		color = 34;
		break;
	case 32:
		color = 35;
		break;
	case 64:
		color = 36;
		break;
	case 128:
		color = 31;
		break;
	case 256:
		color = 32;
		break;
	case 512:
		color = 33;
		break;
	case 1024:
		color = 34;
		break;
	case 2048:
		color = 35;
		break;
	case 0:
	default:
		color = 37;
		break;
	}
	printf("\033[%d;1m %5d\033[0m", color, number);
}

// 打印面板
void printPanel()
{
	system("cls");
	printf("当 前 手 动 版 本-v1.0 By@Lian \n");
	printf("请输入任意 方向键(W A S D) 后回车确认操作\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printNumber(panel[i][j]);
		}
		printf("\n\n");
	}
	printf("score：%d\n", score);

}

// 获取键盘输入
void play()
{
	char ch;
	int re = scanf("%c",&ch);
	if (re == 0)
	{
		printf("输入有误，请重新输入! \n");
		play();
		return;
	}
	switch (ch)
	{
	case 'W':
	case 'w':
		moveUp();
		break;
	case 'S':
	case 's':
		moveDown();
		break;
	case 'A':
	case 'a':
		moveLeft();
		break;
	case 'D':
	case 'd':
		moveRight();
		break;
	case 'exit':
		exit(0);
	default:
		play();
		break;
	}
}

// 函数入口，主函数
int main()
{
	init();
	while (spawnNewBlock())
	{
		printPanel();
		play();
	}
	printf("Sorry,Game over!\n");
	printf("最后得分：%d\n", score);
	system("pause");
	return 0;
}
