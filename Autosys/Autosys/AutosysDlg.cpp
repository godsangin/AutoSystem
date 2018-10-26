
// AutosysDlg.cpp : 구현 파일
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


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CAutosysDlg 대화 상자



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


// CAutosysDlg 메시지 처리기

BOOL CAutosysDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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
	
	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	foldersearch();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CAutosysDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAutosysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAutosysDlg::OnBnClickedButton1()//추가 버튼
{
	
	filename filename;
	ShowWindow(SW_HIDE);
	filename.DoModal();
	filename.DestroyWindow();
	foldersearch();
	ShowWindow(SW_RESTORE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAutosysDlg::OnBnClickedOk() //실행버튼
{
	
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	operate();

	CDialogEx::OnOK();
}


void CAutosysDlg::OnBnClickedCancel()//취소버튼
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

void CAutosysDlg::foldersearch() { //파일찾기
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
	printf("token = %s", token);//첫번째꺼 버림 순서는 이미 끝
	token = strtok(NULL, parser);
	printf("token = %s", token);//두번째꺼 좌우더블텍스트

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
	printf("token = %s", token);//세번째꺼 확장자
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
	IplImage *A = cvLoadImage("copy.jpg", -1); // 책상(A)을 먼저 읽고
	IplImage *B = cvLoadImage(cstr, -1); // 스테이플러(B)를 읽는다.
	IplImage* C = cvCreateImage(cvSize(A->width - B->width + 1, A->height - B->height + 1), IPL_DEPTH_32F, 1); // 상관계수를 구할 이미지(C)

	cvMatchTemplate(A, B, C, CV_TM_CCOEFF_NORMED); // 상관계수를 구하여 C 에 그린다.
	cvMinMaxLoc(C, &min, &max, NULL, &left_top); // 상관계수가 최대값을 값는 위치 찾기  ?????
	cvRectangle(A, left_top, cvPoint(left_top.x + B->width, left_top.y + B->height), CV_RGB(255, 0, 0)); // 찾은 물체에 사격형을 그린다.
	if (max > 0.9) {
		printf("x = %d, y = %d 최대 %lf", left_top.x, left_top.y, max);

		goevent((left_top.x + (B->width) / 2) / windowmultiply, (left_top.y + (B->height) / 2) / windowmultiply,flag); // ??????

		//Show("T9-result", A); // 결과 보기
							  //Show("T9-sample", B); // 스테이플러(B) 보기
							  //Show("C", C);   // 상관계수 이미지 보기
		cvWaitKey(0);

		// 모든 이미지 릴리즈
		cvReleaseImage(&A);
		cvReleaseImage(&B);
		cvReleaseImage(&C);
		// 모든 윈도우 제거
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
