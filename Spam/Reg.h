#pragma once
#include "Metrics.h"
#include "Entity.h"

namespace Reg {

	Metrics* m;

	void init(HINSTANCE hInst) {
		Entity ent = Entity(hInst, nullptr);
		ent.setSize(0, 0);
		m = new Metrics(ent.hWnd);
	}
};
