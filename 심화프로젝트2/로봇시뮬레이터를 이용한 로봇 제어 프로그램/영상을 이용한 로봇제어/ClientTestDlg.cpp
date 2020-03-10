
// ClientTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ClientTest.h"
#include "ClientTestDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void calJacobian(Mat J, float angle[])
{

	float j11, j12, j13, j14, j15, j16;
	float j21, j22, j23, j24, j25, j26;
	float j31, j32, j33, j34, j35, j36;
	float a1, a2, a3, a4, a5, a6;
	a1 = angle[0];
	a2 = angle[1]+90. * CV_PI/180;
	a3 = angle[2];
	a4 = angle[3];
	a5 = angle[4]-90. * CV_PI/188;
	a6 = angle[5];

	j11 = 100 * cos(a1)*sin(a5) - 425 * sin(a1)*sin(a2) - 100 * sin(a6)*(sin(a5)*(cos(a4)*(cos(a2)*sin(a1)*sin(a3)
		+ cos(a3)*sin(a1)*sin(a2)) + sin(a4)*(cos(a2)*cos(a3)*sin(a1) - sin(a1)*sin(a2)*sin(a3)))
		+ cos(a1)*cos(a5)) - 100 * cos(a5)*(cos(a4)*(cos(a2)*sin(a1)*sin(a3) + cos(a3)*sin(a1)*sin(a2))
			+ sin(a4)*(cos(a2)*cos(a3)*sin(a1) - sin(a1)*sin(a2)*sin(a3))) - 100 * cos(a6)*(cos(a4)*(cos(a2)*cos(a3)*sin(a1)
				- sin(a1)*sin(a2)*sin(a3)) - sin(a4)*(cos(a2)*sin(a1)*sin(a3) + cos(a3)*sin(a1)*sin(a2)))
		- (1333 * cos(a1)) / 10 - 392 * cos(a2)*sin(a1)*sin(a3) - 392 * cos(a3)*sin(a1)*sin(a2);
	j12 = 425 * cos(a1)*cos(a2) - 100 * cos(a6)*(sin(a4)*(cos(a1)*cos(a2)*cos(a3) - cos(a1)*sin(a2)*sin(a3))
		+ cos(a4)*(cos(a1)*cos(a2)*sin(a3) + cos(a1)*cos(a3)*sin(a2))) - 100 * cos(a5)*(sin(a4)*(cos(a1)*cos(a2)*sin(a3)
			+ cos(a1)*cos(a3)*sin(a2)) - cos(a4)*(cos(a1)*cos(a2)*cos(a3) - cos(a1)*sin(a2)*sin(a3)))
		- 100 * sin(a5)*sin(a6)*(sin(a4)*(cos(a1)*cos(a2)*sin(a3) + cos(a1)*cos(a3)*sin(a2))
			- cos(a4)*(cos(a1)*cos(a2)*cos(a3) - cos(a1)*sin(a2)*sin(a3))) + 392 * cos(a1)*cos(a2)*cos(a3) - 392 * cos(a1)*sin(a2)*sin(a3);
	j13 = 392 * cos(a1)*cos(a2)*cos(a3) - 100 * cos(a6)*(sin(a4)*(cos(a1)*cos(a2)*cos(a3) - cos(a1)*sin(a2)*sin(a3))
		+ cos(a4)*(cos(a1)*cos(a2)*sin(a3) + cos(a1)*cos(a3)*sin(a2))) - 100 * sin(a5)*sin(a6)*(sin(a4)*(cos(a1)*cos(a2)*sin(a3)
			+ cos(a1)*cos(a3)*sin(a2)) - cos(a4)*(cos(a1)*cos(a2)*cos(a3) - cos(a1)*sin(a2)*sin(a3)))
		- 100 * cos(a5)*(sin(a4)*(cos(a1)*cos(a2)*sin(a3) + cos(a1)*cos(a3)*sin(a2)) - cos(a4)*(cos(a1)*cos(a2)*cos(a3) - cos(a1)*sin(a2)*sin(a3)))
		- 392 * cos(a1)*sin(a2)*sin(a3);
	j14 = -100 * cos(a5)*(sin(a4)*(cos(a1)*cos(a2)*sin(a3) + cos(a1)*cos(a3)*sin(a2)) - cos(a4)*(cos(a1)*cos(a2)*cos(a3)
		- cos(a1)*sin(a2)*sin(a3))) - 100 * cos(a6)*(sin(a4)*(cos(a1)*cos(a2)*cos(a3) - cos(a1)*sin(a2)*sin(a3))
			+ cos(a4)*(cos(a1)*cos(a2)*sin(a3) + cos(a1)*cos(a3)*sin(a2))) - 100 * sin(a5)*sin(a6)*(sin(a4)*(cos(a1)*cos(a2)*sin(a3)
				+ cos(a1)*cos(a3)*sin(a2)) - cos(a4)*(cos(a1)*cos(a2)*cos(a3) - cos(a1)*sin(a2)*sin(a3)));
	j15 = 100 * sin(a6)*(sin(a1)*sin(a5) + cos(a5)*(sin(a4)*(cos(a1)*cos(a2)*cos(a3) - cos(a1)*sin(a2)*sin(a3))
		+ cos(a4)*(cos(a1)*cos(a2)*sin(a3) + cos(a1)*cos(a3)*sin(a2)))) - 100 * sin(a5)*(sin(a4)*(cos(a1)*cos(a2)*cos(a3)
			- cos(a1)*sin(a2)*sin(a3)) + cos(a4)*(cos(a1)*cos(a2)*sin(a3) + cos(a1)*cos(a3)*sin(a2))) + 100 * cos(a5)*sin(a1);
	j16 = 100 * cos(a6)*(sin(a5)*(sin(a4)*(cos(a1)*cos(a2)*cos(a3) - cos(a1)*sin(a2)*sin(a3)) + cos(a4)*(cos(a1)*cos(a2)*sin(a3)
		+ cos(a1)*cos(a3)*sin(a2))) - cos(a5)*sin(a1)) + 100 * sin(a6)*(sin(a4)*(cos(a1)*cos(a2)*sin(a3)
			+ cos(a1)*cos(a3)*sin(a2)) - cos(a4)*(cos(a1)*cos(a2)*cos(a3) - cos(a1)*sin(a2)*sin(a3)));


	j21 = 100 * sin(a1)*sin(a5) - (1333 * sin(a1)) / 10 + 100 * sin(a6)*(sin(a5)*(sin(a4)*(cos(a1)*cos(a2)*cos(a3) - cos(a1)*sin(a2)*sin(a3))
		+ cos(a4)*(cos(a1)*cos(a2)*sin(a3) + cos(a1)*cos(a3)*sin(a2))) - cos(a5)*sin(a1)) + 100 * cos(a5)*(sin(a4)*(cos(a1)*cos(a2)*cos(a3)
			- cos(a1)*sin(a2)*sin(a3)) + cos(a4)*(cos(a1)*cos(a2)*sin(a3) + cos(a1)*cos(a3)*sin(a2)))
		- 100 * cos(a6)*(sin(a4)*(cos(a1)*cos(a2)*sin(a3) + cos(a1)*cos(a3)*sin(a2))
			- cos(a4)*(cos(a1)*cos(a2)*cos(a3) - cos(a1)*sin(a2)*sin(a3))) + 425 * cos(a1)*sin(a2)
		+ 392 * cos(a1)*cos(a2)*sin(a3) + 392 * cos(a1)*cos(a3)*sin(a2);
	j22 = 100 * cos(a5)*(cos(a4)*(cos(a2)*cos(a3)*sin(a1) - sin(a1)*sin(a2)*sin(a3)) - sin(a4)*(cos(a2)*sin(a1)*sin(a3)
		+ cos(a3)*sin(a1)*sin(a2))) - 100 * cos(a6)*(cos(a4)*(cos(a2)*sin(a1)*sin(a3) + cos(a3)*sin(a1)*sin(a2))
			+ sin(a4)*(cos(a2)*cos(a3)*sin(a1) - sin(a1)*sin(a2)*sin(a3))) + 425 * cos(a2)*sin(a1)
		+ 100 * sin(a5)*sin(a6)*(cos(a4)*(cos(a2)*cos(a3)*sin(a1) - sin(a1)*sin(a2)*sin(a3))
			- sin(a4)*(cos(a2)*sin(a1)*sin(a3) + cos(a3)*sin(a1)*sin(a2))) + 392 * cos(a2)*cos(a3)*sin(a1)
		- 392 * sin(a1)*sin(a2)*sin(a3);
	j23 = 100 * cos(a5)*(cos(a4)*(cos(a2)*cos(a3)*sin(a1) - sin(a1)*sin(a2)*sin(a3)) - sin(a4)*(cos(a2)*sin(a1)*sin(a3)
		+ cos(a3)*sin(a1)*sin(a2))) - 100 * cos(a6)*(cos(a4)*(cos(a2)*sin(a1)*sin(a3) + cos(a3)*sin(a1)*sin(a2))
			+ sin(a4)*(cos(a2)*cos(a3)*sin(a1) - sin(a1)*sin(a2)*sin(a3))) + 100 * sin(a5)*sin(a6)*(cos(a4)*(cos(a2)*cos(a3)*sin(a1)
				- sin(a1)*sin(a2)*sin(a3)) - sin(a4)*(cos(a2)*sin(a1)*sin(a3) + cos(a3)*sin(a1)*sin(a2)))
		+ 392 * cos(a2)*cos(a3)*sin(a1) - 392 * sin(a1)*sin(a2)*sin(a3);
	j24 = 100 * cos(a5)*(cos(a4)*(cos(a2)*cos(a3)*sin(a1) - sin(a1)*sin(a2)*sin(a3)) - sin(a4)*(cos(a2)*sin(a1)*sin(a3)
		+ cos(a3)*sin(a1)*sin(a2))) - 100 * cos(a6)*(cos(a4)*(cos(a2)*sin(a1)*sin(a3)
			+ cos(a3)*sin(a1)*sin(a2)) + sin(a4)*(cos(a2)*cos(a3)*sin(a1) - sin(a1)*sin(a2)*sin(a3)))
		+ 100 * sin(a5)*sin(a6)*(cos(a4)*(cos(a2)*cos(a3)*sin(a1) - sin(a1)*sin(a2)*sin(a3))
			- sin(a4)*(cos(a2)*sin(a1)*sin(a3) + cos(a3)*sin(a1)*sin(a2)));
	j25 = 100 * sin(a6)*(cos(a5)*(cos(a4)*(cos(a2)*sin(a1)*sin(a3) + cos(a3)*sin(a1)*sin(a2)) + sin(a4)*(cos(a2)*cos(a3)*sin(a1)
		- sin(a1)*sin(a2)*sin(a3))) - cos(a1)*sin(a5)) - 100 * sin(a5)*(cos(a4)*(cos(a2)*sin(a1)*sin(a3)
			+ cos(a3)*sin(a1)*sin(a2)) + sin(a4)*(cos(a2)*cos(a3)*sin(a1) - sin(a1)*sin(a2)*sin(a3)))
		- 100 * cos(a1)*cos(a5);
	j26 = 100 * cos(a6)*(sin(a5)*(cos(a4)*(cos(a2)*sin(a1)*sin(a3) + cos(a3)*sin(a1)*sin(a2))
		+ sin(a4)*(cos(a2)*cos(a3)*sin(a1) - sin(a1)*sin(a2)*sin(a3))) + cos(a1)*cos(a5))
		- 100 * sin(a6)*(cos(a4)*(cos(a2)*cos(a3)*sin(a1) - sin(a1)*sin(a2)*sin(a3)) - sin(a4)*(cos(a2)*sin(a1)*sin(a3) + cos(a3)*sin(a1)*sin(a2)));


	j31 = 0;
	j32 = 100 * cos(a6)*(cos(a4)*(sin(a2)*sin(a3) - cos(a2)*cos(a3)) + sin(a4)*(cos(a2)*sin(a3) + cos(a3)*sin(a2)))
		- 100 * cos(a5)*(cos(a4)*(cos(a2)*sin(a3) + cos(a3)*sin(a2)) - sin(a4)*(sin(a2)*sin(a3) - cos(a2)*cos(a3)))
		- 425 * sin(a2) - 392 * cos(a2)*sin(a3) - 392 * cos(a3)*sin(a2)
		- 100 * sin(a5)*sin(a6)*(cos(a4)*(cos(a2)*sin(a3) + cos(a3)*sin(a2)) - sin(a4)*(sin(a2)*sin(a3) - cos(a2)*cos(a3)));
	j33 = 100 * cos(a6)*(cos(a4)*(sin(a2)*sin(a3) - cos(a2)*cos(a3)) + sin(a4)*(cos(a2)*sin(a3) + cos(a3)*sin(a2)))
		- 100 * cos(a5)*(cos(a4)*(cos(a2)*sin(a3) + cos(a3)*sin(a2)) - sin(a4)*(sin(a2)*sin(a3)
			- cos(a2)*cos(a3))) - 392 * cos(a2)*sin(a3) - 392 * cos(a3)*sin(a2)
		- 100 * sin(a5)*sin(a6)*(cos(a4)*(cos(a2)*sin(a3) + cos(a3)*sin(a2)) - sin(a4)*(sin(a2)*sin(a3) - cos(a2)*cos(a3)));
	j34 = 100 * cos(a6)*(cos(a4)*(sin(a2)*sin(a3) - cos(a2)*cos(a3)) + sin(a4)*(cos(a2)*sin(a3) + cos(a3)*sin(a2)))
		- 100 * cos(a5)*(cos(a4)*(cos(a2)*sin(a3) + cos(a3)*sin(a2)) - sin(a4)*(sin(a2)*sin(a3)
			- cos(a2)*cos(a3))) - 100 * sin(a5)*sin(a6)*(cos(a4)*(cos(a2)*sin(a3) + cos(a3)*sin(a2))
				- sin(a4)*(sin(a2)*sin(a3) - cos(a2)*cos(a3)));
	j35 = 100 * sin(a5)*(cos(a4)*(sin(a2)*sin(a3) - cos(a2)*cos(a3))
		+ sin(a4)*(cos(a2)*sin(a3) + cos(a3)*sin(a2))) - 100 * cos(a5)*sin(a6)*(cos(a4)*(sin(a2)*sin(a3)
			- cos(a2)*cos(a3)) + sin(a4)*(cos(a2)*sin(a3) + cos(a3)*sin(a2)));
	j36 = 100 * sin(a6)*(cos(a4)*(cos(a2)*sin(a3) + cos(a3)*sin(a2)) - sin(a4)*(sin(a2)*sin(a3) - cos(a2)*cos(a3)))
		- 100 * cos(a6)*sin(a5)*(cos(a4)*(sin(a2)*sin(a3) - cos(a2)*cos(a3)) + sin(a4)*(cos(a2)*sin(a3) + cos(a3)*sin(a2)));

	J.at<float>(0, 0) = j11;
	J.at<float>(0, 1) = j12;
	J.at<float>(0, 2) = j13;
	J.at<float>(0, 3) = j14;
	J.at<float>(0, 4) = j15;
	J.at<float>(0, 5) = j16;
	J.at<float>(1, 0) = j21;
	J.at<float>(1, 1) = j22;
	J.at<float>(1, 2) = j23;
	J.at<float>(1, 3) = j24;
	J.at<float>(1, 4) = j25;
	J.at<float>(1, 5) = j26;
	J.at<float>(2, 0) = j31;
	J.at<float>(2, 1) = j32;
	J.at<float>(2, 2) = j33;
	J.at<float>(2, 3) = j34;
	J.at<float>(2, 4) = j35;
	J.at<float>(2, 5) = j36;
}

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


