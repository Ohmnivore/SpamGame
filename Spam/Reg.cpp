#include "stdafx.h"
#include "Reg.h"

namespace Reg {

	Metrics* m;
	HINSTANCE inst;
	std::list<Entity*> ents;
	std::vector<std::wstring*> images;
	std::mt19937 rng;
	int score;
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

		shakeX = shakeY = shakeTimer = shakeIntensity = 0;
	}

	void update(double elapsed) {
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
		shakeIntensity += intensity;
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
};