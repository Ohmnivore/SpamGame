#include "stdafx.h"
#include "Entity.h"
#include "Util.h"


Entity::Entity(HINSTANCE hInstance, Metrics* metrics) {
	this->metrics = metrics;

	wTitle = L"";
	wClass = L"SpamClass";

	width = height = x = y = velX = velY = 0;

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = wClass;
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassExW(&wcex);

	hInst = hInstance;
	hWnd = CreateWindowW(wClass, wTitle, WS_SYSMENU,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd)
		throw "Couldn't create window";
	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)this);
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
}

void Entity::update(double elapsed) {
	x += velX * elapsed;
	y += velY * elapsed;

	SetWindowPos(hWnd, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
}

void Entity::onExit() {

}

void Entity::setSize(int width, int height) {
	this->width = width;
	this->height = height;
	SetWindowPos(hWnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE);
}

void Entity::alignLeft(int x) {
	this->x = metrics->x(x);
}

void Entity::alignCenter(int x) {
	this->x = metrics->x(x) - (width / 2);
}

void Entity::alignRight(int x) {
	this->x = metrics->x(x) - width;
}

void Entity::alignTop(int y) {
	this->y = metrics->y(y);
}

void Entity::alignMiddle(int y) {
	this->y = metrics->y(y) - (height / 2);
}

void Entity::alignBot(int y) {
	this->y = metrics->y(y) - height;
}

LRESULT CALLBACK Entity::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	Entity* ent = reinterpret_cast<Entity*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (message) {
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_DESTROY:
			ent->onExit();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

Entity::~Entity() {
	wTitle = nullptr;
	wClass = nullptr;
	metrics = nullptr;

	CloseWindow(hWnd);
}
