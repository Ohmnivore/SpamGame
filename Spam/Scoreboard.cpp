#include "stdafx.h"
#include "Scoreboard.h"
#include "Reg.h"

Scoreboard::Scoreboard() : Window::Window() {
	setSize(metrics->eightW, metrics->eightH);
	alignRight(metrics->width);
	alignBot(metrics->height);

	oldScore = -1;
}

void Scoreboard::update(double elapsed) {
	Window::update(elapsed);

	if (oldScore != Reg::score) {
		oldScore = Reg::score;
		InvalidateRect(hWnd, 0, TRUE);
	}
}

void Scoreboard::onExit() {
	Reg::toggleDesktopIconsVisible();
	PostQuitMessage(0);
	delete this;
}

void Scoreboard::onPaint(HDC hdc) {
	RECT rect;
	GetClientRect(hWnd, &rect);

	SetTextColor(hdc, 0x00000000);
	SetBkMode(hdc, TRANSPARENT);

	WCHAR buf[32];
	DrawText(hdc, _itow(Reg::score, buf, 10), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

Scoreboard::~Scoreboard() {
}
