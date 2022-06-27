#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#include <iostream>

using namespace std;

#pragma comment(lib,"ws2_32.lib")

//TCP ~ UDP

int main()
{
	//winsock init
	WSAData wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//make server socket
	SOCKET ServerSocket = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN ServerSockAddr;
	//set server info
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN));
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_port = htons(1234);
	ServerSockAddr.sin_addr.s_addr = INADDR_ANY;
	//socket bind ip:port
	bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));

	float RecvA = 0.0f;
	float RecvB = 0.0f;

	char RecvArrayA[4096] = { 0, };
	char RecvArrayB[4096] = { 0, };

	double SendC = 0;

	//wait for recv
	SOCKADDR_IN ClientSockAddr;                
	memset(&ClientSockAddr, 0, sizeof(SOCKADDR_IN));

	int ClientSockLength = sizeof(ClientSockAddr);

	int RecvLengthA = recvfrom(ServerSocket, RecvArrayA, sizeof(RecvArrayA), 0, (SOCKADDR*)&ClientSockAddr, &ClientSockLength);
	int RecvLengthB = recvfrom(ServerSocket, RecvArrayB, sizeof(RecvArrayB), 0, (SOCKADDR*)&ClientSockAddr, &ClientSockLength);

	RecvA = atof(RecvArrayA);
	RecvB = atof(RecvArrayB);

	SendC = RecvA * RecvB;

	char SendAnswer[4096] = { 0, };

	sprintf(SendAnswer, "%f", SendC);

	int SendLength = sendto(ServerSocket, SendAnswer, sizeof(SendAnswer), 0, (SOCKADDR*)&ClientSockAddr, sizeof(ClientSockAddr));
	//send	


	printf("%f\n", SendC);

	//cleanup winsock
	WSACleanup();

	return 0;
}