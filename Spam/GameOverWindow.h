#pragma once
#include "Window.h"

class GameOverWindow : public Window {
public:
	GameOverWindow();
	~GameOverWindow();

	void update(double elapsed);
	void onExit();
	void onPaint(HDC hdc);
	void onCmd();

private:
	std::wstring msg;
};
