// filename.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "Autosys.h"
#include "filename.h"
#include "afxdialogex.h"
#include "ChildDlg.h"
// filename ��ȭ �����Դϴ�.

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

// filename �޽��� ó�����Դϴ�.

void filename::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


void filename::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (GetFileAttributes(filename) == -1) {
		CreateDirectory(filename, NULL);
		ChildDlg childDlg;
		childDlg.Setfilename(filename);
		childDlg.DoModal();

		childDlg.DestroyWindow();

	}
	else {
		MessageBox(TEXT("�̹� �ֽ��ϴ�. �ٸ��̸��� �̿��Ͻðų� ������ �̿��ϼ���."));
	}
	
	CDialogEx::OnOK();

}
