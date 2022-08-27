#pragma once
#include <iostream>
#include <string>
#include <easyx.h>

using namespace std;

class Button
{
private:

	int left;
	int top;
	int right;
	int bottom;

	LPCTSTR str;

public:
	Button(void);

	Button(int _left, int _top, int _right, int _bottom, LPCTSTR _str);

	bool isClick(ExMessage* msg);

	void draw(void);
};