/*������ 1-1. ���������� ��������� � ������� �����*/
/*��������� �������������*/
#include <windows.h>//��� ����� � �������������, ���������
#include <windowsx.h>//� ����������� ������� Windows

/*�������� ������������ � ��������� ������� ������������*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*������� ������� WinMain*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmd)
{
	char szClassName[] = "MainWindow";//��� ������ �������� ����
	char szTitle[] = "��������� 1-3";//��������� ����
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
HBRUSH hBrush;

/*������� ������� WndProc �������� ����*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	RECT rect;
	switch (msg)
	{
	case WM_CREATE:
		hPen = CreatePen(PS_SOLID, 2, RGB(150, 0, 0));
		hBrush = CreateSolidBrush(RGB(255, 150, 150));
		break;
	case WM_PAINT:
		RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		DrawText(hDC, "������ �����", -1, &rect, DT_TOP | DT_LEFT|DT_SINGLELINE);
		DrawText(hDC, "������ ������", -1, &rect, DT_TOP | DT_RIGHT | DT_SINGLELINE);
		DrawText(hDC, "������ �����", -1, &rect, DT_BOTTOM | DT_LEFT | DT_SINGLELINE);
		DrawText(hDC, "����� ������", -1, &rect, DT_BOTTOM | DT_RIGHT | DT_SINGLELINE);
		DrawText(hDC, "�� ������", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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