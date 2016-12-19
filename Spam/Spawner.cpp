#include "stdafx.h"
#include "Spawner.h"
#include "Window.h"
#include "Reg.h"
#include <random>
#include "EnemyBasic.h"

double roll() {
	std::uniform_real_distribution<double> uni(0.0, 1.0);
	return uni(Reg::rng);
}

void Spawner::setupBasicEnemy(Window* ent) {
	ent->loadImage(Reg::getRandomImage());
	ent->setSize(Reg::m->thirdW - Reg::m->margin * 2, Reg::m->thirdH - Reg::m->margin * 2);
	ent->alignCenter(x);
	ent->alignBot(y);
}

Spawner::Spawner(int x, int y) {
	this->x = x;
	this->y = y;
}

void Spawner::update(double elapsed) {
	if (!Reg::paused) {
		this->elapsed += elapsed;
		if (this->elapsed >= trigger) {
			spawn();
		}
	}
}

void Spawner::spawn() {
	if (roll() <= 0.01 + max(0, 0.1 * (Reg::difficulty - 20.0) / 60.0)) {
		double height;
		double vel;
		for (int i = 0; i < 3; i++) {
			EnemyBasic* ent = new EnemyBasic();
			setupBasicEnemy(ent);
			ent->y -= Reg::m->margin * i;
			height = ent->height + Reg::m->margin * i;
			ent->velY = Reg::m->fourthH / 3.0;
			vel = ent->velY;
		}
		setTrigger((double)(height + Reg::m->margin / 2.0) / vel);
	}
	else {
		EnemyBasic* ent = new EnemyBasic();
		setupBasicEnemy(ent);
		ent->velY = Reg::m->fourthH / 3.0;
		setTrigger((double)(ent->height + Reg::m->margin / 2.0) / ent->velY);
	}
}

void Spawner::setTrigger(double min) {
	elapsed = 0;

	double addTime = max(0.0, 10.0 * (1.0 - Reg::difficulty / 30.0));
	std::uniform_real_distribution<double> uni(min, min + addTime);
	trigger = uni(Reg::rng);
}

Spawner::~Spawner() {

}
