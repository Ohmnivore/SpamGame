#pragma once
class Metrics {
public:
	Metrics(HWND hWnd);
	~Metrics();
	double half;
	double third;
	double fourth;
	double sixth;
	double eight;

private:
	int left;
	int right;
	int top;
	int bot;
	int width;
	int height;
};

