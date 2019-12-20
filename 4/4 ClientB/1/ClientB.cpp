#pragma once
#include "stdafx.h"
#include "Winsock2.h"
#include "WSAError.h"
#pragma comment(lib, "WS2_32.lib")
#define MSG "Hello"
using namespace std;
SOCKET  cC;

bool GetServer(
	char*   call, //[in] позывной сервера 
	short   port, //[in] номер порта сервера 
	struct sockaddr* from, //[out] указатель на SOCKADDR_IN
	int*    flen //[out] указатель на размер from 
)
{
	memset(from, 0, sizeof(flen));

	if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
		throw  SetErrorMsgText("socket:", WSAGetLastError());

	int optval = 1, timeout = 5000;
	SOCKADDR_IN all;
	all.sin_family = AF_INET;
	all.sin_port = htons(port);
	all.sin_addr.s_addr = INADDR_BROADCAST;

	
	if (setsockopt(cC, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) == SOCKET_ERROR)
		throw  SetErrorMsgText("opt:", WSAGetLastError());
	if (setsockopt(cC, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
		throw  SetErrorMsgText("opt:", WSAGetLastError());

	if (sendto(cC, call, strlen(call) + 1, NULL, (sockaddr*)&all, sizeof(all)) == SOCKET_ERROR)
		throw  SetErrorMsgText("sendto:", WSAGetLastError());

	char message[50];
	if (recvfrom(cC, message, sizeof(message), NULL, from, flen) == SOCKET_ERROR)
		if (WSAGetLastError() == WSAETIMEDOUT)
			return false;
		else
			throw  SetErrorMsgText("recvfrom:", WSAGetLastError());

	SOCKADDR_IN* addr = (SOCKADDR_IN*)from;
	cout << endl << "Server port: " << addr->sin_port;
	cout << endl << "Server IP-adress: " << inet_ntoa(addr->sin_addr);

	if (!strcmp(message, call))
	{
		cout << endl << "Server found.\n";
		return true;
	}
	else
	{
		cout << endl << "Incorrect answer from server.";
		return false;
	}

	return true;
}

int main()
{
	WSADATA wsaData;

	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw  SetErrorMsgText("Startup:", WSAGetLastError());

		SOCKADDR_IN clnt;
		int lc = sizeof(clnt);

		if (GetServer(MSG, 2000, (sockaddr*)&clnt, &lc)) cout << "Completed\n";
		else cout << "Cannnot find a server." << endl;
		if (closesocket(cC) == SOCKET_ERROR)
			throw  SetErrorMsgText("closesocket:", WSAGetLastError());
		if (WSACleanup() == SOCKET_ERROR)
			throw  SetErrorMsgText("Cleanup:", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText;
	}

	cout << endl;
	system("pause");
	return 0;
}

