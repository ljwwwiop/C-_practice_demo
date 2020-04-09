// Tcp 服务端
#include "stdafx.h"
#pragma comment(lib, "WS2_32")

int main()
{
	system("title: TCP 服务器");

	// 检查协议是否可用
	WSADATA wsaData;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("error:  WSAStartup() faile...\n");
		return -1;
	}
	printf("服务器已经启动...\n");

	// 创建服务器端口套接字
	SOCKET SockSever = socket(AF_INET,SOCK_STREAM,0);

	// 建立服务端地址
	SOCKADDR_IN addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrServer.sin_port = htons(2000);

	// 绑定套接字
	if (SOCKET_ERROR == bind(SockSever,(SOCKADDR *)&addrServer,sizeof(SOCKADDR)))
	{
		printf("error: bind() fail...%d\n",WSAGetLastError());
		return -1;
	}

	// 监听
	if (SOCKET_ERROR == listen(SockSever,5))
	{
		printf("error: listen() faile ...%d\n",WSAGetLastError());
		return -1;
	}
	printf("服务器监听中...\n");

	// 初始化客户地址长度参数
	int len = sizeof(SOCKADDR);
	SOCKADDR_IN addrClient;
	char szSendBuf[2048] = "已经连接服务器成功";
	char szRecvBuf[2048] = "";

	// 等待客户连接请求，接受请求连接
	SOCKET sockAccept = accept(SockSever,(SOCKADDR *)&addrClient,&len);
	if (INVALID_SOCKET == sockAccept)
	{
		printf("error:  accept() faile...:%d\n", WSAGetLastError());
		return -1;
	}
	// 输出连接成功的客户端IP和端口号
	printf("Aeccpt client IP:[%s], port[%d]\n",inet_ntoa(addrClient.sin_addr),ntohs(addrClient.sin_port));

	// 死循环定义
	while (true)
	{
		recv(sockAccept,szRecvBuf,sizeof(szRecvBuf),0);
		printf("客户端:%s \n",szRecvBuf);
	}

	// 关闭套接字，关闭协议
	closesocket(SockSever);
	WSACleanup();
	return 0;
}

