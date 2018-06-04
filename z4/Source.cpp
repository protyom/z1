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
	char szTitle[] = "Программа 1-4";//Заголовок окна
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


HPEN hRedPen, hGreenPen, hBluePen,hOrangePen;//Дескрипторы новых перьев
HBRUSH hRedBrush, hGreenBrush, hBlueBrush,hOrangeBrush;//и новых кистей

										  /*Оконная функция WndProc главного окна*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	POINT lpPoints[] = { { 370,90 },{ 420,40 },{ 470,90 },{ 420,140 } };//координаты ромба
	char szText1[] = "Эллипс";//Просто
	char szText2[] = "Прямоугольник";  //надписи
	char szText3[] = "Сектор";      //над
	char szText4[] = "Ромб";    //фигурами
	switch (msg)
	{
	case WM_CREATE:
		/*Создадим новые перья*/
		hRedPen = CreatePen(PS_SOLID, 4, RGB(150, 0, 0));
		hGreenPen = CreatePen(PS_SOLID, 4, RGB(0, 150, 0));
		hBluePen = CreatePen(PS_SOLID, 20, RGB(0, 0, 150));
		hOrangePen = CreatePen(PS_SOLID, 5, RGB(195, 85, 0));
		/*Создадим новые кисти*/
		hRedBrush = CreateSolidBrush(RGB(255, 120, 120));
		hGreenBrush = CreateSolidBrush(RGB(120, 255, 120));
		hBlueBrush = CreateSolidBrush(RGB(120, 120, 255));
		hOrangeBrush= CreateSolidBrush(RGB(238, 164, 99));
		break;
	case WM_PAINT:


		hDC = BeginPaint(hWnd, &ps);//Получим контекст устройства

		SetBkColor(hDC, RGB(200, 200, 100));//Фон под текстом
		SetTextColor(hDC, RGB(0, 0, 200));//Синий цвет текста

										  /*Выведем четыре строки текста*/
		TextOut(hDC, 25, 5, szText1, strlen(szText1));
		TextOut(hDC, 125, 5, szText2, strlen(szText2));
		TextOut(hDC, 280, 5, szText3, strlen(szText3));
		TextOut(hDC, 395, 5, szText4, strlen(szText4));

		/*Выведем четыре фигуры*/
		SelectPen(hDC, hRedPen);//Выберем в контекст новое перо
		SelectBrush(hDC, hRedBrush);//и новую кисть
		Ellipse(hDC, 10, 40, 110, 140);
		SelectPen(hDC, hOrangePen);//Выберем в контекст новое перо
		SelectBrush(hDC, hOrangeBrush);//и новую кисть
		Rectangle(hDC, 130, 40, 230, 140);

		SelectPen(hDC, hGreenPen);//Выберем новое перо
		SelectBrush(hDC, hGreenBrush);//и новую кисть
		BeginPath(hDC);
		MoveToEx(hDC, 300, 90, (LPPOINT)NULL);
		AngleArc(hDC, 300, 90, 50, 0.,30.);//Сектор
		LineTo(hDC,300,90);
		EndPath(hDC);
		StrokeAndFillPath(hDC);

		SelectPen(hDC, hBluePen);//Выберем новое перо
		SelectBrush(hDC, hBlueBrush);//и новую кисть
		Polygon(hDC,lpPoints,4);//Ромб

		EndPaint(hWnd, &ps);//Освободим контекст устройства
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

}//Конец функции WndProc
