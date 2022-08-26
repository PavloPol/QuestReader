// �������� ����������� ������������ ���� ��� Windows-��������
#include <windows.h>
#include <ctime>
#include <string>
#include <fstream>

static HWND hBtn0;
static HWND hBtn[4];
static HWND hStat1;
static HWND hStat2;
std::ifstream fin;
std::string text;
std::string file = "quest.txt";
int hbtn[4] = {0, 0, 0, 0};

void check_file()
{
	fin.open(file);
	if (!fin)
	{
		exit(0);
	}
}

void read(int row = 0)
{
	fin.seekg(0, fin.beg);
	for (int i = 0; i < row * 2; i++)
	{
		fin.ignore(INT_MAX, '\n');
	}
	std::getline(fin, text, '/');
	SetWindowText(hStat1, text.c_str());
	std::getline(fin, text, '/');
	int button_num = atoi(text.c_str());
	for (int i = 0; i < button_num; i++)
	{
		std::getline(fin, text, '/');
		SetWindowText(hBtn[i], text.c_str());
		ShowWindow(hBtn[i], SW_SHOW);
		std::getline(fin, text, '/');
		hbtn[i] = atoi(text.c_str());
	}
}

// ���������� ������� ���� (������� ���������)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst; // ������������� ����������

// ��������� �� ����������� ������ �������� - ��� ��������� � ������ ����
LPCSTR AppName = "Quest";

// ����� ����� � ��������� - ������� WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd; // ���������� ������������� ���� (handle)
	MSG msg; // ���������� ��������� ���� MSG, ��� ������ � �����������

	hInst = hInstance; // ��������� ������������� ����������

	// ��������� ��������� WNDCLASS
	WNDCLASS wc;
	// �������������� ���������� ��� ��������� ������ ������
	ZeroMemory(&wc, sizeof(wc));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = AppName;

	RegisterClass(&wc); // ������� � ������������ ������� �����

	// ������� ���� ���������
	hWnd = CreateWindow(
		AppName, // ��� ������ ����
		AppName, // ��������� ����
		WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU, // ����� ����
		CW_USEDEFAULT, 0, // �������������� � ������������ ������� ����
		500, 500, // ������ � ������ ����
		NULL, // ����� ������������� ����
		NULL, // ����� ����
		hInst, // ������������� ����������
		NULL); // �������������� ������ ����

	ShowWindow(hWnd, SW_SHOW); // ���������� ����
	UpdateWindow(hWnd); // �������������� ����


		// ����������� ���� ��������� ���������
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// ������� ���������
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInst;
	//HBITMAP hbm;

	switch (msg)
	{
	case WM_CREATE:
		hInst = ((LPCREATESTRUCT)lParam)->hInstance;

		check_file();

		hBtn0 = CreateWindow("button", "�����",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			20, 240, 444, 30, hWnd, 0, hInst, NULL);
		ShowWindow(hBtn0, SW_SHOWNORMAL);

		hBtn[0] = CreateWindow("button", "button1",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			20, 240, 444, 30, hWnd, 0, hInst, NULL);
		ShowWindow(hBtn[0], SW_HIDE);

		hBtn[1] = CreateWindow("button", "button2",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			20, 290, 444, 30, hWnd, 0, hInst, NULL);
		ShowWindow(hBtn[1], SW_HIDE);

		hBtn[2] = CreateWindow("button", "button3",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			20, 340, 444, 30, hWnd, 0, hInst, NULL);
		ShowWindow(hBtn[2], SW_HIDE);

		hBtn[3] = CreateWindow("button", "button4",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			20, 390, 444, 30, hWnd, 0, hInst, NULL);
		ShowWindow(hBtn[3], SW_HIDE);

		hStat1 = CreateWindow("static", "",
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			20, 20, 444, 200, hWnd, 0, hInst, NULL);
		ShowWindow(hStat1, SW_SHOWNORMAL);

		/*hStat2 = CreateWindow("static", "",
			WS_CHILD | WS_VISIBLE | SS_BITMAP,
			284, 20, 200, 200, hWnd, 0, hInst, NULL);
		ShowWindow(hStat2, SW_SHOWNORMAL);*/



		break;
	case WM_COMMAND:
		if (lParam == (LPARAM)hBtn0)
		{
			SetFocus(hWnd);
			ShowWindow(hBtn0, SW_HIDE);
			read();
			/*
			ShowWindow(hBtn1, SW_HIDE);
			ShowWindow(hBtn2, SW_SHOW);
			ShowWindow(hBtn3, SW_SHOW);*/

			/*hbm = (HBITMAP)LoadImage(NULL, "skeleton.bmp",
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			SendMessage(hStat2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbm);*/

		}
		else if (lParam == (LPARAM)hBtn[0])
		{
			SetFocus(hWnd);
			for (int i = 0; i < 4; i++)
			{
				ShowWindow(hBtn[i], SW_HIDE);
			}
			read(hbtn[0]);
		}
		else if (lParam == (LPARAM)hBtn[1])
		{
			SetFocus(hWnd);
			for (int i = 0; i < 4; i++)
			{
				ShowWindow(hBtn[i], SW_HIDE);
			}
			read(hbtn[1]);
		}
		else if (lParam == (LPARAM)hBtn[2])
		{
			SetFocus(hWnd);
			for (int i = 0; i < 4; i++)
			{
				ShowWindow(hBtn[i], SW_HIDE);
			}
			read(hbtn[2]);
		}
		else if (lParam == (LPARAM)hBtn[3])
		{
			SetFocus(hWnd);
			for (int i = 0; i < 4; i++)
			{
				ShowWindow(hBtn[i], SW_HIDE);
			}
			read(hbtn[3]);
		}
		break;
	case WM_CHAR:
		break;
		/*
		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_LEFT:
				SetWindowText(hStat, "");
				break;
			case VK_RIGHT:
				SetWindowText(hStat, "");
				break;
			case VK_UP:
				SetWindowText(hStat, "");
				break;
			case VK_DOWN:
				SetWindowText(hStat, "");
				break;
			default:
				break;
			}
			break;
			*/

			/*case WM_PAINT:

				hBitmap = LoadImage(NULL, "icon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
				hcdc = CreateCompatibleDC(hdc);
				hOldBitmap = SelectObject(hcdc, hBitmap);
				GetClientRect(hWnd, &rect);
				StretchBlt(
					hdc,			 //HDC hdcDest,      ���������� ��������� DC
					0,				 //int nXOriginDest, x-�����. �������� ������ ���� ��������
					0,				 //int nYOriginDest, y-�����. �������� ������ ���� ��������
					rect.right,		 //int nWidthDest,   ������ �������� ��������������
					rect.bottom,	 //int nHeightDest,  ������ �������� ��������������.
					hcdc,			 //HDC hdcSrc,       ���������� ��������� DC
					0,				 //int nXOriginSrc,  x-�����.�������� ������ ���� ���������
					0,				 //int nYOriginSrc,  y-�����.�������� ������ ���� ���������
					Bitmap.bmWidth,  //int nWidthSrc,    ������ ��������� ��������������
					Bitmap.bmHeight, //int nHeightSrc,   ������ ��������� ��������������
					SRCCOPY			 //DWORD dwRop       ��� ��������� ��������
				);
				// ���� 30 ����� 8 ��� 8 ��� 8 �����
				SelectObject(hcdc, hOldBitmap);
				DeleteObject(hBitmap);
				DeleteDC(hcdc);

				hdc = BeginPaint(hWnd, &ps);
				TextOut(hdc, 50, 20, "Welcome to the dungeon", 23);
				EndPaint(hWnd, &ps);
				break;*/

	case WM_GETMINMAXINFO:
	{
		MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
		POINT Min = { 500, 500 };
		POINT  Max = { 500, 500 };
		pInfo->ptMinTrackSize = Min; // ���������� ����������� ������
		pInfo->ptMaxTrackSize = Max; // ���������� ������������ ������
		break;
	}
	case WM_DESTROY:
		fin.close();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}