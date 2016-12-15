#pragma once
#include "Metrics.h"

class Entity {
public:
	Entity(HINSTANCE hInstance, Metrics* metrics);
	~Entity();

	virtual void update(double elapsed);
	virtual void onExit();

	void setSize(int width, int height);
	void alignLeft(int x);
	void alignCenter(int x);
	void alignRight(int x);
	void alignTop(int y);
	void alignMiddle(int y);
	void alignBot(int y);

	HINSTANCE hInst;
	HWND hWnd;
	Metrics* metrics;

	int width;
	int height;
	double x;
	double y;
	double velX;
	double velY;

private:
	static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	WCHAR* wTitle;
	WCHAR* wClass;
};
