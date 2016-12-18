#pragma once
#include "Entity.h"
#include "Metrics.h"

class Window : public Entity {
public:
	Window();
	virtual ~Window();

	virtual void loadImage(int id);
	virtual void update(double elapsed);
	virtual void onExit();
	virtual void onPaint(HDC hdc);
	virtual void onCmd();

	virtual void setSize(int width, int height);
	virtual void alignLeft(int x);
	virtual void alignCenter(int x);
	virtual void alignRight(int x);
	virtual void alignTop(int y);
	virtual void alignMiddle(int y);
	virtual void alignBot(int y);

	HINSTANCE hInst;
	HWND hWnd;
	HBITMAP hImg;
	Metrics* metrics;

	int width;
	int height;
	double x;
	double y;
	double velX;
	double velY;
	bool closed;

protected:
	static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	WCHAR* wTitle;
	WCHAR* wClass;
	int score;
};
