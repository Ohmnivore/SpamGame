#include "stdafx.h"
#include "EnemySlide.h"
#include "Reg.h"
#include "Timer.h"

class SlideTween : public Timer {
public:
	EnemySlide* parent;
	double origin;
	double change;

	SlideTween(EnemySlide* par, double o, double d) : Timer() {
		parent = par;
		origin = o;
		change = d - o;
		start(2.0);
	}

	double easeOut(double t, double b, double c, double d) {
		return -c * ((t = t / d - 1)*t*t*t - 1) + b;
	}

	void update(double elapsed) {
		Timer::update(elapsed);
		parent->x = easeOut(this->elapsed, origin, change, time);
	}

	void trigger() {
		parent->velY = Reg::m->fourthH / 3.0;
		Reg::remove(this);
	}
};

EnemySlide::EnemySlide() : Window() {
	score = 2;
}

void EnemySlide::startSlide() {
	y = Reg::m->halfH - height / 2;

	int orgX;
	if (x + width / 2 > Reg::m->halfW)
		orgX = 0 - width;
	else
		orgX = Reg::m->width;
	new SlideTween(this, orgX, x);
}

void EnemySlide::onExit() {
	Window::onExit();
	Reg::remove(this);
}

EnemySlide::~EnemySlide() {

}
