// llk.h : main header file for the LLK application
//

#if !defined(AFX_LLK_H__4A4DD2C3_448B_4DB7_8D86_8EC94F00A84D__INCLUDED_)
#define AFX_LLK_H__4A4DD2C3_448B_4DB7_8D86_8EC94F00A84D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLlkApp:
// See llk.cpp for the implementation of this class
//

class CLlkApp : public CWinApp
{
public:
	CLlkApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLlkApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLlkApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LLK_H__4A4DD2C3_448B_4DB7_8D86_8EC94F00A84D__INCLUDED_)
