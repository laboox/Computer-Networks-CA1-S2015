#include "Header.h"

class Time
{
private:
	int houre;
	int minute;
public:
	Time(int h, int m) : houre(h), minute(m) {}; 
	Time(string t);
	bool valid(Time t);
	bool before(Time t);
};