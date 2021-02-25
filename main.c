#include <stdio.h>
#include <time.h>
#include <math.h>
#include "globs.h"

/*
** Function prototypes
*/
struct    tm currentTime (); 
int       isLeap ();
double    fractionalYear(); 

GLOBS Globs;

int main ()
{
	Globs.time = currentTime (); 
	double n = fractionalYear (); 
	printf ("%lf\n", n);
	return 0;
}

/*
** Returns struct declared in time.h with the following members:
** tm.tm_mday, tm.tm_mon, tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec
*/
struct tm currentTime ()
{
	time_t rawtime = time (NULL);
	struct tm time = *localtime (&rawtime); 
	return time; 
}

/*
** Returns 1 if current year is a leap year, else 0 is returned. 
*/
int isLeap ()
{
	int year = Globs.time.tm_year;

	return ((year % 4 == 0 && year % 100 != 0) || (year % 100 == 0 && year % 400 == 0));
}

/*
** Fractional year is calculated, in radians and returned.
*/
double fractionalYear ()
{
	int leap = isLeap();
	double y = (((2 * M_PI) / (365 + leap)) * ((Globs.time.tm_yday - 1) + ((Globs.time.tm_hour - 12) / 24)));
        return y;	
}

double 


