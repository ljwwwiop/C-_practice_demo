/*
	简单的贪吃蛇：AI模式 和 手动模式
	作者：@by Lian
	时间：2020/2/7
	AI: 盲搜 -> bfs 和 dfs 或 Astar 
*/
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
#include <Windows.h>

#include "FindPathBFS.h"
using namespace std;

// 定义四个方向方向
int dir[4][2] = { (0,1),(0,-1),(1,0),(-1,0) };

// 定义常量
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define HEAD 0

int speed = 0;
// 设置光标位子到 x,y
void gotoXY(int x,int y)
{
	COORD c;
	c.X = x, c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

// 设置颜色 windows库中的api
void SetColor(unsigned short ForeColor = 7,unsigned short BackGroundColor = 0) 
{
	// 获取当前窗口的
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	// 上色
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);
}

// 游戏设置相关模块，把函数装到一个类里面，函数定义为static静态成员，不生成实体也可以直接调用
class GameSetting
{
public:
	// 游戏窗口的长宽
	static const int window_height = 40;
	static const int window_width = 80;
public:
	// 初始化
	static void GameInit()
	{
		// 设置窗口游戏大小
		char buffer[32];
		sprintf_s(buffer,"mode con cols=%d lines=%d",window_width,window_height);
		system(buffer);

		// 隐藏光标
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO CursorInfo; // api 生成对象
		GetConsoleCursorInfo(handle,&CursorInfo); // 获取控制台光标
		CursorInfo.bVisible = false; // 隐藏光标
		SetConsoleCursorInfo(handle, &CursorInfo); // 设置光标信息
		// 初始化随机数种子
		srand((unsigned int)time(0));
	}
};

// 打印信息类 -> 欢迎，分数 ，说明， 结束 等
class PrintInfo
{
public:
	// 手动模式 or AI模式
	static void DrawChoicInfo()
	{
		gotoXY(GameSetting::window_width/2 - 10,GameSetting::window_height/2 - 5);
		cout << "请选择游戏模式：" << endl;
		gotoXY(GameSetting::window_width/2 - 10,GameSetting::window_height/2 - 3);
		cout << "1 ->  手动模式：" << endl;
		gotoXY(GameSetting::window_width / 2 - 10, GameSetting::window_height / 2 - 1);
		cout << "2 ->AI自动模式：" << endl;
		gotoXY(GameSetting::window_width / 2 - 10, GameSetting::window_height / 2 + 1);
		cout << "请输入您的选择：" << endl;
	}
	// 绘制地图
	static void DrawMap()
	{
		// 先把上面的请控
		system("cls");
		int i, j;
		for (int i = 0; i < GameSetting::window_width; i++)
			cout << "#";
		cout << endl;
		for (int i = 0; i < GameSetting::window_height - 2; i++)
		{
			for (int j = 0; j < GameSetting::window_width; j++)
			{
				if (i == 13 && j >= GameSetting::window_width - 29)
				{
					cout << "#";
					continue;
				}
				if (j == 0 || j == GameSetting::window_width - 29 || j == GameSetting::window_width - 1)
					cout << "#";
				else
					cout << " ";
			}
			cout << endl;
		}
		for (int i = 0; i < GameSetting::window_width; i++)
			cout << "#";
	}
	// 游戏结束时候
	static void GameOver(int score)
	{
		SetColor(12,0);
		gotoXY(GameSetting::window_width/2-20,GameSetting::window_height/2 - 5);
		cout << "游戏结束，拜拜了!" << endl;
		gotoXY(GameSetting::window_width/2 - 20,GameSetting::window_height/2 - 3);
		cout << "您最终得分: "<<score << endl;
	}
	// 画出分数
	static void DrawScore(int score) 
	{
		gotoXY(GameSetting::window_width - 22 + 14, 6);
		cout << "  ";
		gotoXY(GameSetting::window_width - 22 + 14, 4);
		cout << "  ";

		gotoXY(GameSetting::window_width - 22, 6);
		cout << "当前玩家分数: " << score << endl;
		gotoXY(GameSetting::window_width - 22, 4);
		cout << "当前游戏速度: " << 10 - speed / 25 << endl;
	}
	// 画出游戏操作界面
	static void DrawGameInfo(bool model)
	{
		gotoXY(GameSetting::window_width - 22, 8);

		if (model)
		{
			cout << "当前模式:" << "人机" << endl;
		}
		else 
		{
			cout << "当前模式:"<<"AI"<<endl;
		}
		gotoXY(GameSetting::window_width - 22 ,10);
		cout << "历史最优分数:" << 0 << endl;

		gotoXY(GameSetting::window_width - 22,18);
		cout << "游戏操作说明： " << endl;
		gotoXY(GameSetting::window_width - 22, 20);
		cout << "W:上     S:下  " << endl;
		gotoXY(GameSetting::window_width - 22, 22);
		cout << "A:左     D:右  " << endl;

		gotoXY(GameSetting::window_width - 22, 24);
		cout << "调节游戏速度： " << endl;
		gotoXY(GameSetting::window_width - 22, 26);
		cout << "键盘i :加速度  " << endl;
		gotoXY(GameSetting::window_width - 22, 28);
		cout << "键盘o :减速度  " << endl;
		gotoXY(GameSetting::window_width - 22, 30);
		cout << "E S C :  退出  " << endl;

		gotoXY(GameSetting::window_width - 22, 34);
		cout << "作者: by@Lian  " << endl;
		gotoXY(GameSetting::window_width - 22, 36);
		cout << "版本: 1.1.0    " << endl;

	}

};

