#pragma once
#include "Metrics.h"
#include "Entity.h"
#include <vector>

namespace Reg {

	extern Metrics* m;
	extern HINSTANCE inst;
	extern std::vector<Entity*> ents;

	extern void init(HINSTANCE hInst);
};
