/*
 * 2019/1/31 C++ Tetris制作
 * auther: @by Lian
 * core : 面向过程
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <conio.h>

using namespace std;

int block00[4][4] = { { 10,0,0,0 },{ 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 } }; //  -
int block01[4][4] = { { 11,0,1,0 },{ 0,0,1,0 },{ 0,0,1,0 },{ 0,0,1,0 } }; //  |
int block02[4][4] = { { 12,0,0,0 },{ 0,0,0,0 },{ 1,1,1,0 },{ 0,1,0,0 } }; //  L
int block03[4][4] = { { 13,0,0,0 },{ 0,1,0,0 },{ 1,1,0,0 },{ 0,1,0,0 } };
int block04[4][4] = { { 14,0,0,0 },{ 0,0,0,0 },{ 0,1,0,0 },{ 1,1,1,0 } };
int block05[4][4] = { { 15,0,0,0 },{ 0,1,0,0 },{ 0,1,1,0 },{ 0,1,0,0 } };
int block06[4][4] = { { 16,0,0,0 },{ 0,0,0,0 },{ 1,1,1,0 },{ 1,0,0,0 } };
int block07[4][4] = { { 17,0,0,0 },{ 1,1,0,0 },{ 0,1,0,0 },{ 0,1,0,0 } };
int block08[4][4] = { { 18,0,0,0 },{ 0,0,0,0 },{ 0,0,1,0 },{ 1,1,1,0 } };
int block09[4][4] = { { 19,0,0,0 },{ 0,1,0,0 },{ 0,1,0,0 },{ 0,1,1,0 } };
int block10[4][4] = { { 20,0,0,0 },{ 0,0,0,0 },{ 1,1,1,0 },{ 0,0,1,0 } };
int block11[4][4] = { { 21,0,0,0 },{ 0,1,0,0 },{ 0,1,0,0 },{ 1,1,0,0 } };
int block12[4][4] = { { 22,0,0,0 },{ 0,0,0,0 },{ 1,0,0,0 },{ 1,1,1,0 } };
int block13[4][4] = { { 23,0,0,0 },{ 0,1,1,0 },{ 0,1,0,0 },{ 0,1,0,0 } };
int block14[4][4] = { { 24,0,0,0 },{ 0,0,0,0 },{ 0,1,1,0 },{ 1,1,0,0 } };
int block15[4][4] = { { 25,0,0,0 },{ 1,0,0,0 },{ 1,1,0,0 },{ 0,1,0,0 } };
int block16[4][4] = { { 26,0,0,0 },{ 0,0,0,0 },{ 1,1,0,0 },{ 0,1,1,0 } };
int block17[4][4] = { { 27,0,0,0 },{ 0,0,1,0 },{ 0,1,1,0 },{ 0,1,0,0 } };
int block18[4][4] = { { 28,0,0,0 },{ 0,0,0,0 },{ 1,1,0,0 },{ 1,1,0,0 } };
// 函数声明
// 初始化窗口
void initialWindow(HANDLE hOut);
// 初始化界面
void initialPrint(HANDLE hOut);
// 移动光标
void gotoXY(HANDLE hOut,int x,int y);
// 随机生成方块并且打印出下一块的方块
void roundBlock(HANDLE hOut,int block[4][4]);
// 碰撞检测
bool collisionDetection(int block[4][4],int map[21][12], int x, int y);
// 清除方块
void clearBlock(HANDLE hOut,int block[4][4], int x,int y);
// 打印方块
void printBlock(HANDLE hOut,int block[4][4],int x,int y);
// 方块左移
void myLeft(HANDLE hOut,int block[4][4],int map[21][12], int x, int &y);
// 右移
void myRight(HANDLE hOut,int block[4][4],int map[21][12], int x, int &y);
// 旋转 顺时针90
void myUp(HANDLE hOut,int block[4][4],int map[21][12], int x, int &y);
// 加速下落
int myDown(HANDLE hOut,int block[4][4],int map[21][12], int &x, int y);
// 游戏暂停
void myStop(HANDLE hOut, int block[4][4]);
// 游戏结束
void gameOver(HANDLE hOut, int block[4][4], int map[21][12]);
//判断是否加分
void eliminateRow(HANDLE hOut, int map[21][12], int &val, int &fraction, int &checkpoint);


// 主函数入口
int main()
{
    int map[21][12];
    int blockA[4][4]; // 候选区的方块
    int blockB[4][4]; // 降落区
    int positionX, positionY; // X,Y坐标
    bool check; // 检测是否碰撞
    char key; // 获取键盘
    int val; // 控制下落速度
    int fraction; // 存储得分
    int checkpoint; // 存储关卡
    int times;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取输入设备
    initialWindow(hOut); // 初始化
initial:
    gotoXY(hOut,0,0);
    initialPrint(hOut);
    check = true;
    val = 50;
    fraction = 0;
    checkpoint = 1;
    times = val;
    for(int i=0;i<20;i++)
    {
        for(int j=1;j<11;j++)
        {
            map[i][j] = 0;
        }
    }
    for(int i=0;i<20;i++)
    {
        map[i][0] = map[i][11] = 1;
    }
    for(int i=0;i<12; i++)
    {
        map[20][i] = 1;
    }

    srand((unsigned)time(NULL));
    roundBlock(hOut,blockA);
    // 定义个死循环
    while(true){
        if(check){
            eliminateRow(hOut,map,val,fraction,checkpoint);
            check = false;
            positionX = -3;
            positionY = 4;
            if(collisionDetection(blockA,map,positionX,positionY))
            {
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        blockB[i][j] = blockA[i][j];
                    }
                }
                roundBlock(hOut,blockA);
            }
            else{
                gameOver(hOut,blockA,map);
                goto initial;
            }}
            printBlock(hOut, blockB, positionX, positionY);
            if(_kbhit())
            {
                key = _getch();
                switch(key)
                {
                case 72: // 上
                    myUp(hOut,blockB,map,positionX,positionY);
                    break;
                case 75: // 左
                    myLeft(hOut, blockB, map, positionX, positionY);
                    break;
                case 77: // 右
                    myRight(hOut, blockB, map, positionX, positionY);
                    break;
                case 80: // 下
                    switch (myDown(hOut, blockB, map, positionX, positionY))
                    {
                    case 0:
                        check = false;
                        break;
                    case 1:
                        check = true;
                        break;
                    case 2:
                        gameOver(hOut, blockB, map);
                        goto initial;
                    default:
                        break;
                    }
                    break;
                case 32: //stop
                    myStop(hOut,blockA);
                    break;
                case 27:
                    exit(0);
                default:
                    break;
                }
            }
            Sleep(20);
            if(0 == --times)
            {
                switch(myDown(hOut,blockB,map,positionX,positionY))
                {
                    case 0:
                        check = false;
                        break;
                    case 1:
                        check = true;
                        break;
                    case 2:
                        gameOver(hOut,blockB,map);
                        goto initial;
                    default:
                        break;

                }
                times = val;
            }
    }
    cin.get();
    return 0;
}

void initialWindow(HANDLE hOut)
{
    SetConsoleTitle("俄 罗 斯 方 块 - 1.0v - by@Lian");
    COORD size = {80,25};
    SetConsoleScreenBufferSize(hOut,size);
    // 覆盖区域 从 0,0 到 79,24 点
    SMALL_RECT rc = { 0, 0, 79, 24 };
    // 对象和内容
    SetConsoleWindowInfo(hOut, true, &rc);
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(hOut,&cursor_info);
}

// x ,y , ↓ y , → x
void initialPrint(HANDLE hOut)
{
    SetConsoleTextAttribute(hOut,FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    for(int i=0;i<20;i++)
    {
        cout << "■                    ■☆                      ☆" << endl;
    }
    gotoXY(hOut,26,0);
    cout << "☆☆☆☆☆☆☆☆☆☆☆";
    gotoXY(hOut,0,20);
    cout << "■■■■■■■■■■■■☆☆☆☆☆☆☆☆☆☆☆☆☆";
    gotoXY(hOut, 26, 1);
    cout << "分    数：      ";
    gotoXY(hOut,26,2);
    cout << "关    卡：      ";
    gotoXY(hOut,26,4);
    cout << "下一方块：";
    gotoXY(hOut,26,9);
    cout << "操作方法：";
    gotoXY(hOut,30,11);
    cout << "↑：旋转 ↓：速降";
    gotoXY(hOut,30,12);
    cout << "→：右移 ←：左移";
    gotoXY(hOut,30,13);
    cout << "空格键：开始/暂停";
    gotoXY(hOut, 30, 14);
    cout << "Esc 键：退出";
    gotoXY(hOut,26,16);
    cout << "关    于：";
    gotoXY(hOut,30,18);
    cout << "俄罗斯方块V1.0";

}

void gotoXY(HANDLE hOut, int x,int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOut,pos);
}

void roundBlock(HANDLE hOut,int block[4][4])
{
    clearBlock(hOut,block,5,15);
    switch(rand()%19)
    {
        case 0:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block00[i][j];
                }
            break;

        case 1:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block01[i][j];
                }
            break;
        case 2:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block02[i][j];
                }
            break;
        case 3:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block03[i][j];
                }
            break;
        case 4:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block04[i][j];
                }
            break;
        case 5:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block05[i][j];
                }
            break;
        case 6:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block06[i][j];
                }
            break;
        case 7:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block07[i][j];
                }
            break;
        case 8:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block08[i][j];
                }
            break;
        case 9:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block09[i][j];
                }
            break;
        case 10:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block10[i][j];
                }
            break;
        case 11:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block11[i][j];
                }
            break;
        case 12:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block12[i][j];
                }
            break;
        case 13:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block13[i][j];
                }
            break;
        case 14:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block14[i][j];
                }
            break;

        case 15:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block15[i][j];
                }
            break;
        case 16:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block16[i][j];
                }
            break;
        case 17:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block17[i][j];
                }
            break;
        case 18:
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block18[i][j];
                }
            break;
        default:
            break;
    }
    printBlock(hOut,block,5,15);
}

void clearBlock(HANDLE hOut,int block[4][4], int x,int y)
{
    // 消除对应区域的图形
    for(int i=0;i<4;i++)
    {
        if(i+x>=0)
        {
            for(int j=0;j<4;j++)
            {
                if(block[i][j]==1)
                {
                    gotoXY(hOut, 2 * (y + j), x + i);
                    cout<<"  ";
                }
            }
        }
    }
}

void printBlock(HANDLE hOut,int block[4][4], int x,int y)
{
    switch(block[0][0])
    {
        case 10:
        case 11:
            SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
            break;
        case 12:
        case 13:
        case 14:
        case 15:
            SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
            break;
        case 16:
        case 17:
        case 18:
        case 19:
            SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
            break;
        case 20:
        case 21:
        case 22:
        case 23:
            SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
            break;
        case 24:
        case 25:
            SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
            break;
        case 26:
        case 27:
            SetConsoleTextAttribute(hOut,FOREGROUND_BLUE|FOREGROUND_INTENSITY);
            break;
        case 28:
            SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_INTENSITY);
            break;
        default:
            break;
    }
    // 画到对应区域
    for(int i=0;i<4;i++)
    {
        if(i+x >=0)
        {
            for(int j=0;j<4;j++)
            {
                if(block[i][j] == 1)
                {
                    gotoXY(hOut, 2 * (y + j), x + i);
                    cout << "■";
                }
            }
        }
    }
}

bool collisionDetection(int block[4][4],int map[21][12], int x, int y)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(x+i>=0 && y +j>=0 &&map[x+i][y+j]==1 && block[i][j]==1)
            {
                return false;
            }
        }
    }
    return true;
}

void gameOver(HANDLE hOut, int block[4][4], int map[21][12])
{
    SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    gotoXY(hOut,9,8);
    cout << "GAME OVER";
    gotoXY(hOut,8,9);
    cout << "空格键：重来";
    gotoXY(hOut,8,10);
    cout << "ESC键：退出";
    char key;
    while(key)
    {
        key = _getch();
        if (key == 32)
            return ;
        if (key == 27)
            exit(0);
    }
}

int myDown(HANDLE hOut,int block[4][4],int map[21][12], int &x, int y)
{
    if(collisionDetection(block,map,x+1,y))
    {
        clearBlock(hOut,block,x,y);
        ++x;
        return 0;
    }
    if(x<0)
    {
        return 2;
    }
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(block[i][j] == 1)
            {
                map[x+i][y+j] = 1;
                SetConsoleTextAttribute(hOut,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
                gotoXY(hOut,2*(j+y),x+i);
                cout << "■";
            }
        }
    }
    // return 1太重要了 -> 返回確認已經下落下去
    return 1;
}

void myLeft(HANDLE hOut,int block[4][4],int map[21][12], int x, int &y)
{
    if(collisionDetection(block,map,x,y-1))
    {
        clearBlock(hOut,block,x,y);
        --y;
    }
}

void myRight(HANDLE hOut,int block[4][4],int map[21][12], int x, int &y)
{
    if(collisionDetection(block,map,x,y+1))
    {
        clearBlock(hOut,block,x,y);
        ++y;
    }
}

void myUp(HANDLE hOut, int block[4][4], int map[21][12], int x, int &y)
{
    switch(block[0][0])
    {
    case 10:
        if(collisionDetection(block01,map,x,y))
        {
            clearBlock(hOut,block,x,y);
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                    block[i][j] = block01[i][j];
            }
        }
        break;
    case 11:
        if(collisionDetection(block00,map,x,y))
        {
            clearBlock(hOut,block,x,y);
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                    block[i][j] = block00[i][j];
            }
        }
        else if(collisionDetection(block00,map,x,y-1))
        {
            clearBlock(hOut,block,x,y);
            for(int i=0;i<4 ;i++)
            {
                for(int j=0;j<4;j++)
                    block[i][j] = block00[i][j];
            }
            --y;
        }
        else if(collisionDetection(block00,map,x,y+1))
        {
            clearBlock(hOut,block,x,y);
            for(int i=0;i<4 ;i++)
            {
                for(int j=0;j<4;j++)
                    block[i][j] = block00[i][j];
            }
            ++y;
        }
        else if(collisionDetection(block00,map,x,y-2))
        {
            clearBlock(hOut,block,x,y);
            for(int i=0;i<4 ;i++)
            {
                for(int j=0;j<4;j++)
                    block[i][j] = block00[i][j];
            }
            y = y -2;
        }
        else if(collisionDetection(block00,map,x,y+2))
        {
            clearBlock(hOut,block,x,y);
            for(int i=0;i<4 ;i++)
            {
                for(int j=0;j<4;j++)
                    block[i][j] = block00[i][j];
            }
            y = y + 2;
        }
        break;
    case 12:
        if (collisionDetection(block03, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block03[i][j];
                }
            }
        }
        else if(collisionDetection(block03,map,x,y))
        {
            clearBlock(hOut,block,x,y);
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block03[i][j];
                }
            }
            --y;
        }
        else if(collisionDetection(block03,map,x,y+1))
        {
            clearBlock(hOut,block,x,y);
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                {
                    block[i][j] = block03[i][j];
                }
            }
            ++y;
        }
    case 13:
        if (collisionDetection(block04, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block04[i][j];
                }
            }
        }
        else if (collisionDetection(block04, map, x, y - 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block04[i][j];
                }
            }
            --y;
        }
        else if (collisionDetection(block04, map, x, y + 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block04[i][j];
                }
            }
            ++y;
        }
        break;
    case 14:
        if (collisionDetection(block05, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block05[i][j];
                }
            }
        }
        else if (collisionDetection(block05, map, x, y - 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block05[i][j];
                }
            }
            --y;
        }
        else if (collisionDetection(block05, map, x, y + 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block05[i][j];
                }
            }
            ++y;
        }
        break;
    case 15:
        if (collisionDetection(block02, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block02[i][j];
                }
            }
        }
        else if (collisionDetection(block02, map, x, y - 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block02[i][j];
                }
            }
            --y;
        }
        else if (collisionDetection(block02, map, x, y + 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block02[i][j];
                }
            }
            ++y;
        }
        break;

    case 16:
        if (collisionDetection(block07, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block07[i][j];
                }
            }
        }
        else if (collisionDetection(block07, map, x, y - 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block07[i][j];
                }
            }
            --y;
        }
        else if (collisionDetection(block07, map, x, y + 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block07[i][j];
                }
            }
            ++y;
        }
        break;
    case 17:
        if (collisionDetection(block08, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block08[i][j];
                }
            }
        }
        else if (collisionDetection(block08, map, x, y - 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block08[i][j];
                }
            }
            --y;
        }
        else if (collisionDetection(block08, map, x, y + 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block08[i][j];
                }
            }
            ++y;
        }
        break;
    case 18:
        if (collisionDetection(block09, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block09[i][j];
                }
            }
        }
        else if (collisionDetection(block09, map, x, y - 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block09[i][j];
                }
            }
            --y;
        }
        else if (collisionDetection(block09, map, x, y + 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block09[i][j];
                }
            }
            ++y;
        }
        break;
    case 19:
        if (collisionDetection(block06, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block06[i][j];
                }
            }
        }
        else if (collisionDetection(block06, map, x, y - 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block06[i][j];
                }
            }
            --y;
        }
        else if (collisionDetection(block06, map, x, y + 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block06[i][j];
                }
            }
            ++y;
        }
        break;
    case 20:
        if (collisionDetection(block11, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block11[i][j];
                }
            }
        }
        else if (collisionDetection(block11, map, x, y - 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block11[i][j];
                }
            }
            --y;
        }
        else if (collisionDetection(block11, map, x, y + 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block11[i][j];
                }
            }
            ++y;
        }
        break;
    case 21:
        if (collisionDetection(block12, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block12[i][j];
                }
            }
        }
        else if (collisionDetection(block12, map, x, y - 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block12[i][j];
                }
            }
            --y;
        }
        else if (collisionDetection(block12, map, x, y + 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block12[i][j];
                }
            }
            ++y;
        }
        break;
    case 22:
        if (collisionDetection(block13, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block13[i][j];
                }
            }
        }
        else if (collisionDetection(block13, map, x, y - 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block13[i][j];
                }
            }
            --y;
        }
        else if (collisionDetection(block13, map, x, y + 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block13[i][j];
                }
            }
            ++y;
        }
        break;
    case 23:
        if (collisionDetection(block10, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block10[i][j];
                }
            }
        }
        else if (collisionDetection(block10, map, x, y - 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block10[i][j];
                }
            }
            --y;
        }
        else if (collisionDetection(block10, map, x, y + 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block10[i][j];
                }
            }
            ++y;
        }
        break;
    case 24:
        if (collisionDetection(block15, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block15[i][j];
                }
            }
        }
        else if (collisionDetection(block15, map, x, y - 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block15[i][j];
                }
            }
            --y;
        }
        else if (collisionDetection(block15, map, x, y + 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block15[i][j];
                }
            }
            ++y;
        }
        break;
    case 25:
        if (collisionDetection(block14, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block14[i][j];
                }
            }
        }
        else if (collisionDetection(block14, map, x, y - 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block14[i][j];
                }
            }
            --y;
        }
        else if (collisionDetection(block14, map, x, y + 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block14[i][j];
                }
            }
            ++y;
        }
        break;
    case 26:
        if (collisionDetection(block17, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block17[i][j];
                }
            }
        }
        else if (collisionDetection(block17, map, x, y - 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block17[i][j];
                }
            }
            --y;
        }
        else if (collisionDetection(block17, map, x, y + 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block17[i][j];
                }
            }
            ++y;
        }
        break;
    case 27:
        if (collisionDetection(block16, map, x, y))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block16[i][j];
                }
            }
        }
        else if (collisionDetection(block16, map, x, y - 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block16[i][j];
                }
            }
            --y;
        }
        else if (collisionDetection(block16, map, x, y + 1))
        {
            clearBlock(hOut, block, x, y);
            for (int i = 0; i < 4; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    block[i][j] = block16[i][j];
                }
            }
            ++y;
        }
        break;
    default:
        break;

    }
}

void myStop(HANDLE hOut, int block[4][4])
{
    clearBlock(hOut,block,5,15);
    SetConsoleTextAttribute(hOut,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    gotoXY(hOut,30,7);
    cout << "游戏暂停";
    char key;
    while(key)
    {
        key = _getch();
        if (key == 32)
        {
            gotoXY(hOut, 30, 7);
            cout << "        ";
            printBlock(hOut, block, 5, 15);
            return;
        }
        if (key == 27)
        {
            exit(0);
        }
    }
}

void eliminateRow(HANDLE hOut, int map[21][12], int &val, int &fraction, int &checkpoint)
{
    SetConsoleTextAttribute(hOut,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    for(int i =19;i>=0;--i)
    {
        int x =0;
        for(int j=1;j<11;++j)
        {
            x+=map[i][j];
        }
        // 形成了一排
        if(x == 10)
        {
            // 分数
            fraction +=100;
            if(val >1 && fraction /1000 + 1 !=checkpoint)
            {
                checkpoint = fraction/1000 + 1;
                val -=5;
            }
            for (int m=i;m>0;--m)
            {
                for(int n=1;n<11; ++n)
                {
                    map[m][n] = map[m-1][n];
                    gotoXY(hOut,2*n,m);
                    if(map[m][n] == 1)
                    {
                        cout << "■";
                    }
                    else{
                        cout << "  ";
                    }
                }
            }
            ++i;
        }
    }
    gotoXY(hOut,36,1);
    cout << fraction;
    gotoXY(hOut,36,2);
    cout << checkpoint;
}






