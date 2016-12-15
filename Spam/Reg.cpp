#include "stdafx.h"
#include "Reg.h"

namespace Reg {

	Metrics* m;
	HINSTANCE inst;
	std::vector<Entity*> ents;

	void init(HINSTANCE hInst) {
		Entity ent = Entity(hInst, nullptr);
		ent.setSize(0, 0);
		m = new Metrics(ent.hWnd);
		inst = hInst;
	}
};