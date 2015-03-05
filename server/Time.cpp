#include "Time.h"

Time::Time(string s)
{
	stringstream ss(s);
	char dot;
	if(! (ss>>houre>>dot>>minute && dot==':' && houre>=0 && houre<=23 && minute>=0 && minute<=60))
		throw new Exeption("Invalid Time");
}

bool Time::valid()
{
	return houre>=0 && houre<=23 && minute>=0 && minute<=60;
}

bool Time::before(Time t)
{
	return ((houre<t.houre) || (houre==t.houre && minute<t.minute));
}
