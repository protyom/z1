/*Пример 1-1. Простейшая программа с главным окном*/
/*Операторы препроцессора*/
#include <windows.h>//Два файла с определениями, макросами
#include <windowsx.h>//и прототипами функций Windows
#include <ctime>
#include <cstdlib>

/*Прототип используемой в программе функции пользователя*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*Главная функция WinMain*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmd)
{
	srand(time(NULL));
	char szClassName[] = "MainWindow";//Имя класса главного окна
	char szTitle[] = "Программа 1-6";//Заголовок окна
	MSG msg;//Структура msg для получения сообщений Windows
	WNDCLASS wc;//Структура wc для задания характеристик окна

				/*Зарегистрируем класс главного окна*/
	ZeroMemory(&wc, sizeof(wc));//Обнуление всех членов wc
	wc.lpfnWndProc = WndProc;//Определяем оконную процедуру
	wc.hInstance = hInst;//Дескриптор приложения
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);//Пиктограмма
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//Курсор мыши
	wc.hbrBackground = GetStockBrush(WHITE_BRUSH);//Белый фон
	wc.lpszClassName = szClassName;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);//Собственно регистрация класса окна

					   /*Создадим главное окно и сделаем его видимым*/
	HWND hwnd = CreateWindow(LPCSTR(szClassName),//Класс окна
		LPCSTR(szTitle), WS_OVERLAPPEDWINDOW,//Заголовок, стиль окна
		10, 10, 500, 300, //Координаты, размеры
		NULL, NULL,//Родитель, меню
		hInst, NULL);//Дескриптор приложения, параметры
	ShowWindow(hwnd, nCmd);//Покажем окно

						   /*Организуем цикл обработки сообщений*/
	while (GetMessage(&msg, NULL, 0, 0))//Получить сообщение,
	{
		TranslateMessage(&msg);//Перевод сообщения в код символа
		DispatchMessage(&msg);//вызвать WndProc
	}
	return 0;//После выхода из цикла вернуться в Windows
}//Конец функции WinMain

HPEN hPen;

/*Оконная функция WndProc главного окна*/
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

}//Конец функции WndProc