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
	extern double shakeX;
	extern double shakeY;

	extern void init(HINSTANCE hInst);
	extern void update(double elapsed);
	extern std::wstring getRandomImage();
	extern void shake(double length = 1.0, double intensity = 0.01);
};
