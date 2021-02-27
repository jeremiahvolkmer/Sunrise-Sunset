#include <stdio.h>
#include <time.h>
#include <math.h>
#include "globs.h"

/*
** Function prototypes
*/
struct    tm currentTime (); 
int       isLeap ();
double    fractionalYear (); 
double    eqTime ();
double    decl (); 
double    ha (); 
double    sunrise (); 
double    sNoon (); 

GLOBS Globs;

int main ()
{
	Globs.time = currentTime ();
        Globs.lat  = 47;
	Globs.lng  = 122;

        double n = sNoon (); 	
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

/*
** From fractionalYear () estimating the equation of time in minutes.
*/
double eqTime ()
{
	double y = fractionalYear ();
	double eq_time = 229.18 * ((0.000075 +(0.001868 * cos(y))) - (0.032077 * sin(y)) - (0.014615 * cos(2 * y)) - (0.040849 * sin(2 * y))); 
	return eq_time; 
}

/*
** From fractionalYear () estimatin the equation of the solar declination angle in radiains.
*/
double decl ()
{
	double y = fractionalYear ();
	double decl_ang = 0.006918 - (0.399912 * cos(y)) + (0.070257 * sin(y)) - (0.006758 *cos(2 * y)) + (0.000970 * sin(2 * y)) - (0.002697 * cos(3 * y)) + (0.00148 * sin(3 * y));
	return decl_ang; 
}

/*
** Zenith is set 90.833degs the approximate correction for atmospheric refraction at 
** rise/set, and the size of the solar disk.
*/
double ha ()
{
	double dec_ang = decl (); 
	double h_a = acos(( cos(90.833) / (cos(Globs.lat) * cos(dec_ang))) - (tan(Globs.lat) * tan(dec_ang)));
	return h_a; 
}

double sunrise ()
{
	double h_a = ha ();
        double eq_time = eqTime ();	
	double rise = 720 - (4 * (Globs.lng + h_a)) - eq_time; 
	return rise; 
}

double sNoon ()
{
	double eq_time = eqTime ();
	double s_noon = 720 - (4 * Globs.lng) - eq_time;
	return s_noon; 
}
