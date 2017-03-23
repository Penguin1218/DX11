
// Chap03_InitializationDlg.h : 헤더 파일
//

#pragma once
class DXManager;

// CChap03_InitializationDlg 대화 상자
class CChap03_InitializationDlg : public CDialogEx
{
// 생성입니다.
public:
	CChap03_InitializationDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAP03_INITIALIZATION_DIALOG };
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
private:
	static unsigned __stdcall process_callback(void * param);
	void process(void);

	HANDLE	_d3d_thread;
	bool	_run;
	DXManager* _renderer;
public:
	afx_msg void OnDestroy();
};
