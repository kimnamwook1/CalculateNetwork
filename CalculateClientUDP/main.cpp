#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

using namespace std;
//TCP ~ UDP

int main()
{
	//winsock init
	WSAData wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);



	//make server socket
	SOCKET RemoteSocket = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN RemoteSockAddr;
	//set server info
	memset(&RemoteSockAddr, 0, sizeof(SOCKADDR_IN));
	RemoteSockAddr.sin_family = PF_INET;
	RemoteSockAddr.sin_port = htons(1234);
	RemoteSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int RemoteSockAddrLength = sizeof(RemoteSockAddr);

	float A = 0;
	float B = 0;

	cin >> A;
	cin >> B;

	cout << "첫 번째 숫자:" << A << endl;
	cout << "두 번째 숫자:" << B << endl;

	char SendA[1024] = { 0, };
	char SendB[1024] = { 0, };
	
	sprintf(SendA, "%f", A);
	sprintf(SendB, "%f", B);

	
	//send
	sendto(RemoteSocket, SendA, sizeof(SendA), 0, (SOCKADDR*)&RemoteSockAddr, sizeof(RemoteSockAddr));
	sendto(RemoteSocket, SendB, sizeof(SendB), 0, (SOCKADDR*)&RemoteSockAddr, sizeof(RemoteSockAddr));

	char Buffer[4096] = { 0, };
	double Answer = 0; 

	recvfrom(RemoteSocket, Buffer, sizeof(Buffer), 0, (SOCKADDR*)&RemoteSockAddr, &RemoteSockAddrLength);
	
	Answer = atof(Buffer);

	printf("%f\n", Answer);

	closesocket(RemoteSocket);

	//cleanup winsock
	WSACleanup();

	return 0;
}