// 食物类
class Food
{
private:
	// 食物坐标x,y
	COORDINATE m_coordinate;
public:
	// 坐标范围
	// x: [1,GameSetting::window_width - 30]
	// y: [1,GameSetting::window_height - 2]
	void RandomXY(vector<COORDINATE> &coord) 
	{
		m_coordinate.x = rand() % (GameSetting::window_width - 30) + 1;
		m_coordinate.y = rand() % (GameSetting::window_height - 2) + 1;
		unsigned int i;
		// 不允许食物出现在蛇的位置上，如果发生了，重新生成
		for (i = 0; i < coord.size(); i++)
		{
			// 判断食物位置是否在蛇身上，否在重新生成
			if (coord[i].x == m_coordinate.x && coord[i].y == m_coordinate.y)
			{
				m_coordinate.x = rand() % (GameSetting::window_width - 30) + 1;
				m_coordinate.y = rand() % (GameSetting::window_height - 2) + 1;
				i = 0;
			}
		}
	}
	// 默认构造函数
	Food() {}
	// 构造函数，传入参数是食物坐标
	Food(vector<COORDINATE> &coord) 
	{
		RandomXY(coord);
	}
	// 画出食物
	void DrawFood()
	{
		SetColor(12,0);
		gotoXY(m_coordinate.x,m_coordinate.y);
		cout << "$";
		SetColor(7,0);
	}
	
	// 食物接口,获取食物的位置
	COORDINATE GetFoodCoordinate() 
	{
		return m_coordinate;
	}

};

