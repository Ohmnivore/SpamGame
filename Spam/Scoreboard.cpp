#include "stdafx.h"
#include "Scoreboard.h"
#include "Util.h"


Scoreboard::Scoreboard(HINSTANCE hInstance, Metrics* metrics) : Entity::Entity(hInstance, metrics) {

}

void Scoreboard::update(double elapsed) {
	Entity::update(elapsed);
}

void Scoreboard::onExit() {
	toggleDesktopIconsVisible();
	PostQuitMessage(0);
}

Scoreboard::~Scoreboard() {
}
