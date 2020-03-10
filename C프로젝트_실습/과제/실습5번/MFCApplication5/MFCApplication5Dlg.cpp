
// MFCApplication5Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication5.h"
#include "MFCApplication5Dlg.h"
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


// CMFCApplication5Dlg 대화 상자



CMFCApplication5Dlg::CMFCApplication5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION5_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication5Dlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCApplication5Dlg 메시지 처리기

BOOL CMFCApplication5Dlg::OnInitDialog()
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

void CMFCApplication5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication5Dlg::OnPaint()
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
HCURSOR CMFCApplication5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication5Dlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	SetTimer(100, 30, NULL);


}


void CMFCApplication5Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	vCap.read(iFrame);
	Mat iGray;
	Mat canny;
	Mat dst;

	cvtColor(iFrame, iGray, COLOR_BGR2GRAY);
	GaussianBlur(iGray, iGray, Size(5, 5), 0);

	threshold(iGray, canny, 100, 255, THRESH_BINARY_INV | THRESH_OTSU);

	//adaptiveThreshold(iGray, canny, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 7, 16);

	imshow("iGray", canny);


	Mat mask = getStructuringElement(MORPH_RECT, Size(5, 5));


	dilate(canny, canny, mask, Point(-1, -1), 3);



	erode(canny, canny, mask, Point(-1, -1), 3);



	imshow("thersholdImg3", canny);

	vector<vector<Point>> contours;
	findContours(canny, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<Point2f> approx;
	dst = iFrame.clone();
	int index = 0;
	
	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02, true);
		
	
			int size = approx.size();
			index++;

			Mat img_labels, stats, centroids;
			int numOfLables = connectedComponentsWithStats(canny, img_labels, stats, centroids, 8, CV_32S);

			
			//Contour를 근사화한 직선을 그린다.
			if (size % 2 == 0) {
				line(dst, approx[0], approx[approx.size() - 1], Scalar(255, 0, 0), 3);

				for (int k = 0; k < size - 1; k++)
					line(dst, approx[k], approx[k + 1], Scalar(255, 0, 0), 3);

				for (int k = 0; k < size; k++)
					circle(dst, approx[k], 3, Scalar(255, 0, 0));
			}
			else {
				line(dst, approx[0], approx[approx.size() - 1], Scalar(255, 0, 0), 3);

				for (int k = 0; k < size - 1; k++)
					line(dst, approx[k], approx[k + 1], Scalar(255, 0, 0), 3);

				for (int k = 0; k < size; k++)
					circle(dst, approx[k], 3, Scalar(255, 0, 0));
			}
		
		

	}
	
	
	String text;

	text = "x:" + to_string(approx[0].x) + "y:" + to_string(approx[0].y);
	putText(dst, text, Point(approx[0]), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 0), 1);


	text = "x:" + to_string(approx[1].x) + "y:" + to_string(approx[1].y);
	putText(dst, text, Point(approx[1]), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 0), 1);


	text = "x:" + to_string(approx[2].x) + "y:" + to_string(approx[2].y);
	putText(dst, text, Point(approx[2]), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 0), 1);


	text = "x:" + to_string(approx[3].x) + "y:" + to_string(approx[3].y);
	putText(dst, text, Point(approx[3]), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 0), 1);


	float x1 = approx[0].x;
	float y1 = approx[0].y;
	float x2 = approx[1].x;
	float y2 = approx[1].y;
	float x3 = approx[2].x;
	float y3 = approx[2].y;
	float x4 = approx[3].x;
	float y4 = approx[3].y;

	float d;
	float d2;

	Point p1, p2 , p3, p4;
	p1.x = x1;
	p1.y = y1;

	p2.x = x2;
	p2.y = y2;

	p3.x = x3;
	p3.y = y3;

	p4.x = x4;
	p4.y = y4;

	

	d = sqrt(pow((x1 - x2), 2) + (pow((y1 - y2), 2)));
	d2 = sqrt(pow((x2 - x3), 2) + (pow((y2 - y3), 2)));

	float D = 0.388; // 켈리브레이션 해서 나온값 
	float D2 ,D3;

	D2 = d * D;
	D3 = d2 * D;

	circle(dst, p1, 10, Scalar(0, 0, 255), -1);
	circle(dst, p2, 10, Scalar(0, 0, 255), -1);
	circle(dst, p3, 10, Scalar(0, 0, 255), -1);
	circle(dst, p4, 10, Scalar(0, 0, 255), -1);

	// 회전각 
	float angle = (approx[3].x - approx[2].x) * D;

	float value = angle / D2;

	double theta = acos(value);

	double angleValue = theta * 180 / CV_PI;

	Moments mmt = moments(approx);

	Point center(mmt.m10 / mmt.m00, mmt.m01 / mmt.m00);

	circle(dst, center, 5, Scalar(0, 255, 255), 3);

	String str1 = "width result  :" + to_string(D2);
	String str2 = "height result  :" + to_string(D3);
	putText(dst, "angle :" + to_string(angleValue), center, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);

	putText(dst, str1, Point(400,50), 1, 1, Scalar(0, 200, 255));
	putText(dst, str2, Point(105,350), 1, 1, Scalar(0, 200, 255));

	imshow("canny", dst);

	CDialogEx::OnTimer(nIDEvent);
}
