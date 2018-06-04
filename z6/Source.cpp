/*������ 1-1. ���������� ��������� � ������� �����*/
/*��������� �������������*/
#include <windows.h>//��� ����� � �������������, ���������
#include <windowsx.h>//� ����������� ������� Windows
#include <ctime>
#include <cstdlib>

/*�������� ������������ � ��������� ������� ������������*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*������� ������� WinMain*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmd)
{
	srand(time(NULL));
	char szClassName[] = "MainWindow";//��� ������ �������� ����
	char szTitle[] = "��������� 1-6";//��������� ����
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
	case WM_PAINT:
		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		SelectPen(hDC, hPen);
		//InvalidateRect(hWnd, &rect,FALSE);
		for (int nI = 0;nI < 26;nI++)
		{
			HBRUSH hBrush = CreateSolidBrush(RGB(238-nI*9,164-nI*3, 99+nI*5));
			HBRUSH hOld = (HBRUSH)SelectObject(hDC, hBrush);
			rect.left += 5; rect.top += 5; rect.right -= 5; rect.bottom -= 5;
			FillRect(hDC, &rect ,hBrush);
			DeleteObject(SelectObject(hDC, hOld));
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		DeleteObject(hPen);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

}//����� ������� WndProc