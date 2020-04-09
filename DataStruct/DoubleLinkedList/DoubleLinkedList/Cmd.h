#pragma once
// Cmd 命令中去启动Linker.h 
// 主要定义一些help函数中用的方法

typedef void(*pfun)();

struct CMD_MAP
{
	const char *m_szcmd;
	pfun m_pfun;
};

void Create();
void Add();
void Insert();
void Delete();
void Clearn();
void Modify();
void Find();
void Show();
void Help();
void Exit();

void Finally();





