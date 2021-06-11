﻿
#include<iostream>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
void initialization();

typedef struct user
{
	char username[100];
	char password[100];
	char type;
	char is_used;
	int user_number;
	char SP[11];
};

void str_copy(string a, char* b)
{
	a.copy(b, a.size());

}//将数组复制到字符串

int main() {
	//定义长度变量
	user A;
	A.is_used = 'N';
	int send_len = 0;
	int recv_len = 0;
	//定义发送缓冲区和接受缓冲区
	char send_buf[100];
	char recv_buf[100];
	//定义服务端套接字，接受请求套接字
	SOCKET s_server;
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;
	initialization();
	//服务端信息
	
	server_addr.sin_family = AF_INET;//使用协议类型为（TCP/IP – IPv4）
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//测试时定义为本机访问
	server_addr.sin_port = htons(7777);//端口号为7777
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);//吸收socket流判断是否链接
	if (connect(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "许可证客户端连接失败！" << endl;
		WSACleanup();
	}
	else {
		cout << "许可证客户端连接成功！" << endl;
	}

	//发送,接收数据
	while (1) {
		recv_len = recv(s_server, recv_buf, 100, 0);
		if (recv_len < 0) {
			cout << "接受失败！" << endl;

			break;
		}
		else {
			cout << "服务端链接请求:" << recv_buf << endl;
		}
		string TBD;
		cin >> TBD;
		str_copy(TBD, send_buf);
		send_buf[TBD.size()] = '\0';
		cout<<"你输入的是"<<send_buf<<"对吗？"<<endl;
		for (int i = 0;i < 100; i++)
		{
			A.username[i] = send_buf[i];
		}
		send_len = send(s_server, A.username, 100, 0);
		if (send_len < 0) {
			cout << "发送失败！" << endl;
			break;
		}
		

	}
	//关闭套接字
	closesocket(s_server);
	//释放DLL资源
	WSACleanup();
	return 0;
}
void initialization() {
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "初始化套接字库失败！" << endl;
	}
	else {
		cout << "初始化套接字库成功！" << endl;
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
	}
	else {
		cout << "套接字库版本正确！" << endl;
	}
	//填充服务端地址信息

}