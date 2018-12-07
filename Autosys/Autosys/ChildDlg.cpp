// ChildDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Autosys.h"
#include "ChildDlg.h"
#include "afxdialogex.h"
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <Windows.h>
#include <iostream>
#include "filename.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace cv;
int BreakHan(wchar_t *str, wchar_t *buffer, UINT nSize);
void keybdeventAction(char buffer[], int strLength);
void windowcapture();
static void mouse_callback(int event, int x, int y, int, void* param);
static void imageCapture();
String strValue;
Mat hwnd2mat(HWND hwnd);
bool ldown = false, lup = false;
Mat img, dst;
Point corner1, corner2;
Rect box;
string filename;
int sequence = 1;
string flag;
// ChildDlg ��ȭ �����Դϴ�.
IMPLEMENT_DYNAMIC(ChildDlg, CDialogEx)

ChildDlg::ChildDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
}

ChildDlg::~ChildDlg()
{
}

void ChildDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mEdit);
}


BEGIN_MESSAGE_MAP(ChildDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ChildDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ChildDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &ChildDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &ChildDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &ChildDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ChildDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT1, &ChildDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// ChildDlg �޽��� ó�����Դϴ�.
void ChildDlg::Setfilename(CString str) {
	CT2CA pszConvertedAnsiString(str);
	std::string s(pszConvertedAnsiString);
	filename = s;
}

void ChildDlg::OnBnClickedButton1()
{
	flag = "1";
	imageCapture();

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ChildDlg::OnBnClickedButton2()
{
	flag = "2";
	imageCapture();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ChildDlg::OnBnClickedButton3()
{
	flag = "3";
	imageCapture();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void ChildDlg::OnBnClickedButton4()
{
	flag = "4";
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	string sqstr = to_string(sequence);
	ofstream out(filename + "/" + sqstr + "@" + flag + ".txt");
	sequence++;

	wchar_t *str;
	wchar_t buffer[4096];
	
	CString s;
	GetDlgItemText(IDC_EDIT1, s);
	str = LPWSTR(LPCTSTR(s));
	str = LPWSTR(LPCTSTR(s));
	BreakHan(str, buffer, sizeof buffer);

	setlocale(LC_ALL, "Korean");
	SetDlgItemText(IDC_EDIT1, NULL);

	CT2CA pszConvertedAnsiString(buffer);
	std::string sentence(pszConvertedAnsiString);
	
	

	if (out.is_open()) {
		out << sentence;
	}
	else {

	}

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void ChildDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}


void ChildDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


void ChildDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}




void windowcapture() {
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	Sleep(100);
	HWND hwndDesktop = GetDesktopWindow();

	int key = 0;

	Mat src = hwnd2mat(hwndDesktop);
	//imshow("output", src);

	imwrite("copy.jpg", src);
	//ShowWindow(SW_RESTORE);

}
Mat hwnd2mat(HWND hwnd)
{
	HDC hwindowDC, hwindowCompatibleDC;

	int height, width, srcheight, srcwidth;
	HBITMAP hbwindow;
	Mat src;
	BITMAPINFOHEADER  bi;


	hwindowDC = GetDC(hwnd);
	hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);


	RECT windowsize;    // get the height and width of the screen
	GetClientRect(hwnd, &windowsize);


	srcheight = windowsize.bottom;
	srcwidth = windowsize.right;
	height = windowsize.bottom / 1;  //change this to whatever size you want to resize to
	width = windowsize.right / 1;


	src.create(height, width, CV_8UC4);


	// create a bitmap
	hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
	bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
	bi.biWidth = width;
	bi.biHeight = -height;  //this is the line that makes it draw upside down or not
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;


	// use the previously created device context with the bitmap
	SelectObject(hwindowCompatibleDC, hbwindow);
	// copy from the window device context to the bitmap device context
	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

																									   // avoid memory leak
	DeleteObject(hbwindow);
	DeleteDC(hwindowCompatibleDC);
	ReleaseDC(hwnd, hwindowDC);


	return src;
}
static void mouse_callback(int event, int x, int y, int, void* param) {

	if (event == EVENT_LBUTTONDOWN) {
		ldown = true;
		corner1.x = x;
		corner1.y = y;
	}

	if (event == EVENT_LBUTTONUP) {

		if (abs(x - corner1.x) > 5 && abs(y - corner1.y) > 5) {
			lup = true;
			corner2.x = x;
			corner2.y = y;
		}
		else {
			ldown = false;
		}
	}

	if (ldown == true && lup == false) {
		Point pt;
		pt.x = x;
		pt.y = y;
		Mat locale_img = dst.clone();
		rectangle(locale_img, corner1, pt, Scalar(255, 0, 0));
		imshow("Original IMG", locale_img);
	}

	if (ldown == true && lup == true) {
		box.width = abs(corner1.x - corner2.x);
		box.height = abs(corner1.y - corner2.y);
		box.x = min(corner1.x, corner2.x);
		box.y = min(corner1.y, corner2.y);
		Mat crop(img, box);
		imshow("what", crop);
		string sqstr = to_string(sequence);
		imwrite(filename + "/" + sqstr + "@" + flag + ".jpg", crop);
		sequence++;
		ldown = false; lup = false;
		destroyAllWindows();
	}
}
static void imageCapture() {
	windowcapture();
	Sleep(1000);

	img = imread("copy.jpg", CV_LOAD_IMAGE_COLOR);

	if (!img.data) {

		cout << "Image Can't Load" << endl;

	}

	namedWindow("Original IMG");
	resize(img, dst, Size(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), 0, 0, CV_INTER_NN);

	imshow("Original IMG", dst);
	setMouseCallback("Original IMG", mouse_callback);
	waitKey(0);

}
int BreakHan(wchar_t *str, wchar_t *buffer, UINT nSize)
{
	//�ʼ� 
	static const wchar_t wcHead[] = { L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��' };

	//�߼� 
	static const wchar_t wcMid[] = { L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��', L'��' };

	//���� 
	static const wchar_t wcTail[] = { L' ', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��',
		L'��', L'��', L'��', L'��' };

	UINT    pos = 0;

	while (*str != '\0')
	{
		if (*str < 256)
		{
			if (pos + 2 >= nSize - 1)
				break;

			buffer[pos] = *str;
			++pos;
		}
		else
		{
			if (pos + 4 >= nSize - 1)
				break;

			buffer[pos] = wcHead[(*str - 0xAC00) / (21 * 28)];
			buffer[pos + 1] = wcMid[(*str - 0xAC00) % (21 * 28) / 28];
			buffer[pos + 2] = wcTail[(*str - 0xAC00) % 28];

			pos += 3;
		}

		++str;
	}

	buffer[pos] = '\0';
	return pos;
}
