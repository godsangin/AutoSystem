#pragma once


// filename ��ȭ �����Դϴ�.

class filename : public CDialogEx
{
	DECLARE_DYNAMIC(filename)

public:
	filename(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~filename();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
};
