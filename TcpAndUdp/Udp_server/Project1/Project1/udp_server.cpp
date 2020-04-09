//下面是一个最简单的 UDP 服务器程序 UDPServer. 它运行之后，进入无限循环，监听
//4567 端口到来的 UDP 封包，如果发现就将用户数据以字符串形式打印出来。相关代码如下。

#include "stdafx.h"
#pragma comment(lib, "WS2_32")

int main()
{
	system("title UDP_Server ");
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);

	// 创建套接字
	SOCKET sockServer = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	
	if (sockServer == INVALID_SOCKET)
	{
		printf("Failed socket()\n");
	}

	// 填充sockaddr_in 结构
	SOCKADDR_IN addrServer;
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(3456);

	// 绑定一个套接字地址
	if (SOCKET_ERROR == bind(sockServer,(SOCKADDR *)&addrServer,sizeof(SOCKADDR_IN)))
	{
		printf("Failed bin()\n");
		return 0;
	}
	// 接受数据
	char szRecBuff[1024] = "";
	SOCKADDR_IN addrClient;
	// SOCKET sockClient udp 没有这个
	int len = sizeof(SOCKADDR_IN);

	while (true)
	{
		int nRecv = recvfrom(sockServer, szRecBuff, 1024, 0, (SOCKADDR *)&addrClient, &len); //接收返回总的字节数
		if (nRecv > 0)
		{
			szRecBuff[nRecv] = '\0';
			printf("接收到数据(%s):%s\n", inet_ntoa(addrClient.sin_addr), szRecBuff);
		}
	}

	// 关闭套接字
	closesocket(sockServer);
	WSACleanup();
	return 0;

}