// 蛇类：蛇的移动，打印，吃食物
// 地图大小 width [2, width -2] height [2,height -2]
class Snake 
{
private:
	// 模式判断 true 人机 false AI
	bool m_model;
	// 方向
	int m_direction;
	// 是否存活
	bool m_is_alive;
private:
	// AI功能
	bool m_chess[GameSetting::window_width - 29 +1][GameSetting::window_height];
	FindPathBFS m_AISnake;
	COORDINATE map_size;
public:
	// 蛇坐标
	vector<COORDINATE> m_coordinate;

public:
	// 默认构造函数 默认人机模式
	Snake(bool model= false):m_model(model)
	{
		map_size.x = GameSetting::window_width - 29 + 1;
		map_size.y = GameSetting::window_height;
		// 移动方向
		m_direction = 1;
		m_is_alive = true;
		COORDINATE snake_head;
		snake_head.x = GameSetting::window_width / 2 - 15;
		snake_head.y = GameSetting::window_height / 2;

		// 初试蛇身长度为 3节
		this->m_coordinate.push_back(snake_head);
		snake_head.y++;
		this->m_coordinate.push_back(snake_head);
		snake_head.y++;
		this->m_coordinate.push_back(snake_head);

		// 围墙是障碍
		for (int i = 0; i < GameSetting::window_width - 29 + 1; i++)
		{
			m_chess[i][0] = true;
			m_chess[i][GameSetting::window_height - 1] = true;
		}
		for (int i = 0; i < GameSetting::window_height - 1; i++)
		{
			m_chess[0][i] = true;
			m_chess[GameSetting::window_width - 29][i] = true;
		}
	}
	// 设置游戏模式
	void set_model(bool m)
	{
		m_model = m;
	}
	// 获取键盘输入
	void listen_key_board() 
	{
		char ch;
		// _kbhit 非阻塞函数
		if (_kbhit)
		{
			ch = _getch(); // getch() -> 返回int
			switch (ch) 
			{
			case 'w':
			case 'W':
				if (this->m_direction == DOWN)
					break;
				this->m_direction = UP;
				break;
			case 's':
			case 'S':
				if (this->m_direction == UP)
					break;
				this->m_direction = DOWN;
				break;
			case 'a':
			case 'A':
				if (this->m_direction == RIGHT)
					break;
				this->m_direction = LEFT;
				break;
			case 'd':
			case 'D':
				if (this->m_direction == LEFT)
					break;
				this->m_direction = RIGHT;
				break;
			case 'i':
			case 'I':
				if (speed >= 25)
					speed -= 25;
				break;
			case 'o':
			case 'O':
				if (speed < 250)
					speed += 25;
				break;
			}

		}
	}
	// AI 速度
	void AI_speed()
	{
		char ch;
		if (_kbhit)
		{
			ch = _getch();
			switch (ch)
			{
			case 'i':
			case 'I':
				if (speed >= 25)
					speed -= 25;
				break;
			case 'o':
			case 'O':
				if (speed < 250)
					speed += 25;
				break;
			}
		}
	}

	// AI自动寻路
	void AI_find_path(Food &f)
	{
		static int not_found = 1;
		COORDINATE fpoint = f.GetFoodCoordinate();

		for (unsigned int i = 0; i < m_coordinate.size(); i++)
		{
			m_chess[m_coordinate[i].x][m_coordinate[i].y] = true;
		}
		COORDINATE begin_point, end_point;
		begin_point = m_coordinate[HEAD];
		end_point = fpoint;

		m_AISnake.InitMap((bool**)m_chess);
		m_AISnake.GetPath(begin_point,end_point);

	}
	// 检测是否碰到自己
	bool self_collision(COORDINATE head)
	{
		for (unsigned int i = 1; i < m_coordinate.size(); i++)
		{
			if (head.x == m_coordinate[i].x && head.y == m_coordinate[i].y)
				return true;
		}
		return false;
	}
	
	// AI移动路径问题
	void AI_move_snake() 
	{
		static int cot = 0;
		AI_speed();
		COORDINATE head, temp;
		if (!m_AISnake.m_paths_queue.empty())
		{
			head = m_AISnake.m_paths_queue.front();
			m_AISnake.m_paths_queue.pop();
		}
		else
		{
			// 使用dir定义的方向
			for (int i = 0; i < 4; i++)
			{
				int break_num = rand() % 4;
				temp = m_coordinate[HEAD];
				temp.x = temp.x + dir[i][0];
				temp.y = temp.y + dir[i][1];
				// 判断路劲是否可走
				if (temp.x <= 0 || temp.x >= (map_size.x - 1) ||
					temp.y <= 0 || temp.y >= (map_size.y - 1) || self_collision(temp))
				{
					continue;
				}
				head = temp;
				if (break_num == i)
					break;

			}
		}
		m_coordinate.insert(m_coordinate.begin(),head);
	}

	// 移动贪吃蛇
	void move_snake()
	{
		// 获取键盘
		listen_key_board();
		// 头部
		COORDINATE head = m_coordinate[0];
		// 方向 上 下 左 右
		switch (this->m_direction)
		{
		case UP:
			head.y--;
			break;
		case DOWN:
			head.y++;
			break;
		case LEFT:
			head.x--;
			break;
		case RIGHT:
			head.x++;
			break;
		}
		// 将新的食物点插入移动后新的蛇头
		m_coordinate.insert(m_coordinate.begin(),head);
	}

