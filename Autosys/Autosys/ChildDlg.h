#pragma once
#include "afxwin.h"


// ChildDlg ��ȭ �����Դϴ�.

class ChildDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChildDlg)

public:
	ChildDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ChildDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg
		void Setfilename(CString str);
	void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdit1();

	CEdit mEdit;
};
