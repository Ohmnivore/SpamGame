#include "stdafx.h"
#include "GameOverWindow.h"
#include "Util.h"
#include "Reg.h"

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

	DrawText(hdc, msg.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

GameOverWindow::~GameOverWindow() {
}
