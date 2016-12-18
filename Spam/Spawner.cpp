#include "stdafx.h"
#include "Spawner.h"
#include "Window.h"
#include "Reg.h"
#include <random>
#include "EnemyBasic.h"

Spawner::Spawner(int x, int y) {
	this->x = x;
	this->y = y;
	setTrigger();
}

void Spawner::update(double elapsed) {
	if (!Reg::paused) {
		this->elapsed += elapsed;
		if (this->elapsed >= trigger) {
			spawn();
			setTrigger();
		}
	}
}

void Spawner::spawn() {
	EnemyBasic* ent = new EnemyBasic();
	ent->loadImage(Reg::getRandomImage());

	ent->setSize(Reg::m->thirdW - Reg::m->margin * 2, Reg::m->thirdH - Reg::m->margin * 2);
	ent->alignCenter(x);
	ent->alignBot(y);

	ent->velY = 48;
}

void Spawner::setTrigger() {
	elapsed = 0;

	std::uniform_int_distribution<int> uni(5, 8);
	trigger = uni(Reg::rng);
}

Spawner::~Spawner() {

}
