#include "stdafx.h"
#include "Spawner.h"
#include "Window.h"
#include "Reg.h"
#include <random>
#include "EnemyBasic.h"

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
	EnemyBasic* ent = new EnemyBasic();
	ent->loadImage(Reg::getRandomImage());

	ent->setSize(Reg::m->thirdW - Reg::m->margin * 2, Reg::m->thirdH - Reg::m->margin * 2);
	ent->alignCenter(x);
	ent->alignBot(y);
	ent->velY = Reg::m->fourthH / 3.0;

	setTrigger((double)(ent->height + Reg::m->margin / 2.0) / ent->velY);
}

void Spawner::setTrigger(double min) {
	elapsed = 0;

	double addTime = max(0.0, 10.0 * (1.0 - Reg::difficulty / 30.0));
	std::uniform_real_distribution<double> uni(min, min + addTime);
	trigger = uni(Reg::rng);
}

Spawner::~Spawner() {

}
