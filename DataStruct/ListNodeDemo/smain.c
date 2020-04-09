/*
    * 主要为了简单的运用一下数据结构知识进行一下综合操作/比框架和库的运用更加高效
    * FileName main.c
    * Author 连加未
    * Description 主函数作为程序的入口
    * Version V1.0.0
*/

/* 设计高校学生管理系统
* 1、实现功能：
*    1.1、录入（添加）学生信息：学号、姓名、平时成绩和考试成绩，总评成绩。
*    1.2、查询学生成绩：输入要查询的学生的学号，查询该学生的信息并显示。
*    1.3、显示学生成绩单：按学号顺序显示学生成绩单。
*    1.4、删除学生信息：输入要删除的学生的学号，，删除该学生的信息。
*    1,5、修改学生信息：输入要修改的学生的学号，显示该学生的原有信息，
          用户输入修改后*的信息。
* 2、业务流程
* 3、实现代码
*/

/* 
*    1功能：高校学生信息管理系统
*    2著者：连加未
*    3版本：Easy - V1.0.0
*    4编写语言：C语言
*/

// 宏定义区
#define _CRT_SECURE_NO_DEPRECATE

// 头文件区
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// 全局变量
// 定义结构体
typedef struct tagStudent
{
    char Num[10]; //学号
    char Name[20]; //姓名
    double Regular_Score; //平时成绩
    double Final_Score; //期末成绩
    double Total_Score; //总评成绩
}Student;

// 构建学生链表节点
typedef struct tagNode
{
    Student Stu; //数据域存放学生信息
    struct tagNode *pNext; //指针域：指向下一个学生结点
}Node;


// 定义学生链表的头节点
Node *g_pHead = NULL;

// 全局函数声明区域
// 打印功能菜单
void Print_Menu();
// 1 录入学生信息
void Enter_Students();
// 2 查询学生信息
Node* Inquire_Students();
// 3 显示学生信息
void Display_Students();
// 4 删除学生信息
void Deleting_Students();
// 5 修改学生信息
void Amend_Students();

// 程序入口 - 主函数main
int main(int agrc,char *argv[])
{
    // 定义个死循环，维持登录状态
    while(1)
    {
        // 请屏幕
        system("CLS");

        // 打印菜单
        Print_Menu();

        char ch;
        // 控制台信息获取
        ch = _getch();

        // switch控制分支结构
        switch(ch)
        {
            case '1':
                // 1录入学生信息
                Enter_Students();
            break;
            case '2': // 2查询学生信息
            {
                Node *node = Inquire_Students();
                if(node!=NULL)
                {
                    printf("%s\t| %s\t| %0.2lf \t| %0.2lf \t| %0.2lf\t|\n",
                        node->Stu.Num,   //学号
                        node->Stu.Name,  //姓名
                        node->Stu.Regular_Score,     //平时成绩
                        node->Stu.Final_Score,   //期末成绩
                        node->Stu.Total_Score);  //总评成绩      
                }else{
                    printf("未找到学生信息！\n");
                }
                break;
            }
            case '3': // 3展示学生信息
                Display_Students();
            break;
            case '4': // 4 删除学生信息
                Deleting_Students();
            break;
            case '5': // 5 修改学生信息
                Amend_Students();
            break;
                
            case '0': // 0 退出程序
                printf("欢迎再次使用！\n");
                return 0;
            break;

            default: // 保持程序健壮性，防止按错
                printf("输入有误，请重新输入\n");
            break;
        }
        system("pause\n");
    }
    return 0;
}

// 实现全局函数
// 打印功能菜单
void Print_Menu()
{
    //清屏
    system("CLS");
    printf("=================================================\n");
    printf("===============欢迎使用高校学生管理系统==========\n");
    printf("=================================================\n");
    printf("===================请选择对应功能================\n");
    printf("=================================================\n");
    printf("=\t\t1、录入学生信息\t\t\t=\n");
    printf("=\t\t2、查询学生信息\t\t\t=\n");
    printf("=\t\t3、显示学生信息\t\t\t=\n");
    printf("=\t\t4、删除学生信息\t\t\t=\n");
    printf("=\t\t5、修改学生信息\t\t\t=\n");
    printf("=\t\t0、退出程序系统\t\t\t=\n");
    printf("=\t\t*、回车返回上层\t\t\t=\n");
    printf("=================================================\n");

    return;
}


// 1录入学生信息
// 存在一个BUG，若存入相同信息应该提示，学生信息已经存在，不可再次录入
void Enter_Students()
{
    //清屏
    system("CLS");
    printf("=================================================\n");
    printf("===============欢迎使用高校学生管理系统==========\n");
    printf("=================================================\n");
    printf("===================录入学生信息功能================\n");
    printf("=================================================\n");
    printf("\n请依次输入学生信息:\n\n|学号 \t|姓名   |平时成绩|  |期末成绩|  |总评成绩|\n");

    //定义单链表的一个结点：当前结点
    Node *p;

    //将头结点给当前结点
    p = g_pHead;

    // 把新节点插入队尾部
    while(g_pHead!=NULL && p->pNext!=NULL)
    {
        p = p->pNext;
    }

    //为新的学生元素分配一个空间
    //mallac  void*  泛类型   强制类型转换
    Node* pNewNode=(Node *)malloc(sizeof(Node));
    pNewNode->pNext = NULL;

    // 把新节点做为尾节点，或者头节点插入
    if(g_pHead==NULL)
    {
        g_pHead = pNewNode;
        p = g_pHead;
    }else{
        // p下一个节点为pNewNode
        p->pNext = pNewNode;
    }

    // 输入新的学生信息
    scanf("%s %s %lf %lf %lf", pNewNode->Stu.Num,        //学号  数组名就是数组首地址
    pNewNode->Stu.Name,                  //姓名
    &pNewNode->Stu.Regular_Score,    //平时成绩
    &pNewNode->Stu.Final_Score,      //期末成绩
    &pNewNode->Stu.Total_Score); //总评成绩

    // 待解决BUG 

    printf("\n学生信息录入系统成功！\n");

    return;
}

