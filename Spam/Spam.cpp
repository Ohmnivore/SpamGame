#include "stdafx.h"
#include "Spam.h"
#include "Metrics.h"
#include "Entity.h"
#include "Scoreboard.h"
#include "Util.h"
#include "Reg.h"
#include <vector>
using namespace std;

vector<Entity*> ents;
int lastTick;
const int frameMS = 16;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	toggleDesktopIconsVisible();
	Reg::init(hInstance);

	Entity* ent = (Entity*)(new Scoreboard(hInstance, Reg::m));
	ents.push_back(ent);
	ent->setSize(Reg::m->eightW, Reg::m->eightH);
	ent->alignRight(Reg::m->width);
	ent->alignBot(Reg::m->height);

	Entity* ent2 = new Entity(hInstance, Reg::m);
	ents.push_back(ent2);
	ent2->setSize(Reg::m->eightW, Reg::m->eightH);
	ent2->alignTop(0);
	ent2->alignCenter(Reg::m->fourthH);
	ent2->velY = Reg::m->eightH;

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
			if (!lastTick)
				lastTick = GetTickCount();
			int nowTick = GetTickCount();
			int delta = nowTick - lastTick;
			if (delta >= frameMS) {
				lastTick = nowTick;
				for (Entity* e : ents) {
					e->update(delta / 1000.0);
				}
			}
		}
	}
    return (int)msg.wParam;
}
