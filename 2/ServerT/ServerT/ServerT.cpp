// ServerT.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include "Winsock2.h"               
#pragma comment(lib, "WS2_32.lib")

using namespace std;

string  GetErrorMsgText(int code)    // error text 
{
	switch (code)                      // check return code   
	{
		case WSAEINTR: return "WSAEINTR: Работа функции прервана ";
		case WSAEACCES: return "WSAEACCES: Разрешение отвергнуто";
		case WSAEFAULT:	return "WSAEFAULT: Ошибочный адрес";
		case WSAEINVAL:	return "WSAEINVAL: Ошибка в аргументе";
		case WSAEMFILE: return "WSAEMFILE: Слишком много файлов открыто";
		case WSAEWOULDBLOCK: return "WSAEWOULDBLOCK: Ресурс временно недоступен";
		case WSAEINPROGRESS: return "WSAEINPROGRESS: Операция в процессе развития";
		case WSAEALREADY: return "WSAEALREADY: Операция уже выполняется";
		case WSAENOTSOCK: return "WSAENOTSOCK: Сокет задан неправильно";
		case WSAEDESTADDRREQ: return "WSAEDESTADDRREQ: Требуется адрес расположения";
		case WSAEMSGSIZE: return "WSAEMSGSIZE: Сообщение слишком длинное";
		case WSAEPROTOTYPE: return "WSAEPROTOTYPE: Неправильный тип протокола для сокета";
		case WSAENOPROTOOPT: return "WSAENOPROTOOPT: Ошибка в опции протокола";
		case WSAEPROTONOSUPPORT: return "WSAEPROTONOSUPPORT: Протокол не поддерживается";
		case WSAESOCKTNOSUPPORT: return "WSAESOCKTNOSUPPORT: Тип сокета не поддерживается";
		case WSAEOPNOTSUPP:	return "WSAEOPNOTSUPP: Операция не поддерживается";
		case WSAEPFNOSUPPORT: return "WSAEPFNOSUPPORT: Тип протоколов не поддерживается";
		case WSAEAFNOSUPPORT: return "WSAEAFNOSUPPORT: Тип адресов не поддерживается протоколом";
		case WSAEADDRINUSE:	return "WSAEADDRINUSE: Адрес уже используется";
		case WSAEADDRNOTAVAIL: return "WSAEADDRNOTAVAIL: Запрошенный адрес не может быть использован";
		case WSAENETDOWN: return "WSAENETDOWN: Сеть отключена";
		case WSAENETUNREACH: return "WSAENETUNREACH: Сеть не достижима";
		case WSAENETRESET: return "WSAENETRESET: Сеть разорвала соединение";
		case WSAECONNABORTED: return "WSAECONNABORTED: Программный отказ связи";
		case WSAECONNRESET:	return "WSAECONNRESET: Связь восстановлена";
		case WSAENOBUFS: return "WSAENOBUFS: Не хватает памяти для буферов";
		case WSAEISCONN: return "WSAEISCONN: Сокет уже подключен";
		case WSAENOTCONN: return "WSAENOTCONN: Сокет не подключен";
		case WSAESHUTDOWN: return "WSAESHUTDOWN: Нельзя выполнить send : сокет завершил работу";
		case WSAETIMEDOUT: return "WSAETIMEDOUT: Закончился отведенный интервал  времени";
		case WSAECONNREFUSED: return "WSAECONNREFUSED: Соединение отклонено";
		case WSAEHOSTDOWN: return "WSAEHOSTDOWN: Хост в неработоспособном состоянии";
		case WSAEHOSTUNREACH: return "WSAEHOSTUNREACH: Нет маршрута для хоста";
		case WSAEPROCLIM: return "WSAEPROCLIM: Слишком много процессов";
		case WSASYSNOTREADY: return "WSASYSNOTREADY: Сеть не доступна";
		case WSAVERNOTSUPPORTED: return "WSAVERNOTSUPPORTED: Данная версия недоступна";
		case WSANOTINITIALISED:	return "WSANOTINITIALISED: Не выполнена инициализация WS2_32.DLL";
		case WSAEDISCON: return "WSAEDISCON: Выполняется отключение";
		case WSATYPE_NOT_FOUND: return "WSATYPE_NOT_FOUND: Класс не найден";
		case WSAHOST_NOT_FOUND:	return "WSAHOST_NOT_FOUND: Хост не найден";
		case WSATRY_AGAIN: return "WSATRY_AGAIN: Неавторизированный хост не найден";
		case WSANO_RECOVERY: return "WSANO_RECOVERY: Неопределенная ошибка";
		case WSANO_DATA: return "WSANO_DATA: Нет записи запрошенного типа";
		case WSA_INVALID_HANDLE: return "WSA_INVALID_HANDLE: Указанный дескриптор события с ошибкой";
		case WSA_INVALID_PARAMETER: return "WSA_INVALID_PARAMETER: Один или более параметров с ошибкой";
		case WSA_IO_INCOMPLETE:	return "WSA_IO_INCOMPLETE: Объект ввода - вывода не в сигнальном состоянии";
		case WSA_IO_PENDING: return "WSA_IO_PENDING: Операция завершится позже";
		case WSA_NOT_ENOUGH_MEMORY: return "WSA_NOT_ENOUGH_MEMORY: Не достаточно памяти";
		case WSA_OPERATION_ABORTED: return "WSA_OPERATION_ABORTED: Операция отвергнута";
		case WSASYSCALLFAILURE: return "WSASYSCALLFAILURE: Аварийное завершение системного вызова";
		default: return "**ERROR**";
	};
};
string  SetErrorMsgText(string msgText, int code)
{
	return  msgText + GetErrorMsgText(code);
};



