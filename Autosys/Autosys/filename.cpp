// filename.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Autosys.h"
#include "filename.h"
#include "afxdialogex.h"
#include "ChildDlg.h"

// filename ��ȭ �����Դϴ�.
void keybdeventAction(wchar_t buffer[], int strLength);
int getHangulKey(wchar_t c);

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
	wchar_t c[] = L"���������Ť�";
	GotoDlgCtrl(GetDlgItem(IDC_EDIT1));
	keybdeventAction(c, 6);
	CString filename;
	GetDlgItemText(IDC_EDIT1, filename);
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
void keybdeventAction(wchar_t buffer[], int strLength) {
	
	for (int i = 0; i < strLength; i++) {
		if (::GetKeyState(VK_CAPITAL)) {
			keybd_event(VK_CAPITAL, 0, KEYEVENTF_EXTENDEDKEY, 0);
			Sleep(100);
			keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
		}
		if (::GetKeyState(VK_SHIFT)) {
			keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
		}
		if (!::GetKeyState(VK_HANGEUL) && buffer[i] & 0x80 != 1) {
			keybd_event(VK_HANGEUL, 0, KEYEVENTF_EXTENDEDKEY, 0);
			Sleep(100);
			
		}
		if (buffer[i] & 0x80 != 1) {
			
			keybd_event(getHangulKey(buffer[i]), 0, KEYEVENTF_EXTENDEDKEY, 0);
			Sleep(100);
			keybd_event(getHangulKey(buffer[i]), 0, KEYEVENTF_KEYUP, 0);
			Sleep(100);
			keybd_event(VK_HANGEUL, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buffer[i] >= 48 && buffer[i] <= 57) {
			keybd_event(buffer[i], 0, KEYEVENTF_EXTENDEDKEY, 0);
			Sleep(100);
			keybd_event(buffer[i], 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buffer[i] >= 65 && buffer[i] <= 90) {
			keybd_event(16, 0, KEYEVENTF_EXTENDEDKEY, 0);
			keybd_event(buffer[i], 0, KEYEVENTF_EXTENDEDKEY, 0);
			Sleep(100);
			keybd_event(16, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(buffer[i], 0, KEYEVENTF_KEYUP, 0);

		}
		else if (buffer[i] >= 97 && buffer[i] <= 122) {
			keybd_event(buffer[i] - 32, 0, KEYEVENTF_EXTENDEDKEY, 0);
			Sleep(100);
			keybd_event(buffer[i] - 32, 0, KEYEVENTF_KEYUP, 0);
		}
		else if (buffer[i] == 64) {
			keybd_event(16, 0, KEYEVENTF_EXTENDEDKEY, 0);
			keybd_event(50, 0, KEYEVENTF_EXTENDEDKEY, 0);
			Sleep(100);
			keybd_event(16, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(50, 0, KEYEVENTF_KEYUP, 0);

		}
	}
}

int getHangulKey(wchar_t c) {
	switch (c) {
	case L'��':
		return 81;
	case L'��':
		return 87;
	case L'��':
		return 69;
	case L'��':
		return 82;
	case L'��':
		return 84;
	case L'��':
		return 89;
	case L'��':
		return 85;
	case L'��':
		return 73;
	case L'��':
		return 79;
	case L'��':
		return 80;
	case L'��':
		return 65;
	case L'��':
		return 83;
	case L'��':
		return 68;
	case L'��':
		return 70;
	case L'��':
		return 71;
	case L'��':
		return 72;
	case L'��':
		return 74;
	case L'��':
		return 75;
	case L'��':
		return 76;
	case L'��':
		return 90;
	case L'��':
		return 88;
	case L'��':
		return 67;
	case L'��':
		return 86;
	case L'��':
		return 66;
	case L'��':
		return 78;
	case L'��':
		return 77;
	}
	return 0;
}
