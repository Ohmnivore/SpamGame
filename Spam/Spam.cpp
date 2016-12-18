#include "stdafx.h"
#include "Spam.h"
#include "Metrics.h"
#include "Window.h"
#include "Scoreboard.h"
#include "Reg.h"
#include "Spawner.h"
#include "resource.h"
using namespace std;

int lastTick;
const int frameMS = 16;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	Reg::toggleDesktopIconsVisible();
	Reg::init(hInstance);

	MSG msg;
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				break;
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			int nowTick = GetTickCount();
			if (!lastTick)
				lastTick = nowTick;
			int delta = nowTick - lastTick;

			if (delta >= frameMS) {
				lastTick = nowTick;
				double elapsed = delta / 1000.0;
				Reg::update(elapsed);
				for (Entity* e : Reg::ents) {
					e->update(elapsed);
				}
			}
		}
	}
    return (int)msg.wParam;
}
