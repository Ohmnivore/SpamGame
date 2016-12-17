#include "stdafx.h"
#include "GameOverWindow.h"
#include "Util.h"
#include "Reg.h"

GameOverWindow::GameOverWindow() : Window::Window() {
	setSize(metrics->thirdW, metrics->thirdH);
	alignCenter(metrics->halfW);
	alignMiddle(metrics->halfH);
}

void GameOverWindow::onExit() {
	toggleDesktopIconsVisible();
	PostQuitMessage(0);
}

void GameOverWindow::update(double elapsed) {
	Window::update(elapsed);
	InvalidateRect(hWnd, 0, TRUE);
}

void GameOverWindow::onPaint(HDC hdc) {
	RECT rect;
	GetClientRect(hWnd, &rect);

	SetTextColor(hdc, 0x00000000);
	SetBkMode(hdc, TRANSPARENT);

	WCHAR buf[32];
	DrawText(hdc, L"Game over. Your score was: ", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

GameOverWindow::~GameOverWindow() {
}
