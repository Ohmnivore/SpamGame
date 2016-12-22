#pragma once
#include "Window.h"

class EnemySlide : public Window {
public:
	EnemySlide();
	~EnemySlide();

	void onExit();
	void startSlide();
};
