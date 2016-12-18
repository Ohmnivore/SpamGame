#include "stdafx.h"
#include "Reg.h"

namespace Reg {

	Metrics* m;
	HINSTANCE inst;
	std::list<Entity*> ents;
	std::vector<Entity*> toAdd;
	std::vector<Entity*> toRemove;
	std::vector<std::wstring*> images;
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
		score = 0;
		rng = std::mt19937(rd());
		paused = false;

		shakeX = shakeY = shakeTimer = shakeIntensity = 0;
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
			ents.remove(toRemove.back());
			toRemove.pop_back();
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
		WIN32_FIND_DATA ffd;
		HANDLE hFind;

		hFind = FindFirstFile(L"images/*.bmp", &ffd);
		if (hFind == INVALID_HANDLE_VALUE)
			throw "Couldn't load images directory";
		else {
			do {
				std::wstring* path = new std::wstring(L"images/");
				*path += ffd.cFileName;
				images.push_back(path);
			} while (FindNextFile(hFind, &ffd) != 0);
		}
	}

	std::wstring getRandomImage() {
		std::uniform_int_distribution<int> uni(0, images.size() - 1);
		return *images.at(uni(Reg::rng));
	}

	int getHighscore() {
		DWORD buffer;
		unsigned long type = REG_DWORD;
		unsigned long size = 1024;

		HKEY hKey;
		if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\SpamGame\\Highscore", 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
			return 0;

		if (RegQueryValueEx(hKey, L"Highscore", NULL, &type, (LPBYTE)&buffer, &size) != ERROR_SUCCESS) {
			RegCloseKey(hKey);
			return 0;
		}

		RegCloseKey(hKey);
		return buffer;
	}

	void setHighscore(int score) {
		DWORD buffer = (DWORD)score;

		HKEY hKey;
		if (RegCreateKey(HKEY_CURRENT_USER, L"Software\\SpamGame\\Highscore", &hKey) != ERROR_SUCCESS)
			return;

		if (RegSetValueEx(hKey, L"Highscore", NULL, REG_DWORD, (LPBYTE)&buffer, sizeof(buffer)) != ERROR_SUCCESS) {
			RegCloseKey(hKey);
			return;
		}

		RegCloseKey(hKey);
	}
};