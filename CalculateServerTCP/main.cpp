//TCP Server
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#include <string>

#define PORT		7
#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);  //SOCK STREAM �� TCP

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN)); // '�����Ӿ�巹��'�� 'ó��=0'���� �Ӿ�巹������ ������ ��ŭ
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_port = htons(PORT);	//host to network short
	ServerSockAddr.sin_addr.s_addr = INADDR_ANY;//INET_ADDR("127.0.0.1") OR �� IP �ְ� ����

	bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));

	listen(ServerSocket, 0);

	while (true)
	{
		SOCKADDR_IN ClientSockAddr;
		memset(&ClientSockAddr, 0, sizeof(SOCKADDR_IN));
		int ClientAddrLength = sizeof(ClientSockAddr);
		SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSockAddr, &ClientAddrLength);

		double A = 0;
		double B = 0;

		char Array1[1024] = { 0, };
		char Array2[1024] = { 0, };

		int RevLengthA = recv(ClientSocket, Array1, sizeof(Array1) - 1, 0);  //������ ���ڸ��� null�� �޾ƾ� ���ڿ��� �ϼ��Ǳ� ����, ���� error�� �ȳ���. // ���� ���� �ִ����
		int RevLengthB = recv(ClientSocket, Array2, sizeof(Array2) - 1, 0);  //������ ���ڸ��� null�� �޾ƾ� ���ڿ��� �ϼ��Ǳ� ����, ���� error�� �ȳ���. // ���� ���� �ִ����

		A = atof(Array1);         // ���ڿ��� �Ǽ��� ��ȯ�Ͽ� num1�� �Ҵ�
		B = atof(Array2);

		double C = A + B;
		char Array3[1024] = { 0, };

		sprintf(Array3, "%f", C);

		send(ClientSocket, Array3, strlen(Array3), 0); // ���� ������ ���� ���� strlen -> 0�� nullptr

		closesocket(ClientSocket);
	}
	closesocket(ServerSocket);

	WSACleanup();
}