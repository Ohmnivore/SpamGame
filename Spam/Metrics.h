#pragma once
class Metrics {
public:
	Metrics(HWND hWnd);
	~Metrics();

	int x(int x);
	int y(int y);

	int halfW;
	int thirdW;
	int fourthW;
	int sixthW;
	int eightW;

	int halfH;
	int thirdH;
	int fourthH;
	int sixthH;
	int eightH;

private:
	int left;
	int right;
	int top;
	int bot;
	int width;
	int height;
};
