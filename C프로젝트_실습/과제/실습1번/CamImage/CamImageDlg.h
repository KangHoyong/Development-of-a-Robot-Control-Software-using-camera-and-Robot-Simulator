
// CamImageDlg.h: 헤더 파일
//

#pragma once


// CCamImageDlg 대화 상자
class CCamImageDlg : public CDialogEx
{
// 생성입니다.
public:
	CCamImageDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAMIMAGE_DIALOG };
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
	afx_msg void OnBnClickedButton1();

	VideoCapture vCap; // 비디오 캡처 생성자 
	Mat iFrame; // 프레임 생성자 
	Mat iGray; // 그레이 
	Mat image2;
	

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	// input box
	int xValue;
	int yValue;
	int wValue;
	int hValue;

	// check box 
	BOOL vValue1;
	BOOL vValue2;
	BOOL vValue3;

	// function
	void reversal();
	void tb(); 
	void leftRight();

};
