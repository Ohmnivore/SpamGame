#include "stdafx.h"
#include "Spam.h"
#include "Metrics.h"
#include "Entity.h"
#include "Scoreboard.h"
#include "Util.h"
#include <vector>
using namespace std;

vector<Entity*> ents;
Metrics* metrics;
int lastTick;
const int frameMS = 16;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	toggleDesktopIconsVisible();

	Entity* ent = (Entity*)(new Scoreboard(hInstance, nullptr));
	ents.push_back(ent);
	metrics = new Metrics(ent->hWnd);
	ent->metrics = metrics;
	ent->setSize(metrics->eightW, metrics->eightH);
	ent->alignRight(metrics->width);
	ent->alignBot(metrics->height);

	Entity* ent2 = new Entity(hInstance, metrics);
	ents.push_back(ent2);
	ent2->setSize(metrics->eightW, metrics->eightH);
	ent2->alignTop(0);
	ent2->alignCenter(metrics->fourthH);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

		int nowTick = GetTickCount();
		int delta = nowTick - lastTick;
		if (delta >= frameMS) {
			lastTick = nowTick;
			for (Entity* e : ents) {
				ent->update(delta * 1000.0);
			}
		}
    }
    return (int)msg.wParam;
}
