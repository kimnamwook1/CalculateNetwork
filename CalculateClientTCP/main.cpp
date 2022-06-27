#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#include <iostream>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

#define PORT		7

	
int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN));
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_port = htons(PORT); //host to network short
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));

	float Num1;
	float Num2;

	cin >> Num1;
	cin >> Num2;

	cout << "첫 번째 숫자:" << Num1 << endl;
	cout << "두 번째 숫자:" << Num2 << endl;

	char SendA[1024] = { 0, };
	char SendB[1024] = { 0, };

	//문자열에 실수를 저장
	sprintf(SendA, "%f", Num1);
	sprintf(SendB, "%f", Num2);

	//서버에 전송
	send(ServerSocket, SendA, strlen(SendA), 0);
	send(ServerSocket, SendB, strlen(SendB), 0);

	//서버에서 결과를 받음
	char Result[1024] = { 0, }; // 결과를 받을 배열 
	double Answer = 0; // 배열을 실수로 변환할 변수
	int RecvLength = recv(ServerSocket, Result, sizeof(Result) - 1, 0);// 문자열 결과를 받아서
	Answer = atof(Result); // 문자열을 실수로

	printf("%f\n", Answer);

	closesocket(ServerSocket);

	WSACleanup();

}