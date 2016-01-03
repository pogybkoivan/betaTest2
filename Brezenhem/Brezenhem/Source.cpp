#include "Brezenhem.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR mainMessage[] = "Ура!"; 
POINT startP{ 0, 0 };

//побудова вікна
int WINAPI WinMain(HINSTANCE hInst,
	HINSTANCE hPrevInst, 
	LPSTR lpCmdLine, 
	int nCmdShow)
{
	TCHAR szClassName[] = "Брезентхем";
	HWND hMainWnd;
	MSG msg;
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.cbWndExtra = NULL;
	wc.cbClsExtra = NULL;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hInstance = hInst;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Не получилось зарегистрировать класс!", "Ошибка", MB_OK);
		return NULL;
	}
	hMainWnd = CreateWindow(
		szClassName,
		"Брезенхем",
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		CW_USEDEFAULT,
		NULL,
		CW_USEDEFAULT,
		NULL,
		(HWND)NULL,
		NULL,
		HINSTANCE(hInst),
		NULL);
	if (!hMainWnd)
	{
		MessageBox(NULL, "Не получилось создать окно!", "Ошибка", MB_OK);
		return NULL;
	}
	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	HDC hDC;
	vector < POINT > vec;
	POINT lastP;
	switch (uMsg)
	{
	case WM_PAINT:
		break;
	case WM_LBUTTONDOWN:
		//запамятати першу координату лінії
		startP = { LOWORD(lParam), HIWORD(lParam) };
		break;
	case WM_LBUTTONUP:
		//запамятати останню координату лінії
		lastP = { LOWORD(lParam), HIWORD(lParam) };
		hDC = GetDC(hWnd);
		vec = Brezenhem::genereteVec(startP, lastP);
		for (unsigned int i = 0; i < vec.size(); i++)
			SetPixel(hDC, vec[i].x, vec[i].y, RGB(255, 0, 0));
		ReleaseDC(hWnd, hDC);
		break;
	case WM_DESTROY:
		PostQuitMessage(NULL);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return NULL;
}