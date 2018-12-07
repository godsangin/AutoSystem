// filename.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "Autosys.h"
#include "filename.h"
#include "afxdialogex.h"
#include "ChildDlg.h"
// filename 대화 상자입니다.

IMPLEMENT_DYNAMIC(filename, CDialogEx)
filename::filename(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

filename::~filename()
{
}

void filename::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(filename, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &filename::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT1, &filename::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &filename::OnBnClickedOk)
END_MESSAGE_MAP()

// filename 메시지 처리기입니다.

void filename::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void filename::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void filename::OnBnClickedOk()
{
	
	CString filename;
	GetDlgItemText(IDC_EDIT1, filename);
	
	if (GetFileAttributes(L"auto") == -1) {
		CreateDirectory(L"auto",NULL);
	}
	CString cstring(_T("auto/"));
	filename = cstring + filename;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (GetFileAttributes(filename) == -1) {
		CreateDirectory(filename, NULL);
		ChildDlg childDlg;
		childDlg.Setfilename(filename);
		childDlg.DoModal();

		childDlg.DestroyWindow();

	}
	else {
		MessageBox(TEXT("이미 있습니다. 다른이름을 이용하시거나 삭제후 이용하세요."));
	}
	
	CDialogEx::OnOK();

}
