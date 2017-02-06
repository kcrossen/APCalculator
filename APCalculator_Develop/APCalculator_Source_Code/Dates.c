#include <windef.h>
#include "dates-krc.h"

static void Jul_GregYMDofJDN(RL_INT4 jd, RL_INT4 *year, RL_INT4 *month, RL_INT4 *day);
static void Jul_JulYMDofJDN(RL_INT4 jd, RL_INT4 *year, RL_INT4 *month, RL_INT4 *day);
static void Jul_FixYM(RL_INT4 *year, RL_INT4 *month);
static RL_INT4 Jul_JDNofGregYMD(RL_INT4 year, RL_INT4 month, RL_INT4 day);
static RL_INT4 Jul_JDNofJulYMD(RL_INT4 year, RL_INT4 month, RL_INT4 day);

static RL_INT4 gregorian_dutc  = -152384;   /* Default is October 15, 1582 */
static RL_INT4 gregorian_year  = 1582;
static RL_INT4 gregorian_month = 10;
static RL_INT4 gregorian_day   = 15;

RL_INT4	Jul_DUTCofJDN(RL_INT4 jd)
{
	return jd - JD_OF_J2000;
}

RL_INT4	Jul_JDNofDUTC(RL_INT4 dutc)
{
	return dutc + JD_OF_J2000;
}

void	Jul_YMDofDUTC(RL_INT4 dutc, RL_INT4 *year, RL_INT4 *month, RL_INT4 *day)
{
	if (dutc >= gregorian_dutc)
		Jul_GregYMDofJDN(dutc + JD_OF_J2000, year, month, day);
	else
		Jul_JulYMDofJDN (dutc + JD_OF_J2000, year, month, day);
}

static void Jul_GregYMDofJDN(RL_INT4 jd, RL_INT4 *year, RL_INT4 *month, RL_INT4 *day)
{
RL_INT4	l, n, i, j, d, m, y;

	l = jd + 68569;
	n = (4*l) / 146097;
	l = l - (146097*n + 3)/4;
	i = (4000*(l+1))/1461001;
	l = l - (1461*i)/4 + 31;
	j = (80*l)/2447;
	d = l - (2447*j)/80;
	l = j/11;
	m = j + 2 - 12*l;
	y = 100*(n-49) + i + l;

	*year  = y;
	*month = m;
	*day   = d;
}

static void Jul_JulYMDofJDN(RL_INT4 jd, RL_INT4 *year, RL_INT4 *month, RL_INT4 *day)
{
RL_INT4	j, k, l, n, d, i, m, y;

	j = jd + 1402;
	k = (j-1)/1461;
	l = j - 1461*k;
	n = (l-1)/365 - l/1461;
	i = l - 365*n + 30;
	j = (80*i)/2447;
	d = i - (2447*j)/80;
	i = j/11;
	m = j + 2 - 12*i;
	y = 4*k + n + i - 4716;

	*year  = y;
	*month = m;
	*day   = d;
}

RL_INT4	Jul_DUTCofYMD(RL_INT4 year, RL_INT4 month, RL_INT4 day)
{
RL_BOOL	isgreg;

/* Correct year & month ranges */
	Jul_FixYM(&year, &month);

/* Determine which calendar to use */
	if	  (year > gregorian_year)   isgreg = TRUE;
	else if   (year < gregorian_year)   isgreg = FALSE;
	else {
	  if      (month > gregorian_month) isgreg = TRUE;
	  else if (month < gregorian_month) isgreg = FALSE;
	  else                              isgreg = (day >= gregorian_day);
	}

/* Calculate and return date */
	if (isgreg) return Jul_JDNofGregYMD(year, month, day) - JD_OF_J2000;
	else        return Jul_JDNofJulYMD (year, month, day) - JD_OF_J2000;
}

static void Jul_FixYM(RL_INT4 *year, RL_INT4 *month)
{
RL_INT4	y, m, dyear;

	y = *year;
	m = *month;

/* Shift month into range 1-12 */
	dyear = (m-1) / 12;	
	m -= 12 * dyear;
	y += dyear;

	if (m < 1) {
		m += 12;
		y -= 1;
	}

	*year  = y;
	*month = m;
}

static RL_INT4 Jul_JDNofGregYMD(RL_INT4 year, RL_INT4 month, RL_INT4 day)
{
RL_INT4	temp;

/*	temp = (month - 14)/12; */
	temp = (month <= 2 ? -1:0);

	return   (1461*(year + 4800 + temp))/4
	       + (367*(month - 2 - 12*temp))/12
	       - (3*((year + 4900 + temp)/100))/4 + day - 32075;
}

static RL_INT4 Jul_JDNofJulYMD(RL_INT4 year, RL_INT4 month, RL_INT4 day)
{
	return   367*year
	       - (7*(year + 5001 + (month-9)/7))/4
	       + (275*month)/9
	       + day + 1729777;
}

