#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int error;

int main(){

	int ret;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
		error = WSAGetLastError();
		MessageBox(NULL, TEXT("WSAStartup error"), TEXT("tips"), MB_OK);
		return -1;
	}

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET){
		error = WSAGetLastError();
		MessageBox(NULL, TEXT("create socket fail"), TEXT("tips"), MB_OK);
		return -1;
	}

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);//端口
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");//IP

	//给socket分配一个本地协议地址
	if (bind(s, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR){
		error = WSAGetLastError();
		MessageBox(NULL, TEXT("bind fail"), TEXT("message"), MB_OK);
		return -1;
	}

	//开始监听
	if (listen(s, SOMAXCONN) == SOCKET_ERROR){
		MessageBox(NULL, TEXT("listen fail"), TEXT("message"), MB_OK);
		return -1;
	}

	while (true){
		SOCKET s_new = accept(s, NULL, NULL);
		if (s_new == SOCKET_ERROR){
			MessageBox(NULL, TEXT("accept fail"), TEXT("tips"), MB_OK);
			break;
		}

		char buf[20000];
		memset(buf, 0, sizeof(buf));
		ret = recv(s_new, buf, sizeof(buf), 0);
		if (ret == 0 || ret == SOCKET_ERROR){
			MessageBox(NULL, TEXT("recv fail"), TEXT("tips"), MB_OK);
			break;
		}
		printf("%s\n", buf);

		scanf("%s", buf);
		if (send(s_new, buf, strlen(buf), 0) == SOCKET_ERROR){
			MessageBox(NULL, TEXT("send fail"), TEXT("tips"), MB_OK);
			break;
		}
	}

	closesocket(s);
	WSACleanup();

	system("pause");
	return 0;
}