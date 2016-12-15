#include "stdafx.h"
#include "Spawner.h"
#include "Entity.h"
#include "Reg.h"
#include <random>

Spawner::Spawner(int x, int y) {
	this->x = x;
	this->y = y;
	setTrigger();
}

void Spawner::update(double elapsed) {
	this->elapsed += elapsed;
	if (this->elapsed >= trigger) {
		spawn();
		setTrigger();
	}
}

void Spawner::spawn() {
	Entity* ent = new Entity(Reg::inst, Reg::m);
	Reg::ents.push_back(ent);
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
