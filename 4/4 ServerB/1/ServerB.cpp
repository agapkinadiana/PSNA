#pragma once
#include "stdafx.h"
#include "Winsock2.h"
#include "WSAError.h"
#pragma comment(lib, "WS2_32.lib")

#define BROAD_SERVER_NAME "Hello"

using namespace std;

SOCKET sS;
SOCKADDR_IN client;



bool GetServer(char* call, short port, sockaddr* from, int* flen) //для отправки широковещательного запроса в лок сеть пересылает позывной серверу
																	//и принимает ответы
{
	memset(from, 0, sizeof(flen));
	char message[50];
	int timeout = 5000;
	int optval = 1;

	if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
		throw  SetErrorMsgText("socket:", WSAGetLastError());

	if (setsockopt(sS, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR) //По умолчанию использование  стандартного широковещательного адреса не допускается и для его применения
		//необходимо установить специальный режим использования сокета SO_BROADCAST с помощью функции setsockopt 
		throw  SetErrorMsgText("opt:", WSAGetLastError());

	if (setsockopt(sS, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(int)) == SOCKET_ERROR)
		throw  SetErrorMsgText("opt:", WSAGetLastError());

	SOCKADDR_IN all;
	all.sin_family = AF_INET;
	all.sin_port = htons(port);
	all.sin_addr.s_addr = INADDR_BROADCAST;

	cout << "Searching for other server..." << endl;

	if (sendto(sS, call, sizeof(call) + 1, NULL, (sockaddr*)&all, sizeof(all)) == SOCKET_ERROR)
		throw SetErrorMsgText("sendto:", WSAGetLastError());
	int i = 0;
	if ((i = recvfrom(sS, message, sizeof(message), NULL, from, flen)) == SOCKET_ERROR) //для ожидания отклика
		if (WSAGetLastError() == WSAETIMEDOUT)
			return true;
		else
			throw  SetErrorMsgText("recvfrom:", WSAGetLastError());
	message[i] = 0x00;
	if (!strcmp(message, call))
	{
		SOCKADDR_IN* anotherServer = (SOCKADDR_IN*) from;
		cout << "Another server found" << endl;
		cout << "Port: " << anotherServer->sin_port << endl;
		cout << "IP-adress: " << inet_ntoa(anotherServer->sin_addr) << endl;
		return false;
	}
	else
	{
		return true;
	}
}



bool  GetRequestFromClient(             //для обработки запроса клиентской программы  
	char*            name, //[in] позывной сервера - набор символов, получаемый сервером от клиента и интерпретируемый, как запрос на установку соединения
	short            port, //[in] номер просушиваемого порта 
	struct sockaddr* from, //[out] указатель на SOCKADDR_IN (содержит указатель структуры, содержащей параметры сокета клиента приславшего запрос)
	int*             flen  //[out] указатель на размер from 
)
{//зап стр
	char buf[50];
	memset(from, 0, sizeof(flen));

	SOCKADDR_IN serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);
	serv.sin_addr.s_addr = INADDR_ANY;

	if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
		throw  SetErrorMsgText("bind:", WSAGetLastError());
	int i = 0;
	if ( (i = recvfrom(sS, buf, sizeof(buf), NULL, from, flen)) == SOCKET_ERROR)
		if (WSAGetLastError() == WSAETIMEDOUT)
			return false;
		else
			throw  SetErrorMsgText("recvfrom:", WSAGetLastError());
	buf[i] = 0x00;

	SOCKADDR_IN* addr = (SOCKADDR_IN*)from;
	cout << "CONNECTED." << endl;
	cout << "Port: " << addr->sin_port << endl;
	cout << "IP-adress: " << inet_ntoa(addr->sin_addr) << endl;

	if (!strcmp(buf, name))
		return true;
	else
	{
		cout << endl << "Incorrect server name.";
		return false;
	}
}

bool PutAnswerToClient( //для подтверждения сервером  запроса  клиента на установку соединения
	char*   name, //[in] позывной сервера 
	struct sockaddr* to, //[in] указатель на SOCKADDR_IN
	int*    lto //[in] указатель на размер from 
)
{

	if ((sendto(sS, name, strlen(name) + 1, NULL, to, *lto)) == SOCKET_ERROR)
		throw  SetErrorMsgText("sendto:", WSAGetLastError());
	return true;
}



int main(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");
	WSADATA wsaData;

	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw  SetErrorMsgText("Startup:", WSAGetLastError());

		int port = 2000;
		SOCKADDR_IN from;
		int size = sizeof(from);

		if (GetServer(BROAD_SERVER_NAME, port, (sockaddr*)&from, &size))
		{
			cout << "There's no any other server." << endl;
			cout << "Waiting for clients..." << endl;

			while (true)
			{
				if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
					throw  SetErrorMsgText("socket:", WSAGetLastError());
				if (GetRequestFromClient(BROAD_SERVER_NAME, port, (sockaddr*)&from, &size))
				{
					PutAnswerToClient(BROAD_SERVER_NAME, (sockaddr*)&from, &size);
				}
				if (closesocket(sS) == SOCKET_ERROR)
					throw  SetErrorMsgText("closesocket:", WSAGetLastError());
			}
		}
		if (WSACleanup() == SOCKET_ERROR)
			throw  SetErrorMsgText("Cleanup:", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		cout << errorMsgText << endl;
	}
	system("pause");
	return 0;

}
