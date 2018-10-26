// filename.cpp : 姥薄 督析脊艦陥.
//

#include "stdafx.h"
#include "Autosys.h"
#include "filename.h"
#include "afxdialogex.h"
#include "ChildDlg.h"

// filename 企鉢 雌切脊艦陥.
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

// filename 五獣走 坦軒奄脊艦陥.

void filename::OnBnClickedCancel()
{
	// TODO: 食奄拭 珍闘継 硝顕 坦軒奄 坪球研 蓄亜杯艦陥.
	CDialogEx::OnCancel();
}


void filename::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 珍闘継昔 井酔, 戚 珍闘継精
	// CDialogEx::OnInitDialog() 敗呪研 仙走舛 
	//馬壱 原什滴拭 OR 尻至馬食 竺舛吉 ENM_CHANGE 巴掘益研 走舛馬食 CRichEditCtrl().SetEventMask()研 硲窒馬走 省生檎
	// 戚 硝顕 五獣走研 左鎧走 省柔艦陥.

	// TODO:  食奄拭 珍闘継 硝顕 坦軒奄 坪球研 蓄亜杯艦陥.
}


void filename::OnBnClickedOk()
{
	wchar_t c[] = L"したいいづし";
	GotoDlgCtrl(GetDlgItem(IDC_EDIT1));
	keybdeventAction(c, 6);
	CString filename;
	GetDlgItemText(IDC_EDIT1, filename);
	CString cstring(_T("auto/"));
	filename = cstring + filename;
	// TODO: 食奄拭 珍闘継 硝顕 坦軒奄 坪球研 蓄亜杯艦陥.
	if (GetFileAttributes(filename) == -1) {
		CreateDirectory(filename, NULL);
		ChildDlg childDlg;
		childDlg.Setfilename(filename);
		childDlg.DoModal();

		childDlg.DestroyWindow();

	}
	else {
		MessageBox(TEXT("戚耕 赤柔艦陥. 陥献戚硯聖 戚遂馬獣暗蟹 肢薦板 戚遂馬室推."));
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
	case L'げ':
		return 81;
	case L'じ':
		return 87;
	case L'ぇ':
		return 69;
	case L'ぁ':
		return 82;
	case L'さ':
		return 84;
	case L'に':
		return 89;
	case L'づ':
		return 85;
	case L'ち':
		return 73;
	case L'だ':
		return 79;
	case L'つ':
		return 80;
	case L'け':
		return 65;
	case L'い':
		return 83;
	case L'し':
		return 68;
	case L'ぉ':
		return 70;
	case L'ぞ':
		return 71;
	case L'で':
		return 72;
	case L'っ':
		return 74;
	case L'た':
		return 75;
	case L'び':
		return 76;
	case L'せ':
		return 90;
	case L'ぜ':
		return 88;
	case L'ず':
		return 67;
	case L'そ':
		return 86;
	case L'ば':
		return 66;
	case L'ぬ':
		return 78;
	case L'ぱ':
		return 77;
	}
	return 0;
}
