#include "stdafx.h"
#include "Metrics.h"


Metrics::Metrics(HWND hWnd) {
	HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);
	MONITORINFO mInfo;
	mInfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &mInfo);

	left = mInfo.rcWork.left;
	right = mInfo.rcWork.right;
	top = mInfo.rcWork.top;
	bot = mInfo.rcWork.bottom;
	width = right - left;
	height = bot - top;

	halfW   = width / 2;
	thirdW  = width / 3;
	fourthW = width / 4;
	sixthW  = width / 5;
	eightW  = width / 8;

	halfH   = height / 2;
	thirdH  = height / 3;
	fourthH = height / 4;
	sixthH  = height / 6;
	eightH  = height / 8;
}

int Metrics::x(int x) {
	return x + left;
}

int Metrics::y(int y) {
	return y + top;
}

Metrics::~Metrics() {
}
