
// AutosysDlg.cpp : ���� ����
//
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "stdafx.h"
#include "Autosys.h"
#include "AutosysDlg.h"
#include "afxdialogex.h"
#include "ChildDlg.h"
#include "opencv2/opencv.hpp"  
#include <iostream>  
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "filename.h"
#include <Windows.h>
#include "Resource.h"
void windowcapture();
void goevent(int x, int y,int flag);
void Show(char *str, IplImage *img);
using namespace cv;
using namespace std;
int getHangulKey(wchar_t c);
void keybdeventAction(wchar_t buffer[], int strLength);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAutosysDlg ��ȭ ����



CAutosysDlg::CAutosysDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTOSYS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutosysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
}

BEGIN_MESSAGE_MAP(CAutosysDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAutosysDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CAutosysDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAutosysDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAutosysDlg �޽��� ó����

BOOL CAutosysDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	foldersearch();
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CAutosysDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CAutosysDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CAutosysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAutosysDlg::OnBnClickedButton1()//�߰� ��ư
{
	
	filename filename;
	ShowWindow(SW_HIDE);
	filename.DoModal();
	filename.DestroyWindow();
	foldersearch();
	ShowWindow(SW_RESTORE);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CAutosysDlg::OnBnClickedOk() //�����ư
{
	
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	operate();

	CDialogEx::OnOK();
}


void CAutosysDlg::OnBnClickedCancel()//��ҹ�ư
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}

void CAutosysDlg::foldersearch() { //����ã��
	CFileFind finder;
	string s = "auto/*.*";
	CString sc(s.c_str());
	bool working = finder.FindFile(sc);
	m_listbox.ResetContent();
	while (working) {
		working = finder.FindNextFile();

		if (finder.IsDots()) continue;

		if (finder.IsDirectory()) {
			CString curfile = finder.GetFileName();
			m_listbox.AddString(curfile);
		}
	}
}

void CAutosysDlg::operate() {
	CString selectjob;
	CFileFind finder;
	CString locate;
	int i = 1;
	bool working;
	m_listbox.GetText(m_listbox.GetCurSel(), selectjob);
	CT2CA pszConvertedAnsiString(selectjob);
	std::string sselectjob(pszConvertedAnsiString);
	sselectjob = "auto/" +sselectjob;

	std::string s = std::to_string(i++);
	locate = (sselectjob + "/"+s+"@*.*").c_str();
	working = finder.FindFile(locate);
	while (working) {
		working = finder.FindNextFile();
		CString curfile = finder.GetFileName();
		//MessageBox(curfile);
		CT2CA pszConvertedAnsiString(curfile);
		std::string ccurfile(pszConvertedAnsiString);
		parsing(sselectjob,ccurfile);
		s = std::to_string(i++);
		locate = (sselectjob + "/" + s + "@*.*").c_str();
		
		working = finder.FindFile(locate);
	}

}
void CAutosysDlg::parsing(string jobname,string filename) {
	char *file = new char[filename.length() + 1];
	strcpy(file, filename.c_str());
	char *token = NULL;
	char parser[] = "@.";
	token = strtok(file, parser);
	printf("token = %s", token);//ù��°�� ���� ������ �̹� ��
	token = strtok(NULL, parser);
	printf("token = %s", token);//�ι�°�� �¿�����ؽ�Ʈ

	if (token[0] == '1') {
		printf("");
		matching(jobname, filename, 1);
	}
	else if (token[0] == '2') {
		printf("");
		matching(jobname, filename, 2);

	}
	else if (token[0] == '3') {
		printf("");
		matching(jobname, filename, 3);
	}
	else {
		printf("");
	}
	token = strtok(NULL, parser);
	printf("token = %s", token);//����°�� Ȯ����
	token = strtok(NULL, parser);
}
void CAutosysDlg::matching(string jobname, string filename, int flag) {
	windowcapture();
	string file = jobname + "/" + filename;
	char *cstr = new char[file.length() + 1];
	strcpy(cstr, file.c_str());
	double min, max;
	CvPoint left_top;
	double windowmultiply = 1;
	IplImage *A = cvLoadImage("copy.jpg", -1); // å��(A)�� ���� �а�
	IplImage *B = cvLoadImage(cstr, -1); // �������÷�(B)�� �д´�.
	IplImage* C = cvCreateImage(cvSize(A->width - B->width + 1, A->height - B->height + 1), IPL_DEPTH_32F, 1); // �������� ���� �̹���(C)

	cvMatchTemplate(A, B, C, CV_TM_CCOEFF_NORMED); // �������� ���Ͽ� C �� �׸���.
	cvMinMaxLoc(C, &min, &max, NULL, &left_top); // �������� �ִ밪�� ���� ��ġ ã��  ?????
	cvRectangle(A, left_top, cvPoint(left_top.x + B->width, left_top.y + B->height), CV_RGB(255, 0, 0)); // ã�� ��ü�� ������� �׸���.
	if (max > 0.9) {
		printf("x = %d, y = %d �ִ� %lf", left_top.x, left_top.y, max);

		goevent((left_top.x + (B->width) / 2) / windowmultiply, (left_top.y + (B->height) / 2) / windowmultiply,flag); // ??????

		//Show("T9-result", A); // ��� ����
							  //Show("T9-sample", B); // �������÷�(B) ����
							  //Show("C", C);   // ������ �̹��� ����
		cvWaitKey(0);

		// ��� �̹��� ������
		cvReleaseImage(&A);
		cvReleaseImage(&B);
		cvReleaseImage(&C);
		// ��� ������ ����
		cvDestroyAllWindows();
		cvWaitKey(0);

	}
	else {
		windowcapture();
		matching(jobname, filename, flag);
	}
}

void goevent(int x, int y,int flag) {
	SetCursorPos(x, y);
	if (flag == 1) {
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
	else if (flag == 2) {
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	}
	else if (flag == 3) {
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
	
};
void Show(char *str, IplImage *img)
{
	cvNamedWindow(str, 1);
	cvShowImage(str, img);
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
