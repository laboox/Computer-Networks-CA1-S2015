#include "Time.h"

Time::Time(string s)
{
	stringstream ss(s);
	int houre,minute;
	char dot;
	if(! (ss>>houre>>dot>>minute && dot==':' && h>=0 && h<=23 && m>=0 && m<=60))
		throw new Exeption("Invalid Time");
}

bool Time::valid(Time t)
{
	return houre>=0 && houre<=23 && minute>=0 && minute<=60
}

bool Time::before(Time t);
{
	return ((houre<t.houre) || (houre==t.houre && minute<t.minute);
}