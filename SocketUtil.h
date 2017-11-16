#pragma once

enum SocketAddressFamily
{
	INET = AF_INET,
	INET6 = AF_INET6
};

class SocketUtil
{
public:

	static BOOL DomainToIP(WCHAR* szDomain, IN_ADDR* pAddr);

	static bool			WSAStart();
	static void			CleanUp();

	static TCPSocket*	CreateTCPSocket(SocketAddressFamily inFamily);

private:
};