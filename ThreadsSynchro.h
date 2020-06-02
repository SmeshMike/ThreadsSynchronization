
// ThreadsSynchro.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CThreadsSynchroApp:
// See ThreadsSynchro.cpp for the implementation of this class
//

class CThreadsSynchroApp : public CWinApp
{
public:
	CThreadsSynchroApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CThreadsSynchroApp theApp;
