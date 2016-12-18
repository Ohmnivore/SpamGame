#include "stdafx.h"
#include "Window.h"
#include "Reg.h"


Window::Window() {
	Reg::add(this);
	this->metrics = Reg::m;

	wTitle = L"";
	wClass = L"SpamClass";
	score = 0;
	closed = false;

	width = height = x = y = velX = velY = 0;

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = Reg::inst;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = wClass;
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassExW(&wcex);

	hInst = Reg::inst;
	hWnd = CreateWindowW(wClass, wTitle, WS_SYSMENU,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
	if (!hWnd)
		throw "Couldn't create window";
	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)this);
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
}

void Window::loadImage(std::wstring path) {
	hImg = (HBITMAP)LoadImage(NULL, (LPCWSTR)path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);
	if (hImg == NULL)
		throw "Couldn't load image";
}

void Window::update(double elapsed) {
	if (!Reg::paused) {
		x += velX * elapsed;
		y += velY * elapsed;
	}

	SetWindowPos(hWnd, HWND_TOP, x + Reg::shakeX, y + Reg::shakeY, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
	UpdateWindow(hWnd);
}

void Window::onExit() {
	closed = true;
	if (!Reg::paused)
		Reg::score += score;
}

void Window::onPaint(HDC hdc) {

}

void Window::onCmd() {

}

void Window::setSize(int width, int height) {
	if (height > width)
		height = width;
	this->width = width;
	this->height = height;
	SetWindowPos(hWnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE);
}

void Window::alignLeft(int x) {
	this->x = metrics->x(x);
}

void Window::alignCenter(int x) {
	this->x = metrics->x(x) - (width / 2);
}

void Window::alignRight(int x) {
	this->x = metrics->x(x) - width;
}

void Window::alignTop(int y) {
	this->y = metrics->y(y);
}

void Window::alignMiddle(int y) {
	this->y = metrics->y(y) - (height / 2);
}

void Window::alignBot(int y) {
	this->y = metrics->y(y) - height;
}

LRESULT CALLBACK Window::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	Window* ent = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (message) {
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			if (ent->hWnd != NULL)
				ent->onPaint(hdc);

			if (ent->hImg == NULL)
				EndPaint(hWnd, &ps);
			else {
				RECT rect;
				GetClientRect(hWnd, &rect);
				int clientWidth = rect.right - rect.left;
				int clientHeight = rect.bottom - rect.top;
				int orgWidth = 1280;
				int orgHeight = 640;
				int srcWidth = 0;
				int srcHeight = 0;
				double clientRatio = (double)clientHeight / (double)clientWidth;
				double orgRatio = (double)orgHeight / (double)orgWidth;

				srcWidth = orgWidth;
				srcHeight = (double)orgHeight * (clientRatio / orgRatio);

				HDC hdcMem = CreateCompatibleDC(hdc);
				SelectObject(hdcMem, ent->hImg);
				SetStretchBltMode(hdc, COLORONCOLOR);
				StretchBlt(
					hdc,               // destination DC
					0,                 // x upper left
					0,                 // y upper left
					clientWidth,       // destination width
					clientHeight,      // destination height
					hdcMem,            // you just created this above
					0,                 // x upper left
					0,                 // y upper left
					srcWidth,          // source bitmap width
					srcHeight,         // source bitmap height
					SRCCOPY);          // raster operation
				DeleteDC(hdcMem);
				EndPaint(hWnd, &ps);
			}
			break;
		}
		case WM_COMMAND:
			ent->onCmd();
			break;
		case WM_DESTROY:
			if (!ent->closed)
				ent->onExit();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

Window::~Window() {
	Reg::remove(this);

	wTitle = nullptr;
	wClass = nullptr;
	metrics = nullptr;

	CloseWindow(hWnd);
	DestroyWindow(hWnd);
}
