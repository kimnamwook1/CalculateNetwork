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

	float Num1 = 0;
	float Num2 = 0;

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
	send(ServerSocket, SendA, sizeof(SendA), 0);
	send(ServerSocket, SendB, sizeof(SendB), 0);

	//�������� ����� ����
	char Result1[8192] = { 0, }; // ����� ���� �迭
	char Result2[8192] = { 0, };
	char Result3[8192] = { 0, };
	char Result4[8192] = { 0, };

	int RecvLength1 = recv(ServerSocket, Result1, sizeof(Result1) - 1, 0);// ���ڿ� ����� �޾Ƽ�
	int RecvLength2 = recv(ServerSocket, Result2, sizeof(Result2) - 1, 0);
	int RecvLength3 = recv(ServerSocket, Result3, sizeof(Result3) - 1, 0);
	int RecvLength4 = recv(ServerSocket, Result4, sizeof(Result4) - 1, 0);
	
	double Answer1 = 0; // �迭�� �Ǽ��� ��ȯ�� ����
	double Answer2 = 0;
	double Answer3 = 0;
	double Answer4 = 0;

	Answer1 = atof(Result1); // ���ڿ��� �Ǽ���
	Answer2 = atof(Result2);
	Answer3 = atof(Result3);
	Answer4 = atof(Result4);
	
	printf("%f\n", Answer1);
	printf("%f\n", Answer2);
	printf("%f\n", Answer3);
	printf("%f\n", Answer4);

	closesocket(ServerSocket);

	WSACleanup();

}