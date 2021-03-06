// echoClient.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "hoxy_Header.h"

int main()
{
	CCmdStart MyCmd;
	CCmdStart::CmdDebugText(L"CLIENT START", true);

	SocketUtil::WSAStart();

	TCPSocket* myTcpSocket = nullptr;

	/*
	int backlogCount = 0;

	while (1)
	{
		myTcpSocket = SocketUtil::CreateTCPSocket(INET);

		SOCKADDR_IN myServerAddr;
		myServerAddr.sin_family = AF_INET;
		myServerAddr.sin_port = htons(9500);
		InetPton(AF_INET, L"127.0.0.1", &myServerAddr.sin_addr);

		int retval = myTcpSocket->Connect(&myServerAddr);
		if (retval != NO_ERROR)
		{
			break;
		}

		wcout << L"connect" << endl;

		++backlogCount;
	}

	wcout << L"backlog count : " << backlogCount << endl;
	*/

	myTcpSocket = SocketUtil::CreateTCPSocket(INET);

	SOCKADDR_IN myServerAddr;
	myServerAddr.sin_family = AF_INET;
	myServerAddr.sin_port = htons(9500);
	InetPton(AF_INET, L"127.0.0.1", &myServerAddr.sin_addr);

	int retval = myTcpSocket->Connect(&myServerAddr);
	if (retval != NO_ERROR)
	{
		CCmdStart::CmdDebugText(L"Connect", false);
	}
	CCmdStart::CmdDebugText(L"Connect", true);

	while (1)
	{
		char inputBuf[500] = { 0, };
		std::cin >> inputBuf;

		int RetVal = myTcpSocket->Send(inputBuf, strlen(inputBuf) + 1);

		int received = 0;
		char *ptr = inputBuf;
		int left = RetVal;

		while (left > 0)
		{
			received = myTcpSocket->Receive(ptr, left);
			if (received <= 0)
			{
				break;
			}

			left -= received;
			ptr += received;
		}

		std::cout << inputBuf << endl;
	}

	return 0;
}