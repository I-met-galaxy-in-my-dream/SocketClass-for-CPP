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

	//��mybind()
	int mybind(std::string IP, int port);

	//����mylisten()
	int mylisten(int backlog);

	//������������
	void myaccept();

	//��������
	int myconnect(std::string IP, int port);

	//���ͺͽ�������
	int mysend(std::string senddata);
	std::string myrecv(int len);
	
	//�ر��׽���
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
