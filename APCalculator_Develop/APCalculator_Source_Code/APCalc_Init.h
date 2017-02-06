#ifndef APCALC_INIT_H
#define APCALC_INIT_H

#define APCalc_Precis (char*) \
"config(\"display\", @);config(\"epsilon\", 1e-@);" \
"protect(pi, 0);pi=pi();protect(pi, 7);" \
"protect(e, 0);e=exp(1);protect(e, 7);"

#define APCalc_Config (char*) \
"config(\"display\", 40);config(\"epsilon\", 1e-40);" \
"pi=pi();protect(pi, 7);e=exp(1);protect(e, 7);" \
"rpnstack=list();lastrpnstack=list();" \
"rpnmemory = list(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);" \
"rad2deg=180/pi;deg2rad=pi/180;" \
"fromangle=deg2rad;toangle=rad2deg;"

#define APCalc_SolverFunction (char*) \
"define solver(solve_for, low, high, max_iterations, epsilon) \n" \
"{ \n" \
"	local f_low, f_high, f_mid, mid, places; \n" \
"	local initial_iterations, toggle; \n" \
"	local slope, min, max; \n" \
" \n" \
"	if (isnull(epsilon)) epsilon = epsilon(); \n" \
" \n" \
"	if (epsilon <= 0) quit \"Non-positive epsilon value\"; \n" \
" \n" \
"	places = highbit(1 + int(1/epsilon)) + 1; \n" \
" \n" \
"	if ((low == 0) && (high == 0) && (*solve_for != 0)) { \n" \
"		/* In this case the user is giving the starting estimate */ \n" \
"		/* effectively as the neighborhood of a given value */ \n" \
"		/* such as could be derived by inspection from an */ \n" \
"		/* onscreen graph, for example */ \n" \
"		low = *solve_for; \n" \
"		high = *solve_for; \n" \
"	} \n" \
" \n" \
"	if (low > high) { \n" \
"		/* belt and suspenders here */ \n" \
"		/* user may not have rtfm, */ \n" \
"		/* but we can still program */ \n" \
"		/* as if people mattered */ \n" \
"		mid = high; \n" \
"		high = low; \n" \
"		low = mid; \n" \
"	} \n" \
" \n" \
"	/* user may have no idea what */ \n" \
"	/* the bounds ought to be, */ \n" \
"	/* so we'll try to find them */ \n" \
"	if (low == high) { \n" \
"		if (low == 0) { \n" \
"			high = 1; \n" \
"		} \n" \
"		else { \n" \
"			high = 1.000001 * low; \n" \
"			low = 0.999999 * low; \n" \
"			if (low > high) { \n" \
"			    mid = high; \n" \
"			    high = low; \n" \
"			    low = mid; \n" \
"			} \n" \
"		} \n" \
"	} \n" \
" \n" \
"	initial_iterations = max_iterations / 4; \n" \
"	toggle = 0; \n" \
" \n" \
"	while (initial_iterations > 0) { \n" \
"		*solve_for = low; \n" \
"		f_low = solver_function(); \n" \
"		*solve_for = high; \n" \
"		f_high = solver_function(); \n" \
"		if ((iserror(f_low) || !isreal(f_low)) && (iserror(f_high) || !isreal(f_high))) { \n" \
"			/* trapping two types of problems: divide by zero, etc. and functions */ \n" \
"			/* that contain items like sqrt(x) (we only want real roots) */ \n" \
"			/* we've got nothing to work with here, give up */ \n" \
"			return error(0); \n" \
"		} \n" \
" \n" \
"		if (!(iserror(f_low) || !isreal(f_low))) { \n" \
"			/* could get lucky */ \n" \
"			if (abs(f_low) < epsilon) return low; \n" \
"		} \n" \
" \n" \
"		if (!(iserror(f_high) || !isreal(f_high))) { \n" \
"			/* could get lucky */ \n" \
"			if (abs(f_high) < epsilon) return high; \n" \
"		} \n" \
" \n" \
"		/* this next is often implemented as a switch statement */ \n" \
"		/* steping through the various stages of attaining brackets */ \n" \
"		/* on the root. a switch makes it much harder to recover from */ \n" \
"		/* unexpected loss of ground in the process of finding */ \n" \
"		/* a proper bracket. the steps are roughly 1) get two different */ \n" \
"		/* bounds, 2) make sure they are both defined for your function, */ \n" \
"		/* 3) make sure that their values are different, and finally */ \n" \
"		/* 4) ensure that their values have opposite sign (i.e. they bracket */ \n" \
"		/* the root at zero). this loop should not cycle that many times, so */ \n" \
"		/* again favor robustness over elegance, and grind humorously through */ \n" \
"		/* the problem over and over again on each cycle. */ \n" \
"		/* what's time to a computer? */ \n" \
"		if (iserror(f_low) || (!isreal(f_low)) || \n" \
"			iserror(f_high) || (!isreal(f_high))) {  \n" \
"			/* looking for two defined points on the function */ \n" \
"			/* bisect, keeping the valid value, try again */ \n" \
"			if (iserror(f_low) || (!isreal(f_low))) { \n" \
"				low = (low + high) / 2; \n" \
"			} \n" \
"			else \n" \
"			{ \n" \
"				high = (low + high) / 2; \n" \
"			} \n" \
"			if (low == high) { \n" \
"				/* out of options, give up */ \n" \
"				return error(0); \n" \
"			} \n" \
"		} \n" \
"		else if (f_low == f_high) { \n" \
"			/* looking for two distinct, valid values on the function */ \n" \
"			/* perhaps we're too restricted */ \n" \
"			if (toggle == 0) { \n" \
"				low = low - (10 * (high - low)); \n" \
"			} \n" \
"			else \n" \
"			{ \n" \
"				high = high + (10 * (high - low)); \n" \
"			} \n" \
"			toggle = (toggle + 1) % 2; \n" \
"		} \n" \
"		else if (!(((f_low < 0) && (f_high > 0)) || ((f_low > 0) && (f_high < 0)))) { \n" \
"			/* looking for two distinct, valid values of opposite sign on the function */ \n" \
" \n" \
"			/* not handling infinite slope or zero slope yet */ \n" \
"			/* if ((high - low) <= epsilon) {} */ \n" \
"			/* if ((f_high - f_low) / (high - low) <= epsilon) {} */ \n" \
" \n" \
"			/* the secant method (approximately) is being used here for */ \n" \
"			/* it's property of expanding the bounds in the correct direction */ \n" \
"			/* and in roughly the proper amount */ \n" \
"			slope = (f_high - f_low) / (high - low); \n" \
"			mid = low - (f_low / slope); \n" \
"			if ((f_low > 0) && (f_high > 0)) { \n" \
"				if (slope > 0) { \n" \
"					/* adjust low, but carefully */ \n" \
"					min = low - (10 * (high - low)); \n" \
"					if (mid < min) mid = min; \n" \
"					low = mid; \n" \
"				} \n" \
"				else \n" \
"				{ \n" \
"					/* adjust high, but carefully */ \n" \
"					max = high + (10 * (high - low)); \n" \
"					if (mid > max) mid = max; \n" \
"					high = mid; \n" \
"				} \n" \
"			} \n" \
"			else \n" \
"			{ \n" \
"				if (slope < 0) { \n" \
"					/* adjust low, but carefully */ \n" \
"					min = low - (10 * (high - low)); \n" \
"					if (mid < min) mid = min; \n" \
"					low = mid; \n" \
"				} \n" \
"				else \n" \
"				{ \n" \
"					/* adjust high, but carefully */ \n" \
"					max = high + (10 * (high - low)); \n" \
"					if (mid > max) mid = max; \n" \
"					high = mid; \n" \
"				} \n" \
"			} \n" \
"		}  \n" \
"		else { \n" \
"			max_iterations--; \n" \
"			break; \n" \
"		} \n" \
" \n" \
"		if ((low < -1e100) || (low > +1e100) || (high < -1e100) || (high > +1e100)) { \n" \
"			/* this is not likely to have a finite solution, give up */ \n" \
"			return error(0); \n" \
"		} \n" \
" \n" \
"		initial_iterations--; \n" \
"		max_iterations--; \n" \
"	} \n" \
" \n" \
"	if (sgn(f_low) == sgn(f_high)) quit \"Non-opposite signs\"; \n" \
" \n" \
"	/* got the root bracketed now, just grind on in on it */ \n" \
"	/* using bisection, plodding and inelegant, certainly, */ \n" \
"	/* but also the most reliable and robust method */ \n" \
"	while (max_iterations > 0) { \n" \
"		mid = bround(high - f_high * (high - low) / (f_high - f_low), places); \n" \
"		if ((mid == low) || (mid == high)) \n" \
"			places++; \n" \
"		*solve_for = mid; \n" \
"		f_mid = solver_function(); \n" \
"		if (abs(f_mid) < epsilon) return mid; \n" \
"		if (sgn(f_mid) == sgn(f_low)) { \n" \
"			low = mid; \n" \
"			f_low = f_mid; \n" \
"		}  \n" \
"		else { \n" \
"			high = mid; \n" \
"			f_high = f_mid; \n" \
"		} \n" \
"		max_iterations--; \n" \
"	} \n" \
"} \n"

