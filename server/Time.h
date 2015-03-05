#pragma once

#include "Header.h"

class Time
{
private:
	int houre;
	int minute;
public:
	Time(int h, int m) : houre(h), minute(m) {}; 
	Time(string t);
	bool valid();
	bool before(Time t);
};
