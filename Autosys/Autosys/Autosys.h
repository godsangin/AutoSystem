
// Autosys.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CAutosysApp:
// �� Ŭ������ ������ ���ؼ��� Autosys.cpp�� �����Ͻʽÿ�.
//

class CAutosysApp : public CWinApp
{
public:
	CAutosysApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CAutosysApp theApp;