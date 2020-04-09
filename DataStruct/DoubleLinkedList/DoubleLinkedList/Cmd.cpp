#include "stdafx.h"
#include "Linker.h"
#include "Cmd.h"

void Create()
{
	MyCreateList();
}

void Add()
{
	MyAddNode();
}

void Insert()
{
	MyInsertNode();
}

void Delete()
{
	MyDeleteNode();
}

void Clearn()
{
	MyClearnList();
}

void Modify()
{
	MyModifyNode();
}

void Find()
{
	MyShowNode();
}
void Show()
{
	MyShowList();
}
void Help()
{
	MyHelp();
}

void Exit()
{
	exit(0);
}

// 构建一个 Map 映射
CMD_MAP g_Cmd_Map[] = {
					{"Create", Create},
					{"Add", Add},
					{"Insert", Insert},
					{"Delete", Delete},
					{"Clearn", Clearn},
					{"Modify", Modify},
					{"Find", Find},
					{"Show", Show},
					{"Help", Help},
					{"Exit", Exit},
					{"NULL", NULL}
};

void Finally()
{
	system("title 双向链表 easy_system - v1.1.0");
	system("color 0e");

	// 直接提供帮助菜单
	Help();
	char szCmdBuf[20] = "";
	CMD_MAP *pCmdMap = NULL;
	
	while (true)
	{
		pCmdMap = g_Cmd_Map;
		cout << endl << "请输入命令:";
		cin >> szCmdBuf;
		while (true)
		{
			system("cls");
			if (0 == strcmp(szCmdBuf, pCmdMap->m_szcmd))
			{
				pCmdMap->m_pfun();
				break;
			}

			if ("NULL" == pCmdMap->m_szcmd)
			{
				cout << "您输入的命令有误，请从新输入！" << endl;
				break;
			}

			pCmdMap++;
		}

	}

}

