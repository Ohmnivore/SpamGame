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
}


Metrics::~Metrics() {
}
