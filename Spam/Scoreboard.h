#pragma once
#include "Window.h"

class Scoreboard : public Window {
public:
	Scoreboard();
	~Scoreboard();

	void update(double elapsed);
	void onExit();
	void onPaint(HDC hdc);

private:
	int oldScore;
};

