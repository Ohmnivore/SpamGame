#include "stdafx.h"
#include "EnemyBasic.h"
#include "Reg.h"
#include "Timer.h"
#include "GameOverWindow.h"

class GameOverTimer : public Timer {
	void trigger() {
		GameOverWindow* gw = new GameOverWindow();
		Reg::add(gw);

		delete this;
	}
};

EnemyBasic::EnemyBasic() : Window::Window() {
	score = 1;
}

void EnemyBasic::update(double elapsed) {
	Window::update(elapsed);

	if (y >= Reg::m->height && !Reg::paused) {
		Reg::paused = true;
		Reg::shake(2.0);
		GameOverTimer* t = new GameOverTimer();
		t->start(2.0);
	}
}

EnemyBasic::~EnemyBasic() {
}
