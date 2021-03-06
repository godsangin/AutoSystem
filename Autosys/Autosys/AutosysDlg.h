
// AutosysDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include<iostream>
using namespace std;

// CAutosysDlg 대화 상자
class CAutosysDlg : public CDialogEx
{
// 생성입니다.
public:
	CAutosysDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOSYS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void foldersearch();

	void operate();

	void parsing(string jobname, string filename);
	void matching(string jobname, string filename,int flag);

	CListBox m_listbox;
	afx_msg void OnBnClickedButton2();
};