#define APCalc_UtilityFunctions (char*) \
"define PrintRPN(s) " \
"{local mag, i, r, b, b2; " \
" b = base(); b2 = base2(); " \
" if (isnum(s) == 1) " \
"  {if ((isreal(s) == 0) && (re(s) != 0)) { " \
"    base(10); base2(0); " \
"    r = abs(re(s)); i = abs(im(s) / 1i); " \
"    if ((r == 0) || ((r > 1e-1) && (r < 1e1))) r = 1; else r = abs(trunc(log(r))); " \
"    if ((i == 0) || ((i > 1e-1) && (i < 1e1))) i = 1; else i = abs(trunc(log(i))); " \
"    mag = 14 - (digits(r) + digits(i)) // 2; " \
"    if ((abs(re(s)) >= 1e14) || (abs(im(s)) >= 1e14)) {printf(\"%e\", round(s, mag, 56)); print();} " \
"    else if ((abs(re(s)) <= 1e-3) || (abs(im(s)) <= 1e-3)) {printf(\"%e\", round(s, mag, 56)); print();} " \
"    else print(round(s, 15, 56)); " \
"   } else { " \
"    if ((isint(s) == 0) || (re(s) == 0)) { base(10); base2(0); } " \
"    r = abs(s); " \
"    if ((r == 0) || ((r > 1e-1) && (r < 1e1))) r = 1; else r = abs(trunc(log(r))); " \
"    mag = 32 - digits(r); " \
"    if (abs(s) >= 1e30) {printf(\"%e\", round(s, mag, 56)); print();} " \
"    else if (abs(s) <= 1e-3) {printf(\"%e\", round(s, mag, 56)); print();} " \
"    else print(round(s, 32, 56)); " \
"   }} " \
" else print(s); " \
" base(b); base2(b2);}" \
"\n" \
"define nrand() " \
"{local x1,x2,w;" \
" do {x1=(2*(rand()/2^64))-1;x2=(2*(rand()/2^64))-1;w=x1*x1+x2*x2;} while (w>=1);" \
" w=sqrt((-2*ln(w))/w);" \
" return x1*w;}"

