#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int error;

int main(){
	int ret;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
		MessageBox(NULL, TEXT("WSAStartup error"), TEXT("tips"), MB_OK);
		return -1;
	}
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET){
		MessageBox(NULL, TEXT("create socket fail"), TEXT("tips"), MB_OK);
		return -1;
	}
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);//端口
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");//IP
	//bind(s, (SOCKADDR*)&addr, sizeof(addr));

	//连接
	if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR){
		MessageBox(NULL, TEXT("connect fail"), TEXT("message"), MB_OK);
		return -1;
	}

	char buf[20000];
	int cnt = 0, i = 0;
	for ( i = 0; i < 10000; ++i) {
		if (i % 1000 == 0) {
			++cnt;
		}
		buf[i] = '0' + cnt;
	}
	buf[i-1] = '\0';
	//scanf("%s", buf);
	//发送信息
	if (send(s, buf, strlen(buf), 0) == SOCKET_ERROR){
		MessageBox(NULL, TEXT("send message fail"), TEXT("message"), MB_OK);
	}

	//接受信息
	if (recv(s, buf, sizeof(buf), 0) == SOCKET_ERROR){
		MessageBox(NULL, TEXT("recv message fail"), TEXT("message"), MB_OK);
	}
	printf("%s\n", buf);
	//关闭socket
	if (closesocket(s) == SOCKET_ERROR){
		MessageBox(NULL, TEXT("closesocket fail"), TEXT("message"), MB_OK);
	}

	WSACleanup();
	system("pause");
	return 0;
}
