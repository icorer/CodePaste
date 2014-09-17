// CodesPaste.h : main header file for the CODESPASTE application
//

#if !defined(AFX_CODESPASTE_H__7C9F6394_6DCF_4E67_9553_260162166268__INCLUDED_)
#define AFX_CODESPASTE_H__7C9F6394_6DCF_4E67_9553_260162166268__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCodesPasteApp:
// See CodesPaste.cpp for the implementation of this class
//

class CCodesPasteApp : public CWinApp
{
public:
	CCodesPasteApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCodesPasteApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCodesPasteApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CODESPASTE_H__7C9F6394_6DCF_4E67_9553_260162166268__INCLUDED_)
