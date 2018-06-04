/*������ 1-1. ���������� ��������� � ������� �����*/
/*��������� �������������*/
#include <windows.h>//��� ����� � �������������, ���������
#include <windowsx.h>//� ����������� ������� Windows
#include "resource.h"

/*�������� ������������ � ��������� ������� ������������*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*������� ������� WinMain*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmd)
{
	char szClassName[] = "MainWindow";//��� ������ �������� ����
	char szTitle[] = "��������� 1-1";//��������� ����
	MSG msg;//��������� msg ��� ��������� ��������� Windows
	WNDCLASS wc;//��������� wc ��� ������� ������������� ����

				/*�������������� ����� �������� ����*/
	ZeroMemory(&wc, sizeof(wc));//��������� ���� ������ wc
	wc.lpfnWndProc = WndProc;//���������� ������� ���������
	wc.hInstance = hInst;//���������� ����������
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);//�����������
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//������ ����
	wc.hbrBackground = GetStockBrush(WHITE_BRUSH);//����� ���
	wc.lpszClassName = szClassName;

	RegisterClass(&wc);//���������� ����������� ������ ����

					   /*�������� ������� ���� � ������� ��� �������*/
	HWND hwnd = CreateWindow(LPCSTR(szClassName),//����� ����
		LPCSTR(szTitle), WS_OVERLAPPEDWINDOW,//���������, ����� ����
		10, 10, 500, 300, //����������, �������
		NULL, NULL,//��������, ����
		hInst, NULL);//���������� ����������, ���������
	ShowWindow(hwnd, nCmd);//������� ����

						   /*���������� ���� ��������� ���������*/
	while (GetMessage(&msg, NULL, 0, 0))//�������� ���������,
	{
		TranslateMessage(&msg);//������� ��������� � ��� �������
		DispatchMessage(&msg);//������� WndProc
	}
	return 0;//����� ������ �� ����� ��������� � Windows
}//����� ������� WinMain

HPEN hPen;
HBRUSH hBrush;

 /*������� ������� WndProc �������� ����*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	switch (msg)
	{
	case WM_CREATE:
		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		hBrush = CreateSolidBrush(RGB(150, 150, 150));
	case WM_PAINT:
		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		SelectPen(hDC, hPen);
		SelectBrush(hDC, hBrush);
		Rectangle(hDC, rect.left + 10, rect.top + 10, rect.right - 10, rect.bottom - 10);
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		DeleteObject(hPen);
		DeleteObject(hBrush);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	
}//����� ������� WndProc