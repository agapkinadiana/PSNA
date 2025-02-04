#pragma once
#include "stdafx.h"
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib") 
using namespace std;
string  GetErrorMsgText(int code)    // c����������� ����� ������ 
{
	string msgText;
	char k[] = "qwertyuiop";
	switch (code)                      // �������� ���� ��������  
	{
	case WSAEINTR:          msgText = "WSAEINTR";         break;
	case WSAEACCES:         msgText = "WSAEACCES";        break;
	case WSASYSNOTREADY:          msgText = "WSASYSNOTREADY";         break;
	case WSAVERNOTSUPPORTED:          msgText = "WSAVERNOTSUPPORTED";         break;
	case WSANOTINITIALISED:          msgText = "WSANOTINITIALISED";         break;
	case WSAEDISCON:          msgText = "WSAEDISCON";         break;
	case WSATYPE_NOT_FOUND:          msgText = "WSATYPE_NOT_FOUND";         break;
	case WSAHOST_NOT_FOUND:          msgText = "WSAHOST_NOT_FOUND";         break;
	case WSATRY_AGAIN:          msgText = "WSATRY_AGAIN";         break;
	case WSANO_RECOVERY:          msgText = "WSANO_RECOVERY";         break;
	case WSANO_DATA:          msgText = "WSANO_DATA";         break;
	case WSA_INVALID_HANDLE:          msgText = "WSA_INVALID_HANDLE";         break;
	case WSA_INVALID_PARAMETER:          msgText = "WSA_INVALID_PARAMETER";         break;
	case WSA_IO_INCOMPLETE:          msgText = "WSA_IO_INCOMPLETE";         break;
	case WSA_IO_PENDING:          msgText = "WSA_IO_PENDING";         break;
	case WSA_NOT_ENOUGH_MEMORY:          msgText = "WSA_NOT_ENOUGH_MEMORY";         break;
	case WSA_OPERATION_ABORTED:          msgText = "WSA_OPERATION_ABORTED";         break;
	case WSASYSCALLFAILURE:          msgText = "WSASYSCALLFAILURE";         break;
	case WSAEFAULT:          msgText = "WSAEFAULT";         break;
	case WSAEINVAL:          msgText = "WSAEINVAL";         break;
	case WSAEMFILE:          msgText = "WSAEMFILE";         break;
	case WSAEWOULDBLOCK:          msgText = "WSAEWOULDBLOCK";         break;
	case WSAEINPROGRESS:          msgText = "WSAEINPROGRESS";         break;
	case WSAEALREADY:          msgText = "WSAEALREADY";         break;
	case WSAENOTSOCK:          msgText = "WSAENOTSOCK";         break;
	case WSAEDESTADDRREQ:          msgText = "WSAEDESTADDRREQ";         break;
	case WSAEMSGSIZE:          msgText = "WSAEMSGSIZE";         break;
	case WSAEPROTOTYPE:          msgText = "WSAEPROTOTYPE";         break;
	case WSAENOPROTOOPT:          msgText = "WSAENOPROTOOPT";         break;
	case WSAEPROTONOSUPPORT:          msgText = "WSAEPROTONOSUPPORT";         break;
	case WSAESOCKTNOSUPPORT:          msgText = "WSAESOCKTNOSUPPORT";         break;
	case WSAEOPNOTSUPP:          msgText = "WSAEOPNOTSUPP";         break;
	case WSAEPFNOSUPPORT:          msgText = "WSAEPFNOSUPPORT";         break;
	case WSAEAFNOSUPPORT:          msgText = "WSAEAFNOSUPPORT";         break;
	case WSAEADDRINUSE:          msgText = "WSAEADDRINUSE";         break;
	case WSAEADDRNOTAVAIL:          msgText = "WSAEADDRNOTAVAIL";         break;
	case WSAENETDOWN:          msgText = "WSAENETDOWN";         break;
	case WSAENETUNREACH:          msgText = "WSAENETUNREACH";         break;
	case WSAENETRESET:          msgText = "WSAENETRESET";         break;
	case WSAECONNABORTED:          msgText = "WSAECONNABORTED";         break;
	case WSAECONNRESET:          msgText = "WSAECONNRESET";         break;
	case WSAENOBUFS:          msgText = "WSAENOBUFS";         break;
	case WSAEISCONN:          msgText = "WSAEISCONN";         break;
	case WSAENOTCONN:          msgText = "WSAENOTCONN";         break;
	case WSAESHUTDOWN:          msgText = "WSAESHUTDOWN";         break;
	case WSAETIMEDOUT:          msgText = "WSAETIMEDOUT";         break;
	case WSAECONNREFUSED:          msgText = "WSAECONNREFUSED";         break;
	case WSAEHOSTDOWN:          msgText = "WSAEHOSTDOWN";         break;
	case WSAEHOSTUNREACH:          msgText = "WSAEHOSTUNREACH";         break;
	case WSAEPROCLIM:          msgText = "WSAEPROCLIM";         break;

	default:                msgText = itoa(code, k, 16);      break;
	};
	return msgText;
};

string  SetErrorMsgText(string msgText, int code)
{
	return  msgText + " " + GetErrorMsgText(code);

};
