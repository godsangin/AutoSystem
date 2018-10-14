
// AutosysDlg.cpp : ���� ����
//

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

using namespace cv;
using namespace std;

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
		MessageBox(curfile);
		s = std::to_string(i++);
		locate = (sselectjob + "/" + s + "@*.*").c_str();
		
		working = finder.FindFile(locate);
	}

}