int main()
{
	setlocale(0, "");
	SOCKET  sS;           // дескриптор сокета 
	WSADATA wsaData;
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw  SetErrorMsgText("Startup:", WSAGetLastError());
		if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET) //создание сокета
			throw  SetErrorMsgText("socket:", WSAGetLastError());
		
		SOCKADDR_IN serv;                     // параметры  сокета sS
		serv.sin_family = AF_INET;           // используется IP-адресация  
		serv.sin_port = htons(2000);          // порт 2000 перевод в сетевой
		serv.sin_addr.s_addr = INADDR_ANY;   // любой собственный IP-адрес 

		if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR) //установка параметров сокета
			throw  SetErrorMsgText("bind:", WSAGetLastError());

		if (listen(sS, SOMAXCONN) == SOCKET_ERROR) //макс длина очереди подключений, сокет доступен для подключений
			throw SetErrorMsgText("listen:", WSAGetLastError());

		SOCKET cS;	                 // сокет для обмена данными с клиентом 
		SOCKADDR_IN clnt;             // параметры  сокета клиента
		memset(&clnt, 0, sizeof(clnt)); // обнулить память
		int lclnt = sizeof(clnt);    // размер SOCKADDR_IN
		for (;;) {
			if ((cS = accept(sS, (sockaddr*)&clnt, &lclnt)) == INVALID_SOCKET) //установка соединения создание канала на стороне сервера
				throw  SetErrorMsgText("accept:", WSAGetLastError());
			cout << "Номер порта:" << ntohs(clnt.sin_port) << endl << "Адрес:" << inet_ntoa(clnt.sin_addr) << endl;

			char ibuf[50];                //буфер приёма
			int  libuf = 0, lobuf = 0;               //количество принятых/отправленных байт
			clock_t start = clock();
			for (;;) {
				if ((libuf = recv(cS, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR) //приём данных
					throw  SetErrorMsgText("recv:", WSAGetLastError());
				if (libuf == 0) break;
				cout << ibuf << endl;
				if ((lobuf = send(cS, ibuf, strlen(ibuf) + 1, NULL)) == SOCKET_ERROR)
					throw  SetErrorMsgText("send:", WSAGetLastError());
			}
			clock_t finish = clock();
			cout << "Затраченное время: " << ((float)(finish - start))/ CLOCKS_PER_SEC <<" секунд"<<endl;
		}
		if (closesocket(cS) == SOCKET_ERROR)
			throw  SetErrorMsgText("closesocket:", WSAGetLastError());
		if (closesocket(sS) == SOCKET_ERROR)
			throw  SetErrorMsgText("closesocket:", WSAGetLastError());
		if (WSACleanup() == SOCKET_ERROR) //очистка ресурсов
			throw  SetErrorMsgText("Cleanup:", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText;
	}

	system("pause");
	return 0;


}

