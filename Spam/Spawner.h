#pragma once
#include "Entity.h"

class Spawner : public Entity {
public:
	Spawner(int x, int y);
	~Spawner();

	void update(double elapsed);
	void spawn();

private:
	void setTrigger(double min);

	int x;
	int y;
	double elapsed;
	double trigger;
};
