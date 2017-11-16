#include "stdafx.h"
#include "hoxy_Header.h"

BOOL SocketUtil::DomainToIP(WCHAR * szDomain, IN_ADDR * pAddr)
{
	ADDRINFOW* pAddrInfo;
	SOCKADDR_IN* pSockAddr;
	if (GetAddrInfo(szDomain, L"0", NULL, &pAddrInfo) != 0)
	{
		return FALSE;
	}
	pSockAddr = (SOCKADDR_IN*)pAddrInfo->ai_addr;
	*pAddr = pSockAddr->sin_addr;
	FreeAddrInfo(pAddrInfo);
	return TRUE;
}

bool SocketUtil::WSAStart()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		CCmdStart::CmdDebugText(L"Starting Up", false);
		return false;
	}
	return true;
}

void SocketUtil::CleanUp()
{
	WSACleanup();
}

TCPSocket* SocketUtil::CreateTCPSocket(SocketAddressFamily inFamily)
{
	SOCKET s = socket(inFamily, SOCK_STREAM, IPPROTO_TCP);

	if (s != INVALID_SOCKET)
	{
		return new TCPSocket(s);
	}
	else
	{
		CCmdStart::CmdDebugText(L"SocketUtil::CreateTCPSocket", false);
		return nullptr;
	}
}