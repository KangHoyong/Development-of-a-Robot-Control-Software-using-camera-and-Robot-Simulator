// ClientSock.cpp: 구현 파일
//

#include "pch.h"
#include "ClientTest.h"
#include "ClientSock.h"


// ClientSock

ClientSock::ClientSock()
{
}

ClientSock::~ClientSock()
{
}


// ClientSock 멤버 함수


void ClientSock::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	((CClientTestApp*)AfxGetApp())->CloseChild();// 자신과 연결된 서버의 자소켓이 닫힘

	CAsyncSocket::OnClose(nErrorCode);
}


void ClientSock::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	((CClientTestApp*)AfxGetApp())->ReceiveData(); // 데이터를 읽는다.

	CAsyncSocket::OnReceive(nErrorCode);
}
