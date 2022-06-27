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

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);  //SOCK STREAM 이 TCP

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN)); // '서버속어드레스'의 '처음=0'부터 속어드레스인의 사이즈 만큼
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_port = htons(PORT);	//host to network short
	ServerSockAddr.sin_addr.s_addr = INADDR_ANY;//INET_ADDR("127.0.0.1") OR 내 IP 넣고 실행

	bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));

	listen(ServerSocket, 0);


	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(SOCKADDR_IN));
	int ClientAddrLength = sizeof(ClientSockAddr);
	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSockAddr, &ClientAddrLength);

	double A = 0.0f;
	double B = 0.0f;

	char Array1[4096] = { 0, };
	char Array2[4096] = { 0, };

	int RevLengthA = recv(ClientSocket, Array1, sizeof(Array1) - 1, 0);  //마지막 한자리는 null로 받아야 문자열이 완성되기 떄문, 빼야 error가 안난다. // 내가 받을 최대길이
	int RevLengthB = recv(ClientSocket, Array2, sizeof(Array2) - 1, 0);  //마지막 한자리는 null로 받아야 문자열이 완성되기 떄문, 빼야 error가 안난다. // 내가 받을 최대길이

	A = atof(Array1);         // 문자열을 실수로 변환하여 num1에 할당
	B = atof(Array2);

	double C = A + B;
	double D = A - B;
	double E = A * B;
	double F = A / B;
	
	char Array3[4096] = { 0, };
	char Array4[4096] = { 0, };
	char Array5[4096] = { 0, };
	char Array6[4096] = { 0, };
	
	sprintf(Array3, "%f", C);
	sprintf(Array4, "%f", D);
	sprintf(Array5, "%f", E);
	sprintf(Array6, "%f", F);

	send(ClientSocket, Array3, sizeof(Array3), 0); // 내가 보내고 싶은 길이 strlen -> 0이 nullptr
	send(ClientSocket, Array4, sizeof(Array4), 0);
	send(ClientSocket, Array5, sizeof(Array5), 0);
	send(ClientSocket, Array6, sizeof(Array6), 0);
	
	printf("%f\n", C);
	printf("%f\n", D);
	printf("%f\n", E);
	printf("%f\n", F);

	closesocket(ClientSocket);

	closesocket(ServerSocket);

	WSACleanup();
}