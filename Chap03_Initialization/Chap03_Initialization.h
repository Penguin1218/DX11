
// Chap03_Initialization.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CChap03_InitializationApp:
// �� Ŭ������ ������ ���ؼ��� Chap03_Initialization.cpp�� �����Ͻʽÿ�.
//

class CChap03_InitializationApp : public CWinApp
{
public:
	CChap03_InitializationApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CChap03_InitializationApp theApp;