	// 判断是否吃到食物
	bool is_eat_food(Food &f)
	{
		// 获取食物坐标
		COORDINATE food_coordinate = f.GetFoodCoordinate();
		// 吃到食物，重新生成，不删除蛇尾
		if (m_coordinate[HEAD].x == food_coordinate.x && m_coordinate[HEAD].y == food_coordinate.y)
		{
			f.RandomXY(m_coordinate);
			return true;
		}
		else {
			// 没吃到食物，删除蛇尾
			m_coordinate.erase(m_coordinate.end() - 1);
			return false;
		}
	}
	// 判断蛇死了没有
	bool snake_is_alive() 
	{
		if (m_coordinate[HEAD].x <= 0 ||
			m_coordinate[HEAD].x >= GameSetting::window_width - 29 ||
			m_coordinate[HEAD].y <= 0 ||
			m_coordinate[HEAD].y >= GameSetting::window_height - 1)
		{
			// 超出边界
			m_is_alive = false;
			return m_is_alive;
		}

		// 是否碰到自己
		for (unsigned int i = 1; i < m_coordinate.size(); i++)
		{
			if (m_coordinate[i].x == m_coordinate[HEAD].x && m_coordinate[i].y == m_coordinate[HEAD].y)
			{
				m_is_alive = false;
				return m_is_alive;
			}
		}
		m_is_alive = true;
		return m_is_alive;
	}

	// 画出蛇来
	void draw_snake()
	{
		// 设置颜色
		SetColor(10, 0);
		for (unsigned int i = 0; i < this->m_coordinate.size(); i++)
		{
			gotoXY(m_coordinate[i].x,m_coordinate[i].y);
			cout << "*";
		}
		// 恢复颜色
		SetColor(7, 0);
	}
	// 清除屏幕上的贪吃蛇
	void ClearSnake()
	{
		for (unsigned int i = 0; i < m_coordinate.size(); i++)
		{
			m_chess[m_coordinate[i].x][m_coordinate[i].y] = false;
		}
		gotoXY(m_coordinate[this->m_coordinate.size()-1].x,m_coordinate[this->m_coordinate.size()-1].y);
		cout << " ";
	}

	// 获取贪吃蛇长度
	int GetSnakeSize()
	{
		return m_coordinate.size();
	}
	// 获取当前游戏模式
	bool GetModel()
	{
		return m_model;
	}
};

// 主函数，启动函数，整合各种类和资源
int main()
{
	// 实例化
	GameSetting setting;
	PrintInfo print_info;
	Snake snake;
	// 初始化游戏
	setting.GameInit();
	// 选择模式
	print_info.DrawChoicInfo();
	char ch = _getch();
	switch (ch)
	{
	case '1':
		snake.set_model(true);
		speed = 50;
		break;
	case '2':
		snake.set_model(false);
		break;
	default:
		gotoXY(GameSetting::window_width/2 - 10,GameSetting::window_height/2 + 3);
		cout << " 输入错误 ,bye!" << endl;
		cin.get();
		cin.get();
		return 0;
	}
	gotoXY(GameSetting::window_width/2 - 10,GameSetting::window_height/2 +3);
	system("pause");
	// 画地图
	print_info.DrawMap();
	print_info.DrawGameInfo(snake.GetModel());
	// 生成食物
	Food food(snake.m_coordinate);
	// 游戏死循环
	while (true)
	{
		// 打印成绩
		print_info.DrawScore(snake.GetSnakeSize());
		// 画出食物
		food.DrawFood();
		// 处理蛇尾，每次画蛇前必须要做的操作
		snake.ClearSnake();
		// 判断是否吃到食物
		snake.is_eat_food(food);
		// 根据用户选择不同模式 -> 选择不同方式
		if (snake.GetModel() == true)
		{
			snake.move_snake();
		}
		else
		{
			snake.AI_find_path(food);
			snake.AI_move_snake();
		}
		// 画蛇
		snake.draw_snake();
		// 蛇 是否还活着
		if (!snake.snake_is_alive())
		{
			print_info.GameOver(snake.GetSnakeSize());
			break;
		}
		// 控制速度
		Sleep(speed);
		
	}
	cin.get();
	cin.get();

	return 0;
}



