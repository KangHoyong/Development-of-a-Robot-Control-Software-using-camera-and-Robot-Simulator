// ConnectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ClientTest.h"
#include "ConnectDlg.h"
#include "afxdialogex.h"


// ConnectDlg 대화 상자

IMPLEMENT_DYNAMIC(ConnectDlg, CDialogEx)

ConnectDlg::ConnectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONNECT_DLG, pParent)
{

}

ConnectDlg::~ConnectDlg()
{
}

void ConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ConnectDlg, CDialogEx)
	ON_BN_CLICKED(IDC_OK, &ConnectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ConnectDlg 메시지 처리기


void ConnectDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_IPADDRESS1, m_strAddress);

	CDialog::OnOK();
}
