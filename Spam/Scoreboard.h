#pragma once
#include "Entity.h"

class Scoreboard : Entity {
public:
	Scoreboard(HINSTANCE hInstance, Metrics* metrics);
	~Scoreboard();

	void update(double elapsed);
	void onExit();
};

