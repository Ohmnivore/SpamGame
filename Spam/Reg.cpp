#include "stdafx.h"
#include "Reg.h"

namespace Reg {

	Metrics* m;
	HINSTANCE inst;
	std::vector<Entity*> ents;
	std::vector<std::wstring*> images;
	std::mt19937 rng;
	int score;

	void initImages();

	void init(HINSTANCE hInst) {
		Entity ent = Entity(hInst, nullptr);
		ent.setSize(0, 0);
		m = new Metrics(ent.hWnd);
		inst = hInst;
		initImages();

		std::random_device rd;
		score = 0;
		rng = std::mt19937(rd());
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