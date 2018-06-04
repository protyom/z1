/*������ 1-1. ���������� ��������� � ������� �����*/
/*��������� �������������*/
#include <windows.h>//��� ����� � �������������, ���������
#include <windowsx.h>//� ����������� ������� Windows
#include <string.h>
#include <math.h>

/*�������� ������������ � ��������� ������� ������������*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*������� ������� WinMain*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmd)
{
	char szClassName[] = "MainWindow";//��� ������ �������� ����
	char szTitle[] = "��������� 1-7";//��������� ����
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
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);//���������� ����������� ������ ����

					   /*�������� ������� ���� � ������� ��� �������*/
	HWND hwnd = CreateWindow(LPCSTR(szClassName),//����� ����
		LPCSTR(szTitle), WS_OVERLAPPEDWINDOW,//���������, ����� ����
		10, 10, 400, 270, //����������, �������
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


HPEN hPen;//����������� ����� ������
HBRUSH hRedBrush, hGreenBrush, hSkyBrush, hSeaBrush, hGlassBrush, hBrownBrush,hWhiteBrush;//� ����� ������

														/*������� ������� WndProc �������� ����*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	POINT lpBody[] = { { 100,140 },{ 260,140 },{ 230,160 },{ 130,160 } };
	POINT lpPar1[] = { { 120,130 },{ 178,70 },{ 178,130 } };
	POINT lpPar2[] = { { 183,70 },{ 195,138 },{ 183,138 } };
	POINT lpPar3[] = { { 243,80 },{ 253,138 },{ 243,138 } };
	POINT lpFlag[] = { { 183,60 },{ 213,60 },{ 203,65 },{ 213,70 },{183,70} };
	POINT lpLine[] = { { 112,148 },{ 248,148 },{ 241,153 },{ 120,153 } };
	POINT pOld = { 120,130 };
	switch (msg)
	{
	case WM_CREATE:
		/*�������� ����� �����*/
		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		/*�������� ����� �����*/
		hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
		hGreenBrush = CreateSolidBrush(RGB(120, 255, 120));
		hSkyBrush = CreateSolidBrush(RGB(93, 163, 251));
		hSeaBrush = CreateSolidBrush(RGB(9, 56, 108));
		hGlassBrush = CreateSolidBrush(RGB(74, 123, 179));
		hBrownBrush = CreateSolidBrush(RGB(116, 74, 36));
		hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;//��������� ��� ������� BeginPaint()


		hDC = BeginPaint(hWnd, &ps);//������� �������� ����������



		/*������� ������ ������*/
		SelectPen(hDC, hPen);//������� � �������� ����� ����
		SelectBrush(hDC, hSeaBrush);//� ����� �����
		Rectangle(hDC, 0, 160,400,270);
		SelectBrush(hDC, hSkyBrush);
		Rectangle(hDC, 0, 0, 400, 160);

		SelectBrush(hDC, hWhiteBrush);
		Polygon(hDC, lpBody, 4);
		SelectBrush(hDC, hGreenBrush);
		Polygon(hDC, lpLine, 4);
		SelectBrush(hDC, hGlassBrush);
		Ellipse(hDC, 140, 145, 150, 155);
		Ellipse(hDC, 175, 145, 185, 155);
		Ellipse(hDC, 210, 145, 220, 155);
		SelectBrush(hDC, hBrownBrush);
		Rectangle(hDC, 178, 70, 183, 140);
		Rectangle(hDC, 238, 80, 243, 140);
		SelectBrush(hDC, hWhiteBrush);
		MoveToEx(hDC, 100, 140, NULL);
		LineTo(hDC, 120, 130);
		MoveToEx(hDC, 253, 138, NULL);
		LineTo(hDC, 260, 140);
		Polygon(hDC, lpPar1, 3);
		Polygon(hDC, lpPar2, 3);
		Polygon(hDC, lpPar3, 3);
		SelectBrush(hDC, hRedBrush);
		Polygon(hDC, lpFlag, 5);
		EndPaint(hWnd, &ps);//��������� �������� ����������
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		DeleteObject(hPen);
		DeleteObject(hRedBrush);
		DeleteObject(hSkyBrush);
		DeleteObject(hGreenBrush);
		DeleteObject(hSeaBrush);
		DeleteObject(hGlassBrush);
		DeleteObject(hWhiteBrush);
		DeleteObject(hBrownBrush);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

}//����� ������� WndProc