// 2查询学生信息
Node* Inquire_Students()
{
    //清屏
    system("CLS");
    printf("=================================================\n");
    printf("===============欢迎使用高校学生管理系统==========\n");
    printf("=================================================\n");
    printf("===================查询学生信息功能================\n");
    printf("=================================================\n");
    char Num[10]; //学号

    printf("\n请输入需要查询学生的学号：\n");
    scanf("%s",Num);

    Node  *p = g_pHead;
    printf("\n学号\t姓名\t平时成绩\t期末成绩\t总评成绩\t\n");

    // 遍历链表
    while(p!=NULL)
    {
        /*if (p->Stu.Num == Num) 字符数组不能比较
        需要字符比较      调用函数stricmp 以大小写不敏感方式比较两个串
        用法：int  stricmp( char  *str1,  char  *str2);
        返回值大于0，则str1>str2
        返回值小于0，则str1<str2
        返回值等于0，则str1=str2*/
        int ptr = _stricmp(p->Stu.Num , Num);
        // 找到学生信息
        if(ptr ==0 )
        {
            return p;
        }
        p = p->pNext;
    }

    // 遍历完没有找到
    if(p==NULL)
        return NULL;
    return NULL;
}

// 3展示学生信息
void Display_Students()
{
        //清屏
    system("CLS");
    printf("=================================================\n");
    printf("===============欢迎使用高校学生管理系统==========\n");
    printf("=================================================\n");
    printf("===================显示学生信息功能================\n");
    printf("=================================================\n");

    Node *p = g_pHead;
    // 假如链表中没有该学生存在
    if(p==NULL)
    {
        printf("没有查找到对应学生信息!\n\n");
        return;
    }
    
    // 查找到
    while(p!=NULL)
    {
        printf("%s\t|  %s\t|  %0.2lf \t| %0.2lf \t| %0.2lf\t|\n",
            p->Stu.Num,                  //学号
            p->Stu.Name,                 //姓名
            p->Stu.Regular_Score,    //平时成绩
            p->Stu.Final_Score,      //期末成绩
            p->Stu.Total_Score); //总评成绩);
        p = p->pNext;
    }
    printf("=================================================\n");
    return ;
}

// 4删除学生信息
void Deleting_Students()
{
    //清屏
    system("CLS");
    printf("=================================================\n");
    printf("===============欢迎使用高校学生管理系统==========\n");
    printf("=================================================\n");
    printf("===================删除学生信息功能================\n");
    printf("=================================================\n");
    char Num[10];  //学号
    
    printf("\n请输入需要删除学生的学号：\n");
    scanf("%s", Num);

    Node *p = g_pHead;
    // 定义个删除节点
    Node *p2=NULL;
    int  ptr = _stricmp(g_pHead->Stu.Num , Num);
    if(ptr==0)
    {
        p2 = g_pHead;
        g_pHead = g_pHead->pNext;
        // 释放内存
        free(p2);
        printf("删除学生信息成功！");
        return;
    }

    // 非头节点
    while(p->pNext!=NULL)
    {
        int  ptr = _stricmp(p->pNext->Stu.Num, Num);
        if(ptr==0)
        {
            p2 = p->pNext;
            p->pNext = p->pNext->pNext;
            // 释放内存
            free(p2);
            printf("删除学生信息成功！");
            return;
        }

        // 不成功
        if (ptr != 0)
        {
            printf("学生信息不正确，请确认学生信息！");
        }

        // 继续next
        p = p->pNext;
    }
    if(p==NULL)
        printf("没有该学生信息!\n\n");
    return ;
}

// 5修改学生信息
void Amend_Students()
{
    //清屏
    system("CLS");
    printf("=================================================\n");
    printf("===============欢迎使用高校学生管理系统==========\n");
    printf("=================================================\n");
    printf("===================修改学生信息功能================\n");
    printf("=================================================\n");
    char Num[10];  //学号

    printf("\n请输入需要删除学生的学号：\n");
    scanf("%s", Num);
    
    Node  *p = g_pHead;

    // 遍历链表
    while(p!=NULL)
    {
        int ptr = _stricmp(p->Stu.Num,Num);
        if(ptr == 0)
        {
            //显示要修改学生信息
            printf("=================================================\n");
            printf("%s\t|  %s\t|  %0.2lf \t| %0.2lf \t| %0.2lf\t|\n",
                p->Stu.Num,                  //学号
                p->Stu.Name,                 //姓名
                p->Stu.Regular_Score,    //平时成绩
                p->Stu.Final_Score,      //期末成绩
                p->Stu.Total_Score); //总评成绩);
            printf("=================================================\n");
            printf("请输入修改学生信息\n\n");   
            printf("学号\t姓名\t平时成绩\t期末成绩\t总评成绩\t\n");
            scanf("%s %s %lf %lf %lf",
                p->Stu.Num,                  //学号
                p->Stu.Name,                 //姓名
                &p->Stu.Regular_Score,   //平时成绩
                &p->Stu.Final_Score,     //期末成绩
                &p->Stu.Total_Score);    //总评成绩
            printf("修改学生信息成功！\n");
            break;                     
        }
        // next下去
        p = p->pNext;
    }
    if (p==NULL)
    {
        ("未找到学生信息，请确认学生信息！\n\n");
    }
    return ;
}

