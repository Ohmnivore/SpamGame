#pragma once
#include "Metrics.h"

class Entity {
public:
	Entity(HINSTANCE hInstance, Metrics* metrics);
	~Entity();

	void setSize(int width, int height);

	HINSTANCE hInst;
	HWND hWnd;
	Metrics* metrics;

	int width;
	int height;
	int x;
	int y;

private:
	static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	WCHAR* wTitle;
	WCHAR* wClass;
};
