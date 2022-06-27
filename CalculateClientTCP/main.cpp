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

	cout << "ù ��° ����:" << Num1 << endl;
	cout << "�� ��° ����:" << Num2 << endl;

	char SendA[1024] = { 0, };
	char SendB[1024] = { 0, };

	//���ڿ��� �Ǽ��� ����
	sprintf(SendA, "%f", Num1);
	sprintf(SendB, "%f", Num2);

	//������ ����
	send(ServerSocket, SendA, strlen(SendA), 0);
	send(ServerSocket, SendB, strlen(SendB), 0);

	//�������� ����� ����
	char Result[1024] = { 0, }; // ����� ���� �迭 
	double Answer = 0; // �迭�� �Ǽ��� ��ȯ�� ����
	int RecvLength = recv(ServerSocket, Result, sizeof(Result) - 1, 0);// ���ڿ� ����� �޾Ƽ�
	Answer = atof(Result); // ���ڿ��� �Ǽ���

	printf("%f\n", Answer);

	closesocket(ServerSocket);

	WSACleanup();

}