// CClientTestDlg 대화 상자



CClientTestDlg::CClientTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIENTTEST_DIALOG, pParent)
	, yValue(0)
	, zValue(0)
	, xValue(0)
	, saveX(0)
	, saveY(0)
	, saveZ(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, zValue);

	DDX_Control(pDX, IDC_LIST2, list1);
	DDX_Control(pDX, IDC_LIST3, list2);

	DDX_Text(pDX, IDC_EDIT1, xValue);
	DDX_Text(pDX, IDC_EDIT2, yValue);

	DDX_Text(pDX, IDC_EDIT4, saveX);
	DDX_Text(pDX, IDC_EDIT5, saveY);
	DDX_Text(pDX, IDC_EDIT6, saveZ);
}

BEGIN_MESSAGE_MAP(CClientTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CClientTestDlg::OnSend)
	ON_BN_CLICKED(IDC_CONNECT, &CClientTestDlg::OnConnect)
	ON_BN_CLICKED(IDC_BUTTON2, &CClientTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CClientTestDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CClientTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CClientTestDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CClientTestDlg 메시지 처리기

BOOL CClientTestDlg::OnInitDialog()
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

	vCap.open(0);
	if (!vCap.isOpened())
	{
		MessageBox(_T("카메라 연결실패"));
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CClientTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CClientTestDlg::OnPaint()
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
HCURSOR CClientTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClientTestDlg::OnSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	// 도형 월드 좌표계 불러오기 
	FileStorage fsRead("ceterScalePoint.yml", cv::FileStorage::READ);
	float point1x, point1y, point2x, point2y, point3x, point3y;

	fsRead["Point1x"] >> point1x;
	fsRead["Point1y"] >> point1y;

	fsRead.release();

	// 물체를 반대쪽에 놓을 x y 임이의 좌표값 
	float rePoint1x = -723.646;
	float rePoint1y = -490.549;

	robotSendlocaiotn(point1x, point1y, rePoint1x, rePoint1y);
}


void CClientTestDlg::OnConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CClientTestApp*)AfxGetApp())->Connect();
}