// Approximate summary of the voluminous comments that accompanied
// the following code. For much of the code of interest, the comments
// were double or triple the size of the code. On the other hand,
// the code compiled and worked flawlessly as published.
// *$ Author_and_institution:
// *	Mark R. Showalter
// *	PDS Rings Node
// *	NASA/Ames Research Center
// *$ Version_and_date:
// *	1.0: December 1995
// * Mark R. Showalter, PDS Rings Node, December 1995
// * Revised by MRS 7/97 with minor updates.
// * Revised by MRS 6/98 to conform to RingLib naming conventions.

#define APCalc_DateFunctions (char*) \
    "JD_OF_J2000	    = 2451545 /* Julian Date of noon, J2000 */; \n" \
    " \n" \
    "gregorian_dutc  = -152384 /* Default is October 15, 1582 */; \n" \
    "gregorian_year  = 1582; \n" \
    "gregorian_month = 10; \n" \
    "gregorian_day   = 15; \n" \
    " \n" \
    "define Jul_DUTCofJDN(jd) \n" \
    "{ \n" \
    "	return jd - JD_OF_J2000; \n" \
    "} \n" \
    " \n" \
    "define Jul_JDNofDUTC(dutc) \n" \
    "{ \n" \
    "	return dutc + JD_OF_J2000; \n" \
    "} \n" \
    " \n" \
    "define Jul_YMDofDUTC(dutc, year, month, day) \n" \
    "{ /* ByRef year, month, day */ \n" \
    "	if (dutc >= gregorian_dutc) \n" \
    "		Jul_GregYMDofJDN((dutc + JD_OF_J2000), &year, &month, &day); \n" \
    "	else \n" \
    "		Jul_JulYMDofJDN ((dutc + JD_OF_J2000), &year, &month, &day); \n" \
    "} \n" \
    " \n" \
    "define Jul_GregYMDofJDN(jd, year, month, day) \n" \
    "{ /*ByRef year, month, day */ \n" \
    "    local l, n, i, j, d, m, y; \n" \
    " \n" \
    "	l = jd + 68569; \n" \
    "	n = (4*l) // 146097; \n" \
    "	l = l - (146097*n + 3)//4; \n" \
    "	i = (4000*(l+1))//1461001; \n" \
    "	l = l - (1461*i)//4 + 31; \n" \
    "	j = (80*l)//2447; \n" \
    "	d = l - (2447*j)//80; \n" \
    "	l = j//11; \n" \
    "	m = j + 2 - 12*l; \n" \
    "	y = 100*(n-49) + i + l; \n" \
    " \n" \
    "	*year  = y; \n" \
    "	*month = m; \n" \
    "	*day   = d; \n" \
    "} \n" \
    " \n" \
    "define Jul_JulYMDofJDN(jd, year, month, day) \n" \
    "{ /*ByRef year, month, day */ \n" \
    "    local	j, k, l, n, d, i, m, y; \n" \
    " \n" \
    "	j = jd + 1402; \n" \
    "	k = (j-1)//1461; \n" \
    "	l = j - 1461*k; \n" \
    "	n = (l-1)//365 - l//1461; \n" \
    "	i = l - 365*n + 30; \n" \
    "	j = (80*i)//2447; \n" \
    "	d = i - (2447*j)//80; \n" \
    "	i = j//11; \n" \
    "	m = j + 2 - 12*i; \n" \
    "	y = 4*k + n + i - 4716; \n" \
    " \n" \
    "	*year  = y; \n" \
    "	*month = m; \n" \
    "	*day   = d; \n" \
    "} \n" \
    " \n" \
    "define Jul_DUTCofYMD(year, month, day) \n" \
    "{ \n" \
    "    local isgreg; \n" \
    " \n" \
    "    /* Correct year & month ranges */ \n" \
    "	Jul_FixYM(&year, &month); \n" \
    " \n" \
    "    /* Determine which calendar to use */ \n" \
    "	if	  (year > gregorian_year)   isgreg = 1; \n" \
    "	else if   (year < gregorian_year)   isgreg = 0; \n" \
    "	else { \n" \
    "	  if      (month > gregorian_month) isgreg = 1; \n" \
    "	  else if (month < gregorian_month) isgreg = 0; \n" \
    "	  else                              isgreg = (day >= gregorian_day); \n" \
    "	} \n" \
    " \n" \
    "    /* Calculate and return date */ \n" \
    "	if (isgreg) return Jul_JDNofGregYMD(year, month, day) - JD_OF_J2000; \n" \
    "	else        return Jul_JDNofJulYMD (year, month, day) - JD_OF_J2000; \n" \
    "} \n" \
    " \n" \
    "define Jul_FixYM(year, month) \n" \
    "{ /*ByRef year, month */ \n" \
    "    local y, m, dyear; \n" \
    " \n" \
    "	y = *year; \n" \
    "	m = *month; \n" \
    " \n" \
    "    /* Shift month into range 1-12 */ \n" \
    "	dyear = (m-1) // 12;	 \n" \
    "	m -= 12 * dyear; \n" \
    "	y += dyear; \n" \
    " \n" \
    "	if (m < 1) { \n" \
    "		m += 12; \n" \
    "		y -= 1; \n" \
    "	} \n" \
    " \n" \
    "	*year  = y; \n" \
    "	*month = m; \n" \
    "} \n" \
    " \n" \
    "define Jul_JDNofGregYMD(year, month, day) \n" \
    "{ \n" \
    "    local temp = (month <= 2 ? -1:0); \n" \
    " \n" \
    "	return   (1461*(year + 4800 + temp))//4 \n" \
    "	       + (367*(month - 2 - 12*temp))//12 \n" \
    "	       - (3*((year + 4900 + temp)//100))//4 + day - 32075; \n" \
    "} \n" \
    " \n" \
    "define Jul_JDNofJulYMD(year, month, day) \n" \
    "{ \n" \
    "	return   367*year \n" \
    "	       - (7 *(year + 5001 + (month-9)//7))//4 \n" \
    "	       + (275*month)//9 \n" \
    "	       + day + 1729777; \n" \
    "} \n"

