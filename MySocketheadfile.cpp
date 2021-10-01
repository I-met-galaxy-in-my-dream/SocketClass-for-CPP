#include "MySockethead.h"
MySocket::MySocket()
{
	WSAStartup(MAKEWORD(2, 2), &this->wsaData);
	this->sock_1 = socket(this->af, this->type, this->protocol);
}
MySocket::MySocket(int af, int type, int protocol)
{
	this->af = af;
	this->type = type;
	this->protocol = protocol;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	this->sock_1 = socket(this->af, this->type, this->protocol);
}

MySocket::~MySocket()
{
	WSACleanup();
}

MySocket::MySocket(const MySocket& p)
{
	this->af = p.af;
	this->type = p.type;
	this->protocol = p.protocol;

	this->sock_1 = p.sock_1;
	this->sock_2 = p.sock_2;

	this->server_addr = p.server_addr;
	this->target_addr = p.target_addr;
	this->wsaData = p.wsaData;
}
int MySocket::mybind(std::string IP, int port)
{
	server_addr.sin_family = this->af;
	server_addr.sin_addr.s_addr = inet_addr(IP.c_str());
	server_addr.sin_port = htons(port);

	int rus = bind(this->sock_1, (SOCKADDR*)&this->server_addr, sizeof(SOCKADDR));
	return rus;
}
int MySocket::mylisten(int backlog)
{
	int rus = listen(this->sock_1, backlog);
	return rus;
}
void MySocket::myaccept()
{
	this->sock_2 = accept(this->sock_1, (SOCKADDR*)&this->target_addr, &this->target_addr_size);
}
std::string MySocket::myrecv(int len)
{
	char* recvdata;
	int recvlen = recv(this->sock_2, recvdata, len, 0);
	std::string temp(recvdata);
	return temp;
}
int MySocket::mysend(std::string senddata)
{
	int rus = send(sock_2, senddata.c_str(), sizeof(senddata.c_str()), 0);
	return rus;
}

void MySocket::close()
{
	closesocket(this->sock_2);
	closesocket(this->sock_1);
}

int MySocket::myconnect(std::string IP, int port)
{
	this->target_addr.sin_family = this->af;
	this->target_addr.sin_addr.s_addr = inet_addr(IP.c_str());
	this->target_addr.sin_port = htons(port);
	
	int rus = connect(this->sock_1, (SOCKADDR*)&this->target_addr, sizeof(SOCKADDR));
	return rus;
}


std::string MySocket::myrecvfrom(int len,std::string IP, int port)
{
	char* recvdata;
	int rus = recvfrom(this->sock_1, recvdata, len, 0, (SOCKADDR*)&this->target_addr, &this->target_addr_size);
	std::string temp(recvdata);
	return temp;
}
//默认发送给数据发送者
int MySocket::mysendto(std::string senddata, std::string IP = "", int port = 0)
{
	if (IP != "" && port != 0)
	{
		this->target_addr.sin_family = this->af;
		this->target_addr.sin_addr.s_addr = inet_addr(IP.c_str());
		this->target_addr.sin_port = htons(port);
	}
	int rus = sendto(this->sock_1, senddata.c_str(), sizeof(senddata.c_str()), 0, (SOCKADDR*)&this->target_addr, sizeof(SOCKADDR));
	return 0;
}