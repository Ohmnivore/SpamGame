#include "stdafx.h"
#include "Spam.h"
#include "Metrics.h"
#include "Entity.h"

Metrics* metrics;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	Entity* ent = new Entity(hInstance, nullptr);
	metrics = new Metrics(ent->hWnd);
	ent->metrics = metrics;
	ent->setSize(metrics->eightW, metrics->eightH);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
