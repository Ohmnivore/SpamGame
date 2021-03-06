#pragma once
#include "Entity.h"

class Timer : public Entity {
public:
	Timer();
	virtual ~Timer();

	virtual void start(double time);
	virtual void update(double elapsed);
	virtual void trigger();
	
	double time;
	double elapsed;
	bool finished;
};
