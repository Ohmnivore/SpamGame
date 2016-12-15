#include "stdafx.h"
#include "Spam.h"
#include "Metrics.h"
#include "Entity.h"
#include "Scoreboard.h"
#include "Util.h"
#include "Reg.h"
#include "Spawner.h"
using namespace std;

int lastTick;
const int frameMS = 16;
std::vector<Spawner*> spawns;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	toggleDesktopIconsVisible();
	Reg::init(hInstance);

	spawns.push_back(new Spawner(Reg::m->thirdW * 0.5 + Reg::m->margin / 2, 0));
	spawns.push_back(new Spawner(Reg::m->thirdW * 1.5, 0));
	spawns.push_back(new Spawner(Reg::m->thirdW * 2.5 - Reg::m->margin / 2, 0));

	for (Spawner* s : spawns) {
		s->spawn();
	}

	Entity* ent = (Entity*)(new Scoreboard(Reg::inst, Reg::m));
	Reg::ents.push_back(ent);
	ent->setSize(Reg::m->eightW, Reg::m->eightH);
	ent->alignRight(Reg::m->width);
	ent->alignBot(Reg::m->height);

	/*Entity* ent2 = new Entity(Reg::inst, Reg::m);
	Reg::ents.push_back(ent2);
	ent2->setSize(Reg::m->eightW, Reg::m->eightH);
	ent2->alignTop(0);
	ent2->alignCenter(Reg::m->fourthH);
	ent2->velY = Reg::m->eightH;*/

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
				for (Entity* e : Reg::ents) {
					e->update(elapsed);
				}
				for (Spawner* s : spawns) {
					s->update(elapsed);
				}
			}
		}
	}
    return (int)msg.wParam;
}
