#include "stdafx.h"
#include "GameOverWindow.h"
#include "Reg.h"

#define BTN_CLASS L"BUTTON"
#define BTN_TEXT L"Play again"
#define BTN_WIDTH 96
#define BTN_HEIGHT 32
#define BTN_MARGIN 8

GameOverWindow::GameOverWindow() : Window::Window() {
	setSize(metrics->thirdW, metrics->thirdH);
	alignCenter(metrics->halfW);
	alignMiddle(metrics->halfH);

	int highscore = Reg::getHighscore();
	if (Reg::score > highscore)
		highscore = Reg::score;
	Reg::setHighscore(highscore);

	msg = msg +
		L"Game over. Your score was: " +
		std::to_wstring(Reg::score) +
		L". Your best score is: " +
		std::to_wstring(highscore) +
		L".";

	RECT r1;
	GetClientRect(hWnd, &r1);
	HWND hWndButton = CreateWindow(BTN_CLASS, BTN_TEXT, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		(r1.right - r1.left - BTN_WIDTH) / 2, (r1.bottom - r1.top) - BTN_HEIGHT - BTN_MARGIN, BTN_WIDTH, BTN_HEIGHT,
		hWnd, NULL, Reg::inst, NULL);

	InvalidateRect(hWnd, 0, TRUE);
}

void GameOverWindow::onExit() {
	Window::onExit();
	Reg::toggleDesktopIconsVisible();
	PostQuitMessage(0);
	delete this;
}

void GameOverWindow::update(double elapsed) {
	Window::update(elapsed);
}

void GameOverWindow::onPaint(HDC hdc) {
	RECT rect;
	GetClientRect(hWnd, &rect);

	SetTextColor(hdc, 0x00000000);
	SetBkMode(hdc, TRANSPARENT);

	DrawText(hdc, msg.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void GameOverWindow::onCmd() {
	Reg::reset();
}

GameOverWindow::~GameOverWindow() {

}
