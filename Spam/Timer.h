#pragma once
#include "Entity.h"

class Timer : public Entity {
public:
	Timer();
	~Timer();
	void start(double time);
	virtual void update(double elapsed);
	virtual void trigger();
	
	double time;
	double elapsed;
	bool finished;
};

