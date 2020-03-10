
// ClientTest.h: PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 주 기호입니다.

#include "ClientSock.h"

// CClientTestApp:
// 이 클래스의 구현에 대해서는 ClientTest.cpp을(를) 참조하세요.
//

class CClientTestApp : public CWinApp
{
public:
	void Connect(); // 서버로 접속
	void SendData(CString& strData); // 데이터 전송
	void ReceiveData(); // 데이터 수신
	void CloseChild(); // 연결된 소켓이 닫히면 호출
	void CleanUp(); // 생성된 소켓을 닫고 메모리를 해제한다. 
	ClientSock*  m_pClient; // 서버에 접속할 클라이언트 소켓 

	CClientTestApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CClientTestApp theApp;
