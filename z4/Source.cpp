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
	char szTitle[] = "��������� 1-4";//��������� ����
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


HPEN hRedPen, hGreenPen, hBluePen,hOrangePen;//����������� ����� ������
HBRUSH hRedBrush, hGreenBrush, hBlueBrush,hOrangeBrush;//� ����� ������

										  /*������� ������� WndProc �������� ����*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	POINT lpPoints[] = { { 370,90 },{ 420,40 },{ 470,90 },{ 420,140 } };//���������� �����
	char szText1[] = "������";//������
	char szText2[] = "�������������";  //�������
	char szText3[] = "������";      //���
	char szText4[] = "����";    //��������
	switch (msg)
	{
	case WM_CREATE:
		/*�������� ����� �����*/
		hRedPen = CreatePen(PS_SOLID, 4, RGB(150, 0, 0));
		hGreenPen = CreatePen(PS_SOLID, 4, RGB(0, 150, 0));
		hBluePen = CreatePen(PS_SOLID, 20, RGB(0, 0, 150));
		hOrangePen = CreatePen(PS_SOLID, 5, RGB(195, 85, 0));
		/*�������� ����� �����*/
		hRedBrush = CreateSolidBrush(RGB(255, 120, 120));
		hGreenBrush = CreateSolidBrush(RGB(120, 255, 120));
		hBlueBrush = CreateSolidBrush(RGB(120, 120, 255));
		hOrangeBrush= CreateSolidBrush(RGB(238, 164, 99));
		break;
	case WM_PAINT:


		hDC = BeginPaint(hWnd, &ps);//������� �������� ����������

		SetBkColor(hDC, RGB(200, 200, 100));//��� ��� �������
		SetTextColor(hDC, RGB(0, 0, 200));//����� ���� ������

										  /*������� ������ ������ ������*/
		TextOut(hDC, 25, 5, szText1, strlen(szText1));
		TextOut(hDC, 125, 5, szText2, strlen(szText2));
		TextOut(hDC, 280, 5, szText3, strlen(szText3));
		TextOut(hDC, 395, 5, szText4, strlen(szText4));

		/*������� ������ ������*/
		SelectPen(hDC, hRedPen);//������� � �������� ����� ����
		SelectBrush(hDC, hRedBrush);//� ����� �����
		Ellipse(hDC, 10, 40, 110, 140);
		SelectPen(hDC, hOrangePen);//������� � �������� ����� ����
		SelectBrush(hDC, hOrangeBrush);//� ����� �����
		Rectangle(hDC, 130, 40, 230, 140);

		SelectPen(hDC, hGreenPen);//������� ����� ����
		SelectBrush(hDC, hGreenBrush);//� ����� �����
		BeginPath(hDC);
		MoveToEx(hDC, 300, 90, (LPPOINT)NULL);
		AngleArc(hDC, 300, 90, 50, 0.,30.);//������
		LineTo(hDC,300,90);
		EndPath(hDC);
		StrokeAndFillPath(hDC);

		SelectPen(hDC, hBluePen);//������� ����� ����
		SelectBrush(hDC, hBlueBrush);//� ����� �����
		Polygon(hDC,lpPoints,4);//����

		EndPaint(hWnd, &ps);//��������� �������� ����������
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		DeleteObject(hRedPen);
		DeleteObject(hGreenPen);
		DeleteObject(hBluePen);
		DeleteObject(hRedBrush);
		DeleteObject(hBlueBrush);
		DeleteObject(hGreenBrush);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

}//����� ������� WndProc