BOOL CClientTestDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus() == GetDlgItem(IDC_DATA))
		{
			OnSend();
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CClientTestDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 도형 중심좌표 구해서 월드좌표계 변환 
	SetTimer(101, 30, NULL);
}


void CClientTestDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 스케일 구하기 
	SetTimer(100, 30, NULL);
}

void CClientTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 실시간 영상으로 처리 
	if (nIDEvent == 100)
	{
		showCalib();
	}
	else if (nIDEvent == 101)
	{
		showMeasurement();

	}
	CDialogEx::OnTimer(nIDEvent);
}

void CClientTestDlg::showCalib()
{
	// 스케일 구하기위해서 체스판 라이브러리사용하여 실 거리값 구하기
	//체스판 
	int nBoard = 8;
	int found;

	// 체스판 가로 세로 
	int nCountW = 11;
	int nCountH = 6;
	Size imageSize;

	// 체스판 코너 점을 찾을 경우 개수가 일치 
	int nCorers = nCountW * nCountH;

	// 영상의 점들을 저장하는 리스트 
	vector < vector<Point2f>> image_points;

	// 점들 실제 3차원 좌표를 저장하는 리스트 
	vector < vector<Point2f>> object_points;

	// 체스판 코너점을 찾기
	vector<Point2f> corners;

	float D; // 실제 거리 나누기 픽셀 거리 한 값 
	float D1; // 스케일 값 

	vCap.read(iFream);
	cvtColor(iFream, iGray, COLOR_BGR2GRAY);

	imageSize = iFream.size();

	found = findChessboardCorners(iGray, Size(nCountW, nCountH), corners);

	if (found)
	{
		Point pt1, pt2;

		// 코너 x1 , x2 값 추출 
		int x1 = corners[0].x;
		int y1 = corners[0].y;
		int x2 = corners[10].x;
		int y2 = corners[10].y;

		pt1.x = x1;
		pt1.y = y1;
		pt2.x = x2;
		pt2.y = y2;

		// x1,y1 x2,y2 사이의 거리 구하기 픽셀상
		float d = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));

		// 0.0 ~ 10.10 까지 실거리 측정하면 200MM 

		// 스케일 10칸에 한 실제 거리값 
		float a = 200; // 실거리 측정값 

		// 실거리 측정값 / 픽셀상의 거리 나누어서 스케일 값 구하기 
		D = a / d;

		// 스케일 값을 이용하여 거리 측정 = 스케일 (D1)
		D1 = d * D;

		string text;
		text = "Scale:" + to_string(D); 
		putText(iFream, text, Point(30,30), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
		line(iFream, pt1, pt2, Scalar(55, 100, 200), 1, LINE_AA);

	}
	imshow("result", iFream);

	// 스케일 값 저장 
	FileStorage fs;
	fs.open("intricsics.yml", FileStorage::WRITE);
	fs << "Scale" << D;
	fs.release();

}
void CClientTestDlg::showMeasurement()
{
	// 측정 
	vCap.read(iFream);
	cvtColor(iFream, iGray, COLOR_BGR2GRAY);

	Mat ICanny;
	Moments mmt;

	threshold(iGray, ICanny, 50, 255, THRESH_BINARY);

	// 팽창 침식 열기
	//morphologyEx(ICanny, ICanny, MORPH_OPEN, getStructuringElement(MORPH_OPEN, Size(3, 3)));
	//morphologyEx(ICanny, ICanny, MORPH_DILATE, getStructuringElement(MORPH_DILATE, Size(3, 3)), Point(-1, -1), 1);
	//morphologyEx(ICanny, ICanny, MORPH_ERODE, getStructuringElement(MORPH_ERODE, Size(5, 5)), Point(-1, -1), 1);

	cv::imshow("Canny", ICanny);

	vector<vector<Point>> contours;

	// 코너 검출 
	findContours(ICanny, contours, RETR_LIST, CHAIN_APPROX_NONE);
	vector<Point2f> approx;
	vector<Point> center1;


	Mat dst;
	dst = iFream.clone();

	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02, true);
		if (fabs(contourArea(Mat(approx))) > 500 && fabs(contourArea(Mat(approx))) < 7000)
		{
			int size = approx.size();

			String text;
			mmt = moments(approx);

			Point center(mmt.m10 / mmt.m00, mmt.m01 / mmt.m00);
			circle(dst, center, 5, Scalar(0, 255, 255), 3);

			// 각 도형 및 A4 사이즈의 Area 값을 출력해서 확인용 코드 
			//text = "Area:" + to_string(contourArea(Mat(approx)));
			//putText(dst, text, center+Point(10,10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);

			center1.push_back(center);


			// 근사화 직선을 그린다. 
			if (size % 2 == 0) {
				line(dst, approx[0], approx[approx.size() - 1], Scalar(255, 0, 0), 3);

				for (int k = 0; k < size - 1; k++)
					line(dst, approx[k], approx[k + 1], Scalar(255, 0, 0), 3);

				for (int k = 0; k < size; k++)
					circle(dst, approx[k], 3, Scalar(0, 255, 255));
			}
			else {
				line(dst, approx[0], approx[approx.size() - 1], Scalar(255, 0, 0), 2);

				for (int k = 0; k < size - 1; k++)
					line(dst, approx[k], approx[k + 1], Scalar(255, 0, 0), 2);

				for (int k = 0; k < size; k++)
					circle(dst, approx[k], 3, Scalar(0, 255, 255), FILLED);
			}
		}
	}
	string text;
	Point pt1, pt2, pt3;

	// contours.size() > 3 -> 도형이 3개 이므로 도형 백터 저장값이 3개일 경우 그 좌표 포인터를 얻기위해서 
	// 영상이 출력될때 처음 백터에 쓰레기 값이 들어가는 경우가 발생하여 딱 3개 잡은경우만 백터에 넣는 방식
	if (contours.size() > 3) {
		pt1 = center1[0];
		pt2 = center1[1];
		pt3 = center1[2];

		// 스케일 값 가져오기 
		FileStorage fsFrontRead("intricsics.yml", cv::FileStorage::READ);
		float scaleReuslt;
		fsFrontRead["Scale"] >> scaleReuslt;
		fsFrontRead.release();

		//text = "scale x:" + to_string(scaleReuslt);
		//putText(dst, text, Point(100, 100), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
		text = "center Point1 x:" + to_string(pt1.x) + "y:" + to_string(pt1.y);
		putText(dst, text, pt1, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
		text = "center Point2 x:" + to_string(pt2.x) + "y:" + to_string(pt2.y);
		putText(dst, text, pt2, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
		text = "center Point3 x:" + to_string(pt3.x) + "y:" + to_string(pt3.y);
		putText(dst, text, pt3, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);

		// 픽셀상의 중심 좌표를 실제 xy 값으로 변환 데이터 저장
		FileStorage fsStorage;
		fsStorage.open("ceterScalePoint.yml", FileStorage::WRITE);
		fsStorage << "Point1x" << pt1.x * scaleReuslt;
		fsStorage << "Point1y" << pt1.y * scaleReuslt;
		fsStorage << "Point2x" << pt2.x * scaleReuslt;
		fsStorage << "Point2y" << pt2.y * scaleReuslt;
		fsStorage << "Point3x" << pt3.x * scaleReuslt;
		fsStorage << "Point3y" << pt3.y * scaleReuslt;

		fsStorage.release();

	}
	else if (contours.size() > 2) {
		pt1 = center1[0];
		text = "center Point x:" + to_string(pt1.x) + "y:" + to_string(pt1.y);
		//putText(dst, text, Point(90, 90), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 255), 1);
	}

	/*
	string text;

	FileStorage fsFrontRead("intricsics.yml", cv::FileStorage::READ);
	float tempTimeRead;
	fsFrontRead["Scale"] >> tempTimeRead;
	fsFrontRead.release();

	//int a = stoi(tempTimeRead);

	text = "scale x:" + to_string(tempTimeRead);
	putText(dst, text, Point(100, 100), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255), 1);
	*/
	cv::imshow("result", dst);
}


void CClientTestDlg::robotSendlocaiotn(float x, float y, float reX, float reY)
{
	// 좌표값을 가져와서 계산 하는방식 

	UpdateData(true);

	float xw, yw, zw;
	float tx, ty, tz;
	float xc, yc, zc;
	float point1x = x;
	float point1y = y;

	// 도형의 좌표 위치 
	xc = point1x;
	yc = point1y;
	zc = 0.0;

	// 사용자로 부터 받은 작업대 위치 
	tx = xValue;
	ty = yValue;
	tz = zValue;

	// 도형의 좌표를 listbox 찍기 
	xCam, yCam, zCam;
	xCam.Format(_T("%f"), xc);
	yCam.Format(_T("%f"), yc);
	zCam.Format(_T("%f"), zc);

	list2.AddString("x:" + xCam + "y:" + yCam + "z:" + zCam);

	/*
	매트랩 식 
	-> 목표 위치 x축 180회 전 변환
	*/
	xw = tx + xc;
	yw = ty + yc * cos(180 * CV_PI / 180) - zc * sin(180 * CV_PI / 180);
	zw = tz + zc * cos(180 * CV_PI / 180) + yc * sin(180 * CV_PI / 180);

	// 월드좌표계 <- 가고 싶은 위치 
	float location1x, location1y, location1z;

	// 가고 싶은 위치 
	location1x = xw;
	location1y = yw;
	location1z = zw;

	// 출력 
	CString  x1, y1, z1;
	x1.Format(_T("%f"), location1x);
	y1.Format(_T("%f"), location1y);
	z1.Format(_T("%f"), location1z);

	list1.AddString("x:" + x1 + "y:" + y1 + "z:" + z1);

	Mat J = Mat(3, 6, CV_32FC1);
	float *angle = new float[6];

	// 조인트 초기 
	angle[0] = 0;
	angle[1] = -90 * CV_PI / 180;
	angle[2] = 90 * CV_PI / 180;
	angle[3] = -90 * CV_PI / 180;
	angle[4] = -90 * CV_PI / 180;
	angle[5] = 0;

	// 로봇의 현재 좌표계 델포이 상에서 위치 (월드 좌표계 기준)

	// 10번 반복 
	for (int i = 0; i < 100; i++)
	{
		calJacobian(J, angle);

		Mat J_t = J.t();
		Mat J_1 = (J * J_t).inv();

		Mat ang(6, 1, CV_32FC1);
		Vec3f pt;

		// 목표 위치 - 로봇 위치 

		pt[0] = (location1x - 400.801) / 100.0;
		pt[1] = (location1y - -44.676) / 100.0;
		pt[2] = (location1z - 337.711) / 100.0;

		ang = J_t * J_1  * pt;

		// 원래 + 증분 
		for (int j = 0; j < 6; j++)
		{
			angle[j] = angle[j] + ang.at<float>(j, 0);
		}

	}

	CString strData;
	//GetDlgItemText(IDC_DATA, strData);
	strData.Format("[ %f, %f, %f, %f, %f, %f ]",
		angle[0] * 180.0 / 3.141592,
		angle[1] * 180.0 / 3.141592,
		angle[2] * 180.0 / 3.141592,
		angle[3] * 180.0 / 3.141592,
		angle[4] * 180.0 / 3.141592,
		angle[5] * 180.0 / 3.141592);


	((CClientTestApp*)AfxGetApp())->SendData(strData);
	SetDlgItemText(IDC_DATA, "");
	
	Sleep(1000);

	float *angleVale = new float[6];
	angleVale[0] = angle[0] * 180.0 / 3.141592;
	angleVale[1] = angle[1] * 180.0 / 3.141592;
	angleVale[2] = angle[2] * 180.0 / 3.141592;
	angleVale[3] = angle[3] * 180.0 / 3.141592;
	angleVale[4] = angle[4] * 180.0 / 3.141592;
	angleVale[5] = angle[5] * 180.0 / 3.141592;

	Mat B = Mat(3, 6, CV_32FC1);
	float *angle1 = new float[6];

	// 이전 위치 조인트 
	angle1[0] = angleVale[0] * CV_PI / 180;
	angle1[1] = angleVale[1] * CV_PI / 180;
	angle1[2] = angleVale[2] * CV_PI / 180;
	angle1[3] = angleVale[3] * CV_PI / 180;
	angle1[4] = angleVale[4] * CV_PI / 180;
	angle1[5] = angleVale[5] * CV_PI / 180;

	//원하는 목표 위치 를 100번 쪼개기
	for (int i = 0; i < 100; i++)
	{
		calJacobian(B, angle1);

		Mat J_t1 = B.t();
		Mat J_11 = (B * J_t1).inv();

		Mat ang1(6, 1, CV_32FC1);
		Vec3f pt1;

		//	// 목표 위치 - 로봇 위치 
		pt1[0] = (400.801 - location1x) / 100.0;
		pt1[1] = (-44.671 - location1y) / 100.0;
		pt1[2] = (337.711 - location1z) / 100.0;

		ang1 = J_t1 * J_11  * pt1;

		//	// 원래 + 증분 
		for (int j = 0; j < 6; j++)
		{
			angle1[j] = angle1[j] + ang1.at<float>(j, 0);
		}

	}

	CString strData2;
	//GetDlgItemText(IDC_DATA, strData);
	strData2.Format("[ %f, %f, %f, %f, %f, %f ]",
		angle1[0] * 180.0 / 3.141592,
		angle1[1] * 180.0 / 3.141592,
		angle1[2] * 180.0 / 3.141592,
		angle1[3] * 180.0 / 3.141592,
		angle1[4] * 180.0 / 3.141592,
		angle1[5] * 180.0 / 3.141592);


	((CClientTestApp*)AfxGetApp())->SendData(strData2);
	SetDlgItemText(IDC_DATA, "");

	
	Sleep(1000);

	// 저장고 위치에 물체를 놓기 위한 작업 

	float xw1, yw1, zw1;
	float tx1, ty1, tz1;
	float xc1, yc1, zc1;
	float rePoint1x = reX;
	float rePoint1y = reY;

	// 저장고 위치에 물체를 놓기 좌표값 
	xc1 = rePoint1x;
	yc1 = rePoint1y;
	zc1 = 0.0;

	// 사용자로 부터 받은 작업대 위치 
	tx1 = saveX;
	ty1 = saveY;
	tz1 = saveZ;

	// 도형의 좌표를 listbox 찍기 
	CString xCam1, yCam1, zCam1;
	xCam1.Format(_T("%f"), xc1);
	yCam1.Format(_T("%f"), yc1);
	zCam1.Format(_T("%f"), zc1);

	// sx - > save 작업대 물체를 놓아야하는 위치 
	list2.AddString("sx:" + xCam1 + "sy:" + yCam1 + "sz:" + zCam1);

	xw1 = tx1 + xc1;
	yw1 = ty1 + yc1 * cos(180 * CV_PI / 180) - zc1 * sin(180 * CV_PI / 180);
	zw1 = tz1 + zc1 * cos(180 * CV_PI / 180) + yc1 * sin(180 * CV_PI / 180);

	// 월드좌표계 <- 가고 싶은 위치 
	float reLocation1x, reLocation1y, reLocation1z;

	// 가고 싶은 위치 
	reLocation1x = xw1;
	reLocation1y = yw1;
	reLocation1z = zw1;

	// 출력 
	CString  reLocaiotnX, reLocationY, reLocationZ;
	reLocaiotnX.Format(_T("%f"), reLocation1x);
	reLocationY.Format(_T("%f"), reLocation1y);
	reLocationZ.Format(_T("%f"), reLocation1z);

	list1.AddString("re x:" + reLocaiotnX + "re y:" + reLocationY + "re z:" + reLocationZ);

	float *angleVale2 = new float[6];
	angleVale2[0] = angle1[0] * 180.0 / 3.141592;
	angleVale2[1] = angle1[1] * 180.0 / 3.141592;
	angleVale2[2] = angle1[2] * 180.0 / 3.141592;
	angleVale2[3] = angle1[3] * 180.0 / 3.141592;
	angleVale2[4] = angle1[4] * 180.0 / 3.141592;
	angleVale2[5] = angle1[5] * 180.0 / 3.141592;

	Mat C = Mat(3, 6, CV_32FC1);
	float *angle3 = new float[6];

	// 이전 위치 조인트 
	angle3[0] = angleVale2[0] * CV_PI / 180;
	angle3[1] = angleVale2[1] * CV_PI / 180;
	angle3[2] = angleVale2[2] * CV_PI / 180;
	angle3[3] = angleVale2[3] * CV_PI / 180;
	angle3[4] = angleVale2[4] * CV_PI / 180;
	angle3[5] = angleVale2[5] * CV_PI / 180;

	//원하는 목표 위치 를 100번 쪼개기
	for (int i = 0; i < 100; i++)
	{
		calJacobian(C, angle3);

		Mat J_t3 = C.t();
		Mat J_13 = (C * J_t3).inv();

		Mat ang3(6, 1, CV_32FC1);
		Vec3f pt3;

		//	// 목표 위치 - 로봇 위치 
		pt3[0] = (reLocation1x - 400.801) / 100.0;
		pt3[1] = (reLocation1y - -44.676) / 100.0;
		pt3[2] = (reLocation1z - 337.711) / 100.0;
		ang3 = J_t3 * J_13  * pt3;

		//	// 원래 + 증분 
		for (int j = 0; j < 6; j++)
		{
			angle3[j] = angle3[j] + ang3.at<float>(j, 0);
		}

	}

	CString strData3;
	//GetDlgItemText(IDC_DATA, strData);
	strData3.Format("[ %f, %f, %f, %f, %f, %f ]",
		angle3[0] * 180.0 / 3.141592,
		angle3[1] * 180.0 / 3.141592,
		angle3[2] * 180.0 / 3.141592,
		angle3[3] * 180.0 / 3.141592,
		angle3[4] * 180.0 / 3.141592,
		angle3[5] * 180.0 / 3.141592);


	((CClientTestApp*)AfxGetApp())->SendData(strData3);
	SetDlgItemText(IDC_DATA, "");
	
	Sleep(1000);

	// 원래의 기존 값으로 돌아가는 코드 
	float *angleVale3 = new float[6];
	angleVale3[0] = angle3[0] * 180.0 / 3.141592;
	angleVale3[1] = angle3[1] * 180.0 / 3.141592;
	angleVale3[2] = angle3[2] * 180.0 / 3.141592;
	angleVale3[3] = angle3[3] * 180.0 / 3.141592;
	angleVale3[4] = angle3[4] * 180.0 / 3.141592;
	angleVale3[5] = angle3[5] * 180.0 / 3.141592;

	Mat D = Mat(3, 6, CV_32FC1);
	float *angle4 = new float[6];

	// 이전 위치 조인트 
	angle4[0] = angleVale3[0] * CV_PI / 180;
	angle4[1] = angleVale3[1] * CV_PI / 180;
	angle4[2] = angleVale3[2] * CV_PI / 180;
	angle4[3] = angleVale3[3] * CV_PI / 180;
	angle4[4] = angleVale3[4] * CV_PI / 180;
	angle4[5] = angleVale3[5] * CV_PI / 180;

	//원하는 목표 위치 를 100번 쪼개기
	for (int i = 0; i < 100; i++)
	{
		calJacobian(D, angle4);

		Mat J_t4 = D.t();
		Mat J_14 = (D * J_t4).inv();

		Mat ang4(6, 1, CV_32FC1);
		Vec3f pt4;

		//	// 목표 위치 - 로봇 위치 
		pt4[0] = (400.801 - reLocation1x) / 100.0;
		pt4[1] = (-44.671 - reLocation1y) / 100.0;
		pt4[2] = (337.711 - reLocation1z) / 100.0;

		ang4 = J_t4 * J_14  * pt4;

		//	// 원래 + 증분 
		for (int j = 0; j < 6; j++)
		{
			angle4[j] = angle4[j] + ang4.at<float>(j, 0);
		}

	}

	CString strData4;
	//GetDlgItemText(IDC_DATA, strData);
	strData4.Format("[ %f, %f, %f, %f, %f, %f ]",
		angle1[0] * 180.0 / 3.141592,
		angle1[1] * 180.0 / 3.141592,
		angle1[2] * 180.0 / 3.141592,
		angle1[3] * 180.0 / 3.141592,
		angle1[4] * 180.0 / 3.141592,
		angle1[5] * 180.0 / 3.141592);

	((CClientTestApp*)AfxGetApp())->SendData(strData4);
	SetDlgItemText(IDC_DATA, "");
	
	UpdateData(false);
}


void CClientTestDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	// 도형 리얼 좌표계 불러오기 
	FileStorage fsRead("ceterScalePoint.yml", cv::FileStorage::READ);

	float point2x;
	float point2y;

	fsRead["Point2x"] >> point2x;
	fsRead["Point2y"] >> point2y;

	fsRead.release();

	// 물체를 반대쪽에 놓을 x y 임이의 좌표값 
	float rePoint2x = -748.705;
	float rePoint2y = -178.037;

	robotSendlocaiotn(point2x, point2y, rePoint2x, rePoint2y);


}


void CClientTestDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	// 도형 리얼 좌표계 불러오기 
	FileStorage fsRead("ceterScalePoint.yml", cv::FileStorage::READ);

	float point3x;
	float point3y;
	fsRead["Point3x"] >> point3x;
	fsRead["Point3y"] >> point3y;

	fsRead.release();

	// 물체를 반대쪽에 놓을 x y 임이의 좌표값 
	float rePoint3x = -903.894;
	float rePoint3y = -387.256;

	robotSendlocaiotn(point3x, point3y, rePoint3x, rePoint3y);

}
