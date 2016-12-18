#include "stdafx.h"
#include "EnemyBasic.h"
#include "Reg.h"
#include "Timer.h"
#include "GameOverWindow.h"

#define SCORE 1
#define SHAKE_DELAY 2

class GameOverTimer : public Timer {
	void trigger() {
		GameOverWindow* gw = new GameOverWindow();
		Reg::remove(this);
	}
};

EnemyBasic::EnemyBasic() : Window::Window() {
	score = SCORE;
}

void EnemyBasic::update(double elapsed) {
	Window::update(elapsed);

	if (y >= Reg::m->height && !Reg::paused) {
		Reg::paused = true;
		Reg::shake(SHAKE_DELAY);
		GameOverTimer* t = new GameOverTimer();
		t->start(SHAKE_DELAY);
	}
}

void EnemyBasic::onExit() {
	Window::onExit();
	Reg::remove(this);
}

EnemyBasic::~EnemyBasic() {
	
}
