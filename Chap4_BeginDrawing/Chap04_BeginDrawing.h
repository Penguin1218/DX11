
// Chap4_BeginDrawing.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CChap04_BeginDrawingApp:
// See Chap4_BeginDrawing.cpp for the implementation of this class
//

class CChap04_BeginDrawingApp : public CWinApp
{
public:
	CChap04_BeginDrawingApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CChap04_BeginDrawingApp theApp;