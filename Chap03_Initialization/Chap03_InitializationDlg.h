
// Chap03_InitializationDlg.h : ��� ����
//

#pragma once
class DXManager;

// CChap03_InitializationDlg ��ȭ ����
class CChap03_InitializationDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CChap03_InitializationDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAP03_INITIALIZATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
