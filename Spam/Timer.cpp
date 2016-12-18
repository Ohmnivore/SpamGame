#include "stdafx.h"
#include "Timer.h"
#include "Reg.h"

Timer::Timer() {
	finished = true;
	time = elapsed = 0;
	Reg::add(this);
}

void Timer::start(double time) {
	finished = false;
	elapsed = 0;
	this->time = time;
}

void Timer::update(double elapsed) {
	if (!finished) {
		this->elapsed += elapsed;
		if (this->elapsed >= time) {
			finished = true;
			trigger();
		}
	}
}

void Timer::trigger() {

}

Timer::~Timer() {

}
