#pragma once
#include "Window.h"

class EnemyBasic : public Window {
public:
	EnemyBasic();
	~EnemyBasic();
	void update(double elapsed);
	void onExit();
};

