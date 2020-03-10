
// project1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "project1.h"
#include "project1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cproject1Dlg 대화 상자



Cproject1Dlg::Cproject1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cproject1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cproject1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cproject1Dlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Cproject1Dlg 메시지 처리기

BOOL Cproject1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	vCap = new VideoCapture;
	vCap->open(0);
	if (!vCap->isOpened())
	{
		MessageBox(_T("카메라 연결실패!!!"));
	}


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cproject1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Cproject1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Cproject1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cproject1Dlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 영상 
	SetTimer(100, 30, NULL);
}


void Cproject1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 카메라 read
	vCap->read(iFrame);

	// 필터링 
	GaussianBlur(iFrame, filterImg, Size(5, 5), 0);

	// 이진화 
	Canny(filterImg, thersholdImg, 100, 200, 3);

	mask = getStructuringElement(MORPH_RECT, Size(3, 3));
	// 팽창 
	dilate(thersholdImg, idilate, mask, Point(-1, -1), 3);
	imshow("Dilate", idilate);

	// 침식
	erode(idilate, ierod, mask, Point(-1, -1), 3);
	imshow("Erode", ierod);

	// 라인 검출 
	vector<Vec2f> lines;

	Point pt1, pt2, pt3; 

	HoughLines(ierod, lines, 1, CV_PI / 180, 60);
	for (int i = 0; i < 3; i++)
	{
		float rho1 = lines[i][0], theta1 = lines[i][1];
		float rho2 = lines[i + 1][0], theta2 = lines[i + 1][1];

		double a = cos(theta1), b = sin(theta1);
		double x0 = a * rho1, y0 = b * rho1;

		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));

		// 교차점 찾기 
		pt3.x = (rho2 / sin(theta2) - rho1 / sin(theta1)) / (-cos(theta1) / sin(theta1) + cos(theta2) / sin(theta2));
		pt3.y = -pt3.x * cos(theta1) / sin(theta1) + rho1 / sin(theta1);

		line(iFrame, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
		circle(iFrame, pt3, 10, Scalar(0, 0, 255), -1);

	}
	imshow("iFrema3", iFrame);

	CDialogEx::OnTimer(nIDEvent);
}

