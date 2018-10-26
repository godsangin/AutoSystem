// filename.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Autosys.h"
#include "filename.h"
#include "afxdialogex.h"
#include "ChildDlg.h"

// filename 대화 상자입니다.
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
	wchar_t c[] = L"ㅇㅏㄴㄴㅕㅇ";
	GotoDlgCtrl(GetDlgItem(IDC_EDIT1));
	keybdeventAction(c, 6);
	CString filename;
	GetDlgItemText(IDC_EDIT1, filename);
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
	case L'ㅂ':
		return 81;
	case L'ㅈ':
		return 87;
	case L'ㄷ':
		return 69;
	case L'ㄱ':
		return 82;
	case L'ㅅ':
		return 84;
	case L'ㅛ':
		return 89;
	case L'ㅕ':
		return 85;
	case L'ㅑ':
		return 73;
	case L'ㅐ':
		return 79;
	case L'ㅔ':
		return 80;
	case L'ㅁ':
		return 65;
	case L'ㄴ':
		return 83;
	case L'ㅇ':
		return 68;
	case L'ㄹ':
		return 70;
	case L'ㅎ':
		return 71;
	case L'ㅗ':
		return 72;
	case L'ㅓ':
		return 74;
	case L'ㅏ':
		return 75;
	case L'ㅣ':
		return 76;
	case L'ㅋ':
		return 90;
	case L'ㅌ':
		return 88;
	case L'ㅊ':
		return 67;
	case L'ㅍ':
		return 86;
	case L'ㅠ':
		return 66;
	case L'ㅜ':
		return 78;
	case L'ㅡ':
		return 77;
	}
	return 0;
}