#define APCalc_DegreeAwareTrig (char*) \
    "define sind(x) {if (isreal(x)) return sin(fromangle*x);else return sin(x);};\n" \
    "define cosd(x) {if (isreal(x)) return cos(fromangle*x);else return cos(x);};\n" \
    "define tand(x) = tan(fromangle*x);\n" \
    "define secd(x) = sec(fromangle*x);\n" \
    "define cscd(x) = csc(fromangle*x);\n" \
    "define cotd(x) = cot(fromangle*x);\n" \
    "\n" \
    "define sinhd(x) = sinh(fromangle*x);\n" \
    "define coshd(x) = cosh(fromangle*x);\n" \
    "define tanhd(x) = tanh(fromangle*x);\n" \
    "define sechd(x) = sech(fromangle*x);\n" \
    "define cschd(x) = csch(fromangle*x);\n" \
    "define cothd(x) = coth(fromangle*x);\n" \
    "\n" \
    "define asind(x) = toangle*asin(x);\n" \
    "define acosd(x) = toangle*acos(x);\n" \
    "define atand(x) = toangle*atan(x);\n" \
    "define asecd(x) = toangle*asec(x);\n" \
    "define acscd(x) = toangle*acsc(x);\n" \
    "define acotd(x) = toangle*acot(x);\n" \
    "\n" \
    "define asinhd(x) = toangle*asinh(x);\n" \
    "define acoshd(x) = toangle*acosh(x);\n" \
    "define atanhd(x) = toangle*atanh(x);\n" \
    "define asechd(x) = toangle*asech(x);\n" \
    "define acschd(x) = toangle*acsch(x);\n" \
    "define acothd(x) = toangle*acoth(x);\n" \
    "\n" \
    "define atan2d(y,x) = toangle*atan2(y,x);\n"

#endif // APCALC_INIT_H
