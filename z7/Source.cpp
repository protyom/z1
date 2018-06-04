/*Пример 1-1. Простейшая программа с главным окном*/
/*Операторы препроцессора*/
#include <windows.h>//Два файла с определениями, макросами
#include <windowsx.h>//и прототипами функций Windows
#include <string.h>
#include <math.h>

/*Прототип используемой в программе функции пользователя*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*Главная функция WinMain*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmd)
{
	char szClassName[] = "MainWindow";//Имя класса главного окна
	char szTitle[] = "Программа 1-7";//Заголовок окна
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
		10, 10, 400, 270, //Координаты, размеры
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


HPEN hPen;//Дескрипторы новых перьев
HBRUSH hRedBrush, hGreenBrush, hSkyBrush, hSeaBrush, hGlassBrush, hBrownBrush,hWhiteBrush;//и новых кистей

														/*Оконная функция WndProc главного окна*/
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
		/*Создадим новые перья*/
		hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		/*Создадим новые кисти*/
		hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
		hGreenBrush = CreateSolidBrush(RGB(120, 255, 120));
		hSkyBrush = CreateSolidBrush(RGB(93, 163, 251));
		hSeaBrush = CreateSolidBrush(RGB(9, 56, 108));
		hGlassBrush = CreateSolidBrush(RGB(74, 123, 179));
		hBrownBrush = CreateSolidBrush(RGB(116, 74, 36));
		hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;//Структура для функции BeginPaint()


		hDC = BeginPaint(hWnd, &ps);//Получим контекст устройства



		/*Выведем четыре фигуры*/
		SelectPen(hDC, hPen);//Выберем в контекст новое перо
		SelectBrush(hDC, hSeaBrush);//и новую кисть
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
		EndPaint(hWnd, &ps);//Освободим контекст устройства
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

}//Конец функции WndProc