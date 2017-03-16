
// Chap03_Initialization.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.


// CChap03_InitializationApp:
// 이 클래스의 구현에 대해서는 Chap03_Initialization.cpp을 참조하십시오.
//

class CChap03_InitializationApp : public CWinApp
{
public:
	CChap03_InitializationApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CChap03_InitializationApp theApp;