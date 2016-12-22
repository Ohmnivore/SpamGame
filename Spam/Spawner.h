#pragma once
#include "Entity.h"
#include "Window.h"

class Spawner : public Entity {
public:
	Spawner(int x, int y);
	~Spawner();

	void update(double elapsed);
	void spawn();

	bool canSlide;

protected:
	void setTrigger(double min);
	void setupBasicEnemy(Window* ent);

	int x;
	int y;
	double elapsed;
	double trigger;
};
