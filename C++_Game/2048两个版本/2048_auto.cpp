/*
	title : 2048 自动版 v1.0 并非 AI选优玩法
	auther : @By Lian
	time : 2020/2/13
	core : 面向过程
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int panel[4][4];
int score = 0;

void init()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			panel[i][j] = 0;
	}
}

// 上
int canMoveUp()
{
	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 4; a++)
		{
			// 第一行为0
			if (i == 0 || panel[i][a] == 0)
			{
				continue;
			}
			// 上方有空或者是可以组合
			if (panel[i - 1][a] == 0 || panel[i - 1][a] == panel[i][a])
			{

				return 1;
			}
		}
	}
	return 0;
}

void moveUp()
{
	// 一步一步移动，移动到不能动为止
	while (canMoveUp())
	{
		for (int i = 0; i < 4; i++)
		{
			for (int a = 0; a < 4; a++)
			{
				// 0 行 或者位子上为0
				if (i == 0 || panel[i][a] == 0)
				{
					continue;
				}
				// 上方有空
				if (panel[i - 1][a] == 0)
				{
					panel[i - 1][a] = panel[i][a];
					panel[i][a] = 0;
					continue;
				}
				// 可以合并
				if (panel[i - 1][a] == panel[i][a])
				{
					score += panel[i][a] * 2;
					panel[i - 1][a] = panel[i][a] * 2;
					panel[i][a] = 0;
				}
			}
		}
	}
}

// 下
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

// 左
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
				if (panel[i][j - 1] == 0)
				{
					panel[i][j - 1] = panel[i][j];
					panel[i][j] = 0;
					continue;
				}
				if (panel[i][j - 1] == panel[i][j])
				{
					score += panel[i][j] * 3;
					panel[i][j - 1] = panel[i][j] * 2;
					panel[i][j] = 0;
				}

			}
		}
	}
}

// 右
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

// 权值上移
int weightMoveUp()
{
	int weight = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// 空位子
			if (i == 0 || panel[i][j] == 0)
				continue;
			// 权值最高的上移
			if (panel[i - 1][j] == panel[i][j])
			{
				weight += panel[i][j] * 2;
				continue;
			}
			if (panel[i - 1][j] == 0)
				weight++;
		}
	}
	return weight;
}
// 权值右移
int weightMoveRight()
{
	if (canMoveRight() != 1)
	{
		return 0;
	}
	int cache[4][4];
	int cacheScore;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cache[i][j] = panel[i][j];
		}
	}
	cacheScore = score;
	moveRight();
	int weight = weightMoveUp();
	score = cacheScore;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			panel[i][j] = cache[i][j];
	}
	return weight;
}
// 权值左移
int weightMoveLeft()
{
	if (canMoveLeft() != 1)
	{
		return 0;
	}
	int cache[4][4];
	int cacheScore;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cache[i][j] = panel[i][j];
		}
	}
	cacheScore = score;
	moveLeft();
	int weight = weightMoveUp();
	score = cacheScore;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			panel[i][j] = cache[i][j];
	}
	return weight;
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

// 上色
void printNumber(int number)
{
	int color;
	switch (number)
	{

	case 2:
		color = 39;
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
	printf("当 前 自 动 模 式 中！-v1.0 By@Lian\n");
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

int status = 1;
void play()
{
	if (weightMoveUp() >= 8)
	{
		moveUp();
		Sleep(50);
		return;
	}
	int left = weightMoveLeft();
	int right = weightMoveRight();
	if (left >= 4 && left > right)
	{
		moveLeft();
		Sleep(50);
		return;
	}
	if (right >= 4 && right > left)
	{
		moveRight();
		Sleep(50);
		return;
	}
	switch (status)
	{
	case 1:
		moveUp();
		break;
	case 2:
		moveRight();
		break;
	case 3:
		moveDown();
		break;
	case 4:
		moveLeft();
		break;
	case 5:
		moveUp();
		break;
	default:
		break;
	}
	status++;
	if (status > 5)
	{
		status = 1;
	}
	Sleep(50);
}

// 主函数 函数入口
int main()
{
	init();
	while (spawnNewBlock())
	{
		printPanel();
		play();
	}
	printf("Sorry ，Game Over!\n");
	printf("最终得分 ：%d\n", score);
	system("pause");
	return 0;
}


