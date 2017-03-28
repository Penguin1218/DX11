
// Chap4_BeginDrawingDlg.h : header file
//

#pragma once

class primitive_scene_manager;
// CChap4_BeginDrawingDlg dialog
class CChap4_BeginDrawingDlg : public CDialogEx
{
// Construction
public:
	CChap4_BeginDrawingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAP4_BEGINDRAWING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	primitive_scene_manager* _manager;
public:
	afx_msg void OnDestroy();
};
