#pragma once


// filename 대화 상자입니다.

class filename : public CDialogEx
{
	DECLARE_DYNAMIC(filename)

public:
	filename(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~filename();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
};
