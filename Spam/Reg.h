#pragma once
#include "Metrics.h"
#include "Entity.h"
#include <random>

namespace Reg {

	extern Metrics* m;
	extern HINSTANCE inst;
	extern std::vector<Entity*> ents;
	extern std::mt19937 rng;

	extern void init(HINSTANCE hInst);
	extern std::wstring getRandomImage();
};
