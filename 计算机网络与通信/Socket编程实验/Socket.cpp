#pragma once
#include "winsock2.h"
#include <stdio.h>
#include <iostream>
using namespace std;

#pragma comment(lib,"ws2_32.lib")
void sendHead(char* filename, char* extname, SOCKET s);
void sendData(char* filename, SOCKET s);

void main() {
	WSADATA wsaData;
	bool first_connection = true;

	int nRc = WSAStartup(0x0202, &wsaData); //初始化Winsock
	if (nRc) {
		printf("Winsock initialization failed!\n");
		WSAGetLastError();
	}
	else if (wsaData.wVersion != 0x0202) {
		printf("Incorrect Winsock version!\n");
		WSAGetLastError();
	}
	else printf("Winsock initialization successful!\n");

	SOCKET srvSocket;
	sockaddr_in srvAddr;
	srvSocket = socket(AF_INET, SOCK_STREAM, 0);  //创建一个监听socket
	if (srvSocket != INVALID_SOCKET) printf("Socket created successfully!\n");
	else {
		printf("Socket creation failed!\n");
		WSAGetLastError();
	}
	printf("----------------------------------------------\n");

	int srvPort;
	char srvIP[20];
	char fileAddr[50], fileName[50]; //fileName为输入主目录的副本
	printf("Please enter the listening port number:"); //置IP和端口号，以及主目录路径
	scanf("%d", &srvPort);
	printf("Please enter the listening IP address:");
	scanf("%s", srvIP);
	printf("Please enter your home directory:");
	scanf("%s", fileAddr);
	printf("----------------------------------------------\n");

	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(srvPort);
	srvAddr.sin_addr.s_addr = inet_addr(srvIP);

	nRc = bind(srvSocket, (LPSOCKADDR)&srvAddr, sizeof(srvAddr));  //监听绑定
	if (nRc != SOCKET_ERROR)
		printf("Socket binding successful!\n");
	else {
		printf("Socket binding failed!\n");
		WSAGetLastError();
	}
	nRc = listen(srvSocket, 5);  //设置等待连接状态
	if (nRc != SOCKET_ERROR)
		printf("Set waiting for connection status to be successful!\n");
	else {
		printf("Failed to set waiting for connection status!\n");
		WSAGetLastError();
	}

	sockaddr_in cltAddr;
	cltAddr.sin_family = AF_INET;
	int addrLen = sizeof(cltAddr);
	while (true) {
		SOCKET cltSocket = accept(srvSocket, (LPSOCKADDR)&cltAddr, &addrLen);
		if (cltSocket != INVALID_SOCKET)
			printf("Socket successfully connected to client!\n");
		else {
			printf("Socket failed to connect to client!\n");
			WSAGetLastError();
		}
		printf("----------------------------------------------\n");
		printf("Client IP address:%s\n", inet_ntoa(cltAddr.sin_addr));
		printf("Client port number:%u\n", htons(cltAddr.sin_port));

		char rcvdata[2000] = "";
		nRc = recv(cltSocket, rcvdata, 2000, 0); //接收数据
		if (nRc != SOCKET_ERROR)
			printf("Data received successfully!\n");
		else {
			printf("Failed to receive data!\n");
			WSAGetLastError();
		}
		printf("Received %d bytes of data from client:\n %s\n", nRc, rcvdata);

		char rqtname[20] = "";  //在请求行（即第一行）获取请求的文件名
		char extname[10] = "";  //请求文件的后缀
		for (int i = 0; i < nRc; i++) {
			if (rcvdata[i] == '/') {
				for (int j = 0; j < nRc - i; j++) {
					if (rcvdata[i] != ' ') {
						rqtname[j] = rcvdata[i];
						i++;
					}
					else {
						rqtname[j + 1] = '\0';
						break;
					}
				}
				break;
			}
		}
		for (int k = 0; k < nRc; k++) {
			if (rcvdata[k] == '.') {
				for (int j = 0; j < nRc - k; j++) {
					if (rcvdata[k + 1] != ' ') {
						extname[j] = rcvdata[k + 1];
						k++;
					}
					else {
						extname[j + 1] = '\0';
						break;
					}
				}
				break;
			}
		}
		printf("----------------------------------------------\n");

		strcpy(fileName, fileAddr);
		printf("Request file name:%s\n", rqtname);
		strcat(fileName, rqtname);
		printf("Complete route:%s\n", fileName);
		sendHead(fileName, extname, cltSocket); //发送首部
		sendData(fileName, cltSocket); //发送实体
		printf("----------------------------------------------\n\n\n");

		closesocket(cltSocket);
	}

	closesocket(srvSocket);
	WSACleanup();
	return;
}

void sendHead(char* filename, char* extname, SOCKET s) {
	char content_Type[20] = ""; //设置content-type

	if (strcmp(extname, "html") == 0) strcpy(content_Type, "text/html");
	if (strcmp(extname, "gif") == 0) strcpy(content_Type, "image/gif");
	if (strcmp(extname, "jpg") == 0) strcpy(content_Type, "image/jpeg");
	if (strcmp(extname, "jpeg") == 0) strcpy(content_Type, "image/jpeg");
	if (strcmp(extname, "png") == 0) strcpy(content_Type, "image/png");

	char sendContent_Type[40] = "Content-Type: ";
	strcat(sendContent_Type, content_Type);
	strcat(sendContent_Type, "\r\n");

	const char* ok_find = "HTTP/1.1 200 OK\r\n"; //200 OK
	const char* not_find = "HTTP/1.1 404 NOT FOUND\r\n"; //404 Not Found
	const char* forbidden = "HTTP/1.1 403 FORBIDDEN\r\n"; //403 Forbidden

	if (strcmp(filename, "C:/index/private.jpg") == 0) {  //403 禁止访问
		if (send(s, forbidden, strlen(forbidden), 0) == SOCKET_ERROR) {
			printf("Failed to send!\n");
			return;
		}
		if (send(s, sendContent_Type, strlen(sendContent_Type), 0) == SOCKET_ERROR) {
			printf("Failed to send!\n");
			return;
		}
		printf("403 The client requested that access to the file be prohibited!\n");
		return;
	}

	FILE* fp = fopen(filename, "rb");
	if (fp == NULL) {                    //404 无法查找到文件
		if (send(s, not_find, strlen(not_find), 0) == SOCKET_ERROR) {
			printf("Failed to send!\n");
			return;
		}
		printf("404 The client requested file search failed!\n");
	}
	else {                                  //200 文件查找成功
		if (send(s, ok_find, strlen(ok_find), 0) == SOCKET_ERROR) {
			printf("Failed to send!\n");
			return;
		}
		printf("200 The client requested file search successfully!\n");
	}
	if (content_Type) {
		if (send(s, sendContent_Type, strlen(sendContent_Type), 0) == SOCKET_ERROR) {
			printf("Failed to send!\n");
			return;
		}
	}
	if (send(s, "\r\n", 2, 0) == SOCKET_ERROR) {
		printf("Failed to send!\n");
		return;
	}
	return;
}



void sendData(char* filename, SOCKET s) {
	FILE* fp_Data = fopen(filename, "rb");
	if (fp_Data == NULL) return;
	fseek(fp_Data, 0L, SEEK_END);
	int dataLen = ftell(fp_Data);  //计算文件字节数
	char* p = (char*)malloc(dataLen + 1);
	fseek(fp_Data, 0L, SEEK_SET);
	fread(p, dataLen, 1, fp_Data);
	if (send(s, p, dataLen, 0) == SOCKET_ERROR) {
		printf("Failed to send!\n");
	}
	return;
}