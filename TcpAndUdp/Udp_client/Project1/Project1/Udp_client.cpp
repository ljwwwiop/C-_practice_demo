// Udp的client端

#include "stdafx.h"
#pragma comment(lib,"WS2_32")


int main()
{
	system("title UDP_Client ");
	// 初始化winsock库
	WSADATA wasData;
	WSAStartup(MAKEWORD(2,2), &wasData);

	// 创建udp socket套接字
	SOCKET sockClient = socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP);

	// 也可以和tcp一样使用bind函数绑定一个本地地址
	// 否则系统也会自动安排的

	// 填写远程地址
	SOCKADDR_IN addrClient;
	//char szbuff[20] = "127.0.0.1";
	char szbuff[20] = "";
	printf("当前IP地址 ：%s",szbuff);
	scanf("%s",szbuff);
	addrClient.sin_addr.S_un.S_addr = inet_addr(szbuff);
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(3456);

	// 这里填写服务器IP地址，如果计算机没有联网，直接使用127.0.0.1即可
	// 发送数据
	char szSendBuff[1024] = "";
	while (true)
	{
		printf(">>");
		scanf("%s", szSendBuff);
		sendto(sockClient,szSendBuff,strlen(szSendBuff)+1, 0,(SOCKADDR *)&addrClient,sizeof(SOCKADDR_IN));
	}
	closesocket(sockClient);
	WSACleanup();

	return 0;

}
