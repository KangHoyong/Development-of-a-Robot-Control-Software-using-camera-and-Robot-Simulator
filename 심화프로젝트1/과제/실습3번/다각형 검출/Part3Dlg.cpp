
// Part3Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Part3.h"
#include "Part3Dlg.h"
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


// CPart3Dlg 대화 상자



CPart3Dlg::CPart3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PART3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPart3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list1);
}

BEGIN_MESSAGE_MAP(CPart3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPart3Dlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_LBN_SELCHANGE(IDC_LIST1, &CPart3Dlg::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// CPart3Dlg 메시지 처리기

BOOL CPart3Dlg::OnInitDialog()
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
		MessageBox(_T("카메라 연결안되었습니다."));
	}


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPart3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPart3Dlg::OnPaint()
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
HCURSOR CPart3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CPart3Dlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	SetTimer(100, 30, NULL);
}
void  CPart3Dlg::setLabel(Mat& image, string str, vector<Point> contour, int index)
{
	int fontface = FONT_HERSHEY_SIMPLEX;
	double scale = 0.5;
	int thickness = 1;
	int baseline = 0;


	Size text = getTextSize(str, fontface, scale, thickness, &baseline);
	//Rect r = boundingRect(contour);

	if (count == 1)
	{
		str.c_str();
		CString test;
		CString test1;

		str = str + '(' + to_string(index) + ')';


		Rect a = boundingRect(contour);

		CString output, count, output1, output2, area, x, y;


		Moments mmt = moments(contour);
		Point center(mmt.m10 / mmt.m00, mmt.m01 / mmt.m00);
		circle(image, center, 5, Scalar(0, 255, 255), 3);

		count.Format(_T("%d"), index);


		x.Format(_T("%d"), a.x);
		area.Format(_T("%.2f"), contourArea(contour));

		test = str.c_str();

		x.Format(_T("%d"), a.x);

		y.Format(_T("%d"), a.y);

		output.Format(_T("%d"), center.x);

		output1.Format(_T("%d"), center.y);
		
		list1.AddString(count + "x:" + x + "y:" + y + "center x: " + output + +"center y: " + output1 + "면적:" + area +"다각형" + test);


		//Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
		//rectangle(image, pt + Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(200, 200, 200), FILLED);
		//putText(image, str, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
	}
	


}

void CPart3Dlg::OnTimer(UINT_PTR nIDEvent)
{


	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Mat img_result;

	// 원본 이미지 
	vCap.read(iFrame);

	Mat img_binary;
	// 이진화
	cvtColor(iFrame, iGray, COLOR_BGR2GRAY);

	threshold(iGray, img_binary, 127, 255, THRESH_BINARY_INV | THRESH_OTSU);

	imshow("img_bin", img_binary);
	// 레이블링 
	Mat img_labels, stats, centroids;

	// int numOfLables = ; 
	int numOfLables = connectedComponentsWithStats(img_binary, img_labels, stats, centroids);

	//contour를 찾는다.
	vector<vector<Point> > contours;
	findContours(img_binary, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); i++)
	{
		Scalar c(0, 255, 0);
		drawContours(iFrame, contours, i, c, 2);
		rectangle(iFrame, boundingRect(contours[i]), Scalar(0, 0, 255));
	}
	//contour를 근사화한다


	// vector<vector<Point>> approx;
	vector<Point2f> approx;
	img_result = iFrame.clone();

	int index = 0;


	for (size_t i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
		if (fabs(contourArea(Mat(approx))) > 100)
		{
			int size = approx.size();
			index++;

			//Contour를 근사화한 직선을 그린다.
			if (size % 2 == 0) {
				line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);

				for (int k = 0; k < size - 1; k++)
					line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);

				for (int k = 0; k < size; k++)
					circle(img_result, approx[k], 3, Scalar(0, 0, 255));
			}
			else {
				line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);

				for (int k = 0; k < size - 1; k++)
					line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);

				for (int k = 0; k < size; k++)
					circle(img_result, approx[k], 3, Scalar(0, 0, 255));
			}

			//도형을 판정한다.
			if (size == 3)
			{
				setLabel(img_result, "triangle", contours[i], index);
			}
			else if (size == 4)
			{
				setLabel(img_result, "rectangle", contours[i], index);
			}
			else if (size == 5)
			{
				setLabel(img_result, "pentagon", contours[i], index);

			}
			else if (size == 6)
			{
				setLabel(img_result, "hexagon", contours[i], index);

			}
			else setLabel(img_result, to_string(approx.size()), contours[i], index);//알수 없는 경우에는 찾아낸 꼭지점 갯수를 표시
		}

	}

	count = 0;

	FileStorage fs;
	fs.open("testtt.yum", FileStorage::WRITE);

	
	for (int i = 1; i < numOfLables; i++)
	{
		int LefX = stats.at<int>(i, CC_STAT_LEFT);
		int topY = stats.at<int>(i, CC_STAT_TOP);
		double x = centroids.at<double>(i, 0);
		double y = centroids.at<double>(i, 1);
		int area = stats.at<int>(i, CC_STAT_AREA);
		fs << "count " << i;
		fs << "x" << LefX;
		fs << "y" << topY;
		fs << "centroids x" << x;
		fs << "centroids y" << y;
		fs << "area" << area;
	
		//CString a;
		//a.Format(_T("%d"),x);
		//list1.AddString(a);

		putText(img_result, to_string(area), Point(LefX + 30, topY + 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 250), 2);
		//putText(img_result, to_string(i), Point(LefX , topY), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 250), 2);

	}

	fs.release();
	imshow("Test", img_result);

	CDialogEx::OnTimer(nIDEvent);
}



void CPart3Dlg::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
