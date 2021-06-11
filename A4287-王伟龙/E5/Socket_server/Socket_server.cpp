
#include<iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;
void initialization();
int used_num=1;
typedef struct user
{
	char username[100];
	char password[100];
	char type[100];
	char is_used=false;
	char Prototal[11];

};
user users[10];
bool search_user_old(char*name)
{
	for (int i = 0; i < 10; i++)
	{
		string t1(name);
		string t2(users[i].username);
		if (t1==t2)
		{
			return true;
		}

	}
	
	return false;
	//用于检索用户身份，是否新用户，新用户则返回许可
}
void str_copy(string a, char* b)
{
	a.copy(b, a.size());

}//将数组复制到字符串

//查询是否超载
bool search_non_overload(char* A)
{
	if (used_num >= 10)
	{
		return false;
	}

	for (int i = 0; i < 10; i++)
	{
		

		if (string(users[i].Prototal) == string(A) && used_num<10  )
		{
			used_num += 1;
			return true;
		}
		
	}
	return false;
}
void iniauser()
{

	users[0].username[0] = 'A';
	users[0].username[1] = '\0';
	char A = '0';
	for (int i = 0; i < 10; i++)
	{
		users[0].password[i] = A;
		A++;
	}
	users[0].type[0] = 'A';
	users[0].is_used = true;
	users[0].Prototal[0] = '1';
	users[0].Prototal[1] = '1';
	users[0].Prototal[2] = '4';
	users[0].Prototal[3] = '5';
	users[0].Prototal[4] = '1';
	users[0].Prototal[5] = '4';
	users[0].Prototal[6] = '1';
	users[0].Prototal[7] = '9';
	users[0].Prototal[8] = '1';
	users[0].Prototal[9] = '9';


}
int main() {

	//定义必要储存字

	iniauser();
	cout << users[0].username;
	int send_len = 0;
	int recv_len = 0;
	int len = 0;
	//定义发送缓冲区和接受缓冲区
	char send_buf[100];
	char recv_buf[100];
	//定义服务端套接字，接受请求套接字
	SOCKET s_server;
	SOCKET s_accept;
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;
	SOCKADDR_IN accept_addr;
	initialization();
	//填充服务端信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(7777);
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "套接字绑定失败！" << endl;
		WSACleanup();
	}
	else {
		cout << "套接字绑定成功！" << endl;
	}
	//设置套接字为监听状态
	if (listen(s_server, SOMAXCONN) < 0) {
		cout << "设置监听状态失败！" << endl;
		WSACleanup();
	}
	else {
		cout << "设置监听状态成功！" << endl;
	}
	cout << "服务端正在监听连接，请稍候...." << endl;
	//接受连接请求
	len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR*)&accept_addr, &len);
	if (s_accept == SOCKET_ERROR) {
		cout << "连接失败！" << endl;
		WSACleanup();
		return 0;
	}
	cout << "连接建立，准备接受数据" << endl;
	//接收数据
	
		//发信用户名
		string tbd = "请输入用户名";
		str_copy(tbd, send_buf);
		send_buf[tbd.size()] = '\0';
		
		//发信检查是否成功发送
		send_len = send(s_accept, send_buf, 100, 0);
		if (send_len < 0) {
			cout << "Error1:用户名请求提交错误！" << endl;
		}
		else
		{
			cout << "log1:已发送用户名请求" << endl;
		}//发信：用户名请求
		recv_len = recv(s_accept, recv_buf, 100, 0);
		cout << recv_buf;
		//发信检查是否收到用户名
		if (recv_len < 0) {
			cout << "Error2:接受用户信息失败！" << endl;
		}
		else {
			cout << "log2:已收到用户名消息:" << recv_buf << endl;
		}//收信：接受用户名
		

		 //鉴定成分
		//判断是否新用户
		if (!search_user_old(recv_buf))
		{
			cout << "是新用户" << endl;
			string tbd5 = "请输入口令";
			str_copy(tbd5, send_buf);
			send_buf[tbd5.size()] = '\0';
			//发信检查是否成功发送
			send_len = send(s_accept, send_buf, 100, 0);
			if (send_len < 0) {
				cout << "Error5:口令请求提交错误！" << endl;
			}
			else
			{
				cout << "log5:已发送口令请求" << endl;
			}//发信：口令请求
			recv_len = recv(s_accept, recv_buf, 100, 0);
			//发信检查是否收到口令
			if (recv_len < 0) {
				cout << "Error6:接受口令信息失败！" << endl;
			}
			else {
				cout << "log6:已收到口令消息:" << recv_buf << endl;
			}//收信：接受口令
			
			//注册协议类型
			string tbd6 = "请输入协议类型（A/B）";
			str_copy(tbd6, send_buf);
			send_buf[tbd6.size()] = '\0';
			//发信检查是否成功发送
			send_len = send(s_accept, send_buf, 100, 0);
			if (send_len < 0) {
				cout << "Error7:协议请求提交错误！" << endl;
			}
			else
			{
				cout << "log7:已发送协议请求" << endl;
			}//发信：协议请求
			recv_len = recv(s_accept, recv_buf, 100, 0);
			//发信检查是否收到协议
			if (recv_len < 0) {
				cout << "Error8:接受协议信息失败！" << endl;
			}
			else {
				cout << "log8:已收到协议消息:" << recv_buf << endl;
			}//收信：接受协议
			//发信序列号给对面
			string tbd8 = "你被发放了序列号：1145141919";
			str_copy(tbd8, send_buf);
			send_buf[tbd8.size()] = '\0';
			//发信检查是否成功发送

			send_len = send(s_accept, send_buf, 100, 0);
			if (send_len < 0) {
				cout << "Error9:序列号通知提交错误！" << endl;
			}
			else
			{
				cout << "log9:已发送序列号" << endl;
			}//发信：序列号通知
			//储存序列号

		

		}

		//新用户操作分界线————————————
		//老用户操作
		else
		{
			string T3 = "已经是老用户,请登录序列号。";
			str_copy(T3, send_buf);
			send_buf[T3.size()] = '\0';
			send_len = send(s_accept, send_buf, 100, 0);

			if (send_len < 0) {
				cout << "Error5:序列号请求消息提交失败！" << endl;
			}
			else
			{
				cout << "log5:已发送序列号请求消息" << endl;

			}//发信：序列号请求

			recv_len = recv(s_accept, recv_buf, 100, 0);
			//发信检查是否收到序列号
			if (recv_len < 0) {
				cout << "Error6:接受序列号信息失败！" << endl;
			}
			else {
				cout << "log2:已收到用户序列号:" << recv_buf << endl;
			}//收信：接受用户名


			if (search_non_overload(recv_buf))
			{
				string tbd3 = "允许授权";

				str_copy(tbd3, send_buf);
				send_buf[tbd3.size()] = '\0';

				send_len = send(s_accept, send_buf, 100, 0);
				//提示授权提交失败
				if (send_len < 0) {
					cout << "Error3:授权消息提交失败！" << endl;
				}
				
				else
				{
					cout << "log3:已发送授权允许" << endl;

				}
				
			}
			//不予授权
			else

			{
				string tbd4 = "不允许授权，人数超限，或者非正确序列号";

				str_copy(tbd4, send_buf);
				send_buf[tbd4.size()] = '\0';

				send_len = send(s_accept, send_buf, 100, 0);
			}
		}

		//老用户操作终止分界线——————————————————————
		
	
	//关闭套接字
	closesocket(s_server);
	closesocket(s_accept);
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
		cout << "初始化1失败！" << endl;
	}
	else {
		cout << "初始化1成功！" << endl;
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "初始化2失败！" << endl;
		WSACleanup();
	}
	else {
		cout << "初始化2成功！" << endl;
	}
}
	//填充服务端地址信息





