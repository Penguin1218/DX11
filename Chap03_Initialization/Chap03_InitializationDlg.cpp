
// Chap03_InitializationDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Chap03_Initialization.h"
#include "Chap03_InitializationDlg.h"
#include "afxdialogex.h"

#include <process.h>
#include "DXManager.h"
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


// CChap03_InitializationDlg 대화 상자



CChap03_InitializationDlg::CChap03_InitializationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHAP03_INITIALIZATION_DIALOG, pParent)
	, _d3d_thread(INVALID_HANDLE_VALUE)
{
	_renderer = DXManager::get_insatance();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChap03_InitializationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChap03_InitializationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CChap03_InitializationDlg 메시지 처리기

BOOL CChap03_InitializationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	g_hwnd = GetSafeHwnd();
	//g_hwnd = ::GetDlgItem(GetSafeHwnd(), IDC_STATIC_VIDEO_WINDOW);
	unsigned int thrdaddr = 0;
	
	_d3d_thread = (HANDLE)::_beginthreadex(NULL, 0, CChap03_InitializationDlg::process_callback, this, 0, &thrdaddr);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChap03_InitializationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChap03_InitializationDlg::OnPaint()
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
HCURSOR CChap03_InitializationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


unsigned __stdcall CChap03_InitializationDlg::process_callback(void* param)
{
	CChap03_InitializationDlg * self = static_cast<CChap03_InitializationDlg*>(param);
	self->process();
	return 0;
}
void CChap03_InitializationDlg::process(void)
{
	Sleep(1000);
	_run = true;
	_renderer->initialize(1280, 720, DXGI_FORMAT_R8G8B8A8_UNORM);
	//_renderer->create_swap_chain();
	_renderer->init_scene();
	while(_run)
	{
		_renderer->updeate_scene();
		_renderer->draw_scene();
	}
}

void CChap03_InitializationDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	_run = false;
	::WaitForSingleObject(_d3d_thread, INFINITE);
	::CloseHandle(_d3d_thread);
	_d3d_thread = INVALID_HANDLE_VALUE;
}
