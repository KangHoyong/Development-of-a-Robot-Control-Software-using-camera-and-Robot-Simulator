
// ClientTestDlg.h: 헤더 파일
//

#pragma once


// CClientTestDlg 대화 상자
class CClientTestDlg : public CDialogEx
{
// 생성입니다.
public:
	CClientTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENTTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSend();
	afx_msg void OnConnect();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	void showMeasurement();
	void showCalib();

	Mat iFream;
	Mat iGray;
	VideoCapture vCap;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListBox list1;
	CListBox list2;

	float xValue;
	float yValue;
	float zValue;

	// Cam 좌표계 
	CString  xCam, yCam, zCam;

	float xw, yw, zw;
	float tx, ty, tz;
	float xc, yc, zc;
	float point1x, point1y;

	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();

	void robotSendlocaiotn(float x , float y, float reX, float reY);

	float saveX;
	float saveY;
	float saveZ;
};
