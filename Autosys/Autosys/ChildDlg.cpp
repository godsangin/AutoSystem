// ChildDlg.cpp : 구현 파일입니다.
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
int sequence=1;
string flag;
// ChildDlg 대화 상자입니다.
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


// ChildDlg 메시지 처리기입니다.
void ChildDlg::Setfilename(CString str) {
	CT2CA pszConvertedAnsiString(str);
	std::string s(pszConvertedAnsiString);
	filename = s;
}

void ChildDlg::OnBnClickedButton1()
{
	flag = "1";
	imageCapture();
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ChildDlg::OnBnClickedButton2()
{
	flag = "2";
	imageCapture();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ChildDlg::OnBnClickedButton3()
{
	flag = "3";
	imageCapture();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void ChildDlg::OnBnClickedButton4()
{
	flag = "4";
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	string sqstr = to_string(sequence);
	ofstream out(filename + "/" + sqstr + "@" + flag + ".txt");
	//ofstream out("ddd.txt");
	sequence++;
	CString s;
	GetDlgItemText(IDC_EDIT1, s);
	CT2CA pszConvertedAnsiString(s);
	std::string sentence(pszConvertedAnsiString);
	if (out.is_open()) {
		out << sentence;
	}
	else {

	}

	/*CString str;

	mEdit.GetWindowTextW(str);
	char buffer[256];
	strcpy_s(buffer, CStringA(str).GetString());
	SetCursorPos(1260, 10);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(20);
	SetCursorPos(20, 460);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(20);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(1000);

	keybdeventAction(buffer, str.GetLength());*/


	//MessageBox(BreakHan(w_temp, buffer, sizeof buffer));

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void ChildDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void ChildDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void ChildDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void keybdeventAction(char buffer[], int strLength) {
	for (int i = 0; i < strLength; i++) {
		if (::GetKeyState(VK_CAPITAL)) {
			keybd_event(VK_CAPITAL, 0, KEYEVENTF_EXTENDEDKEY, 0);
			Sleep(100);
			keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
		}
		if (::GetKeyState(VK_SHIFT)) {
			keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
		}
		if (buffer[i] >= 48 && buffer[i] <= 57) {
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

void windowcapture() {
	//ShowWindow(SW_SHOWMINIMIZED);
	//visible = 0;
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
		imwrite(filename+"/" +sqstr+"@"+flag +".jpg", crop);
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
	resize(img, dst, Size(1920, 1080), 0, 0, CV_INTER_NN);

	imshow("Original IMG", dst);
	setMouseCallback("Original IMG", mouse_callback);
	waitKey(0);

}
