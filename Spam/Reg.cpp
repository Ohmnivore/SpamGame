#include "stdafx.h"
#include "Reg.h"
#include "Scoreboard.h"
#include "Spawner.h"
#include "resource.h"

#define REG_SUBKEY L"Software\\SpamGame\\Highscore"
#define REG_VALUE L"Highscore"
#define PROG_CLASS L"Progman"
#define PROG_TITLE L"Program Manager"
#define PROG_CTRL 0x7402

namespace Reg {

	Metrics* m;
	HINSTANCE inst;
	std::list<Entity*> ents;
	std::vector<Entity*> toAdd;
	std::vector<Entity*> toRemove;
	std::vector<int> images;
	std::mt19937 rng;
	int score;
	bool paused;
	void initImages();

	double shakeX;
	double shakeY;
	double shakeTimer;
	double shakeIntensity;

	void init(HINSTANCE hInst) {
		inst = hInst;
		Window ent = Window();
		ent.setSize(0, 0);
		m = new Metrics(ent.hWnd);
		initImages();

		std::random_device rd;
		rng = std::mt19937(rd());
		
		toAdd.clear();
		ents.clear();
		reset();
	}

	void reset() {
		while (!ents.empty()) {
			Entity* ent = ents.back();
			ents.pop_back();
			delete ent;
		}
		while (!toAdd.empty()) {
			Entity* ent = toAdd.back();
			toAdd.pop_back();
			delete ent;
		}

		score = 0;
		paused = false;
		shakeX = shakeY = shakeTimer = shakeIntensity = 0;

		Scoreboard* scoreBoard = new Scoreboard();
		Spawner* s1 = new Spawner(m->thirdW * 0.5 + m->margin / 2, 0);
		s1->spawn();
		Spawner* s2 = new Spawner(m->thirdW * 1.5, 0);
		s2->spawn();
		Spawner* s3 = new Spawner(m->thirdW * 2.5 - m->margin / 2, 0);
		s3->spawn();
		ents.push_back(s1);
		ents.push_back(s2);
		ents.push_back(s3);
	}

	void add(Entity* ent) {
		toAdd.push_back(ent);
	}

	void remove(Entity* ent) {
		toRemove.push_back(ent);
	}

	void update(double elapsed) {
		while (!toAdd.empty()) {
			ents.push_back(toAdd.back());
			toAdd.pop_back();
		}

		while (!toRemove.empty()) {
			Entity* rem = toRemove.back();
			ents.remove(rem);
			toRemove.pop_back();
			delete rem;
		}

		shakeTimer -= elapsed;
		if (shakeTimer <= 0) {
			shakeX = shakeY = shakeTimer = shakeIntensity = 0;
		}
		else {
			std::uniform_real_distribution<double> uni(-shakeIntensity * (double)m->width, 0);
			shakeX = uni(Reg::rng);
			shakeY = uni(Reg::rng);
		}
	}

	void shake(double length, double intensity) {
		if (shakeTimer < length)
			shakeTimer = length;
		if (shakeIntensity < intensity)
			shakeIntensity = intensity;
	}

	void initImages() {
		images.push_back(IDB_BITMAP1);
		images.push_back(IDB_BITMAP2);
		images.push_back(IDB_BITMAP3);
		images.push_back(IDB_BITMAP4);
		images.push_back(IDB_BITMAP5);
		images.push_back(IDB_BITMAP6);
		images.push_back(IDB_BITMAP7);
		images.push_back(IDB_BITMAP8);
		images.push_back(IDB_BITMAP9);
		images.push_back(IDB_BITMAP10);
		images.push_back(IDB_BITMAP11);
	}

	int getRandomImage() {
		std::uniform_int_distribution<int> uni(0, images.size() - 1);
		return images.at(uni(Reg::rng));
	}

	void toggleDesktopIconsVisible() {
		SendMessage(GetWindow(FindWindow(PROG_CLASS, PROG_TITLE), GW_CHILD), WM_COMMAND, PROG_CTRL, 0);
	}

	int getHighscore() {
		DWORD buffer;
		unsigned long type = REG_DWORD;
		unsigned long size = 1024;

		HKEY hKey;
		if (RegOpenKeyEx(HKEY_CURRENT_USER, REG_SUBKEY, 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
			return 0;

		if (RegQueryValueEx(hKey, REG_VALUE, NULL, &type, (LPBYTE)&buffer, &size) != ERROR_SUCCESS) {
			RegCloseKey(hKey);
			return 0;
		}

		RegCloseKey(hKey);
		return buffer;
	}

	void setHighscore(int score) {
		DWORD buffer = (DWORD)score;

		HKEY hKey;
		if (RegCreateKey(HKEY_CURRENT_USER, REG_SUBKEY, &hKey) != ERROR_SUCCESS)
			return;

		if (RegSetValueEx(hKey, REG_VALUE, NULL, REG_DWORD, (LPBYTE)&buffer, sizeof(buffer)) != ERROR_SUCCESS) {
			RegCloseKey(hKey);
			return;
		}

		RegCloseKey(hKey);
	}
};