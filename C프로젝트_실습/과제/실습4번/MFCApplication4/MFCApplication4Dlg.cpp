
// MFCApplication4Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication4.h"
#include "MFCApplication4Dlg.h"
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


// CMFCApplication4Dlg 대화 상자



CMFCApplication4Dlg::CMFCApplication4Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION4_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication4Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCApplication4Dlg 메시지 처리기

BOOL CMFCApplication4Dlg::OnInitDialog()
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

void CMFCApplication4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication4Dlg::OnPaint()
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
HCURSOR CMFCApplication4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication4Dlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	// 체스판 수 
	int nBoard = 8;
	int found1;
	bool found;

	// 체스판의 가로 점의 개수 , 세로 점의 개수
	int nComerW = 11;
	int nComerH = 6;
	Size image_size;

	// 체스판 코너 점을 찾을 때 개수가 일치
	int nComer = nComerW * nComerH;

	// 영상의 점들을 저장하는 리스트 
	vector<vector<Point2f>> imge_points;

	// 점들 실제 3차원 좌표를 저장하는 리스트 
	vector<vector<Point3f>> object_points;

	// 체스판에서 찾는 코너점을 찾는것 
	vector<Point2f> corners;

	float D;
	float D1;
	float D2;

	vCap.read(iFream);

	cvtColor(iFream, iGray, COLOR_BGR2GRAY);

	image_size = iFream.size();

	// 체스판 코너 찾기 
	//bool found = findChessboardCorners(iGray, Size(nComerW, nComerH), corners);
	found1 = findChessboardCorners(iGray, Size(nComerW, nComerH), corners);

	if (found1)
	{
		// 그려주기 
		// 찾은 코너 이미지 그리기 

		Point pt1, pt2;
		Point pt3, pt4;

		for (int i = 0; i < corners.size(); i++)
		{
			int x = corners[i].x;
			int y = corners[i].y;
		}
		int x1 = corners[0].x;
		int x2 = corners[10].x;
		int y1 = corners[0].y;
		int y2 = corners[10].y;

		int x3 = corners[0].x;
		int x4 = corners[22].x;
		int y3 = corners[0].y;
		int y4 = corners[22].y;

		pt1.x = x1;
		pt2.x = x2;
		pt1.y = y1;
		pt2.y = y2;

		pt3.x = x3;
		pt4.x = x4;
		pt3.y = y3;
		pt4.y = y4;

		float d = sqrt(pow((x1 - x2), 2) + (pow((y1 - y2), 2)));
		float d1 = sqrt(pow((x3 - x4), 2) + (pow((y3 - y4), 2)));

		float a = 200;
		// 스케일 
		D = a / d;

		// 실제거리 
		D1 = d1 * D;
		D2 = d * D;
		String str = "result  :" + to_string(D1);
		String str1 = "result  :" + to_string(D2);
		String str2 = "D :" + to_string(D);

		putText(iFream, str, pt4, 1, 1, Scalar(0, 200, 255));
		putText(iFream, str1, pt2, 1, 1, Scalar(0, 200, 255));
		putText(iFream, str2, Point(30,30), 1, 1, Scalar(0, 200, 255));
	

		line(iFream, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
		line(iFream, pt3, pt4, Scalar(0, 0, 255), 1, LINE_AA);
	}
	FileStorage fs;
	fs.open("intricsics.yml", FileStorage::WRITE);
	fs << "image_width" << image_size.width;
	fs << "image_height" << image_size.height;
	fs << "Corners Matrix" << corners;

	for (int i = 0; i < corners.size(); i++)
	{
		int x = corners[i].x;
		int y = corners[i].y;
		fs << "x" + to_string(i) << x ;
		fs << "Y" + to_string(i) << y;
	}
	fs << "resuslt 0 0 - 10 10 " << D1;
	fs << "resuslt 0 0 - 22 22 " << D2;

	fs << "D" << D;

	MessageBox(_T("저장완료!!"));

	fs.release();

	imshow("result", iFream);

}
