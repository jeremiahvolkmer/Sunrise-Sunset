#include <stdio.h>
#include <time.h>

/*
** Function prototypes
*/
struct tm currentTime (); 
int    isLeap ();
int    fractionalYear(); 

int main ()
{
	struct tm time; 
	time = currentTime ();
        int test = isLeap(time);	
	printf ("%02d\n", test);
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
** Returns true if current year is a leap year.
*/
int isLeap (struct tm time)
{
	int year = time.tm_year;
	return ((year % 4 == 0 && year % 100 != 0) || (year % 100 == 0 && year % 400 == 0));
}

int fractionalYear ()
{
	int y; 

}
