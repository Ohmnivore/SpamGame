#include "stdafx.h"
#include "Spam.h"
#include "Metrics.h"
#include "Window.h"
#include "Scoreboard.h"
#include "Util.h"
#include "Reg.h"
#include "Spawner.h"
using namespace std;

int lastTick;
const int frameMS = 16;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	toggleDesktopIconsVisible();
	Reg::init(hInstance);

	Scoreboard* scoreBoard = new Scoreboard(Reg::inst, Reg::m);
	Reg::ents.push_back((Entity*)scoreBoard);
	scoreBoard->setSize(Reg::m->eightW, Reg::m->eightH);
	scoreBoard->alignRight(Reg::m->width);
	scoreBoard->alignBot(Reg::m->height);

	Spawner* s1 = new Spawner(Reg::m->thirdW * 0.5 + Reg::m->margin / 2, 0);
	s1->spawn();
	Spawner* s2 = new Spawner(Reg::m->thirdW * 1.5, 0);
	s2->spawn();
	Spawner* s3 = new Spawner(Reg::m->thirdW * 2.5 - Reg::m->margin / 2, 0);
	s3->spawn();
	Reg::ents.push_back((Entity*)s1);
	Reg::ents.push_back((Entity*)s2);
	Reg::ents.push_back((Entity*)s3);

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
				for (Entity* e : Reg::ents) {
					e->update(delta / 1000.0);
				}
			}
		}
	}
    return (int)msg.wParam;
}
