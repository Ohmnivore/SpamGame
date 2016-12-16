#pragma once
#include "Entity.h"
#include "Metrics.h"
#include "Window.h"
#include <random>
#include <list>

namespace Reg {

	extern Metrics* m;
	extern HINSTANCE inst;
	extern std::list<Entity*> ents;
	extern std::mt19937 rng;
	extern int score;

	extern void init(HINSTANCE hInst);
	extern std::wstring getRandomImage();
};
