#pragma once
#ifndef MYSOCKETHEAD_H
#define MYSOCKETHEAD_H
#include <string>
#include <WinSock2.h>
#pragma comment (lib,"ws2_32.lib")
class MySocket
{
public:
	MySocket();
	MySocket(int af, int type, int protocol);
	MySocket(const MySocket& p);

	~MySocket();

	//绑定mybind()
	int mybind(std::string IP, int port);

	//监听mylisten()
	int mylisten(int backlog);

	//接收连接请求
	void myaccept();

	//连接请求
	int myconnect(std::string IP, int port);

	//发送和接收数据
	int mysend(std::string senddata);
	std::string myrecv(int len);
	
	//关闭套接字
	void close();
	
	//UDP
	int mysendto(std::string senddata, std::string IP, int port);

	std::string myrecvfrom(int len, std::string IP, int port);
	


private:
	WSADATA wsaData;
	struct sockaddr_in server_addr;
	struct sockaddr_in target_addr;
	int target_addr_size = sizeof(SOCKADDR);
	SOCKET sock_1;
	SOCKET sock_2;
	int af = AF_INET;
	int type = SOCK_STREAM;
	int protocol = IPPROTO_TCP;
	
};
#endif // !MYSOCKETHEAD_H
