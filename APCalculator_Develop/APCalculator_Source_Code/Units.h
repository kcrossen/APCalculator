struct UnitDefinition {
    char* Index;
    char* Category;
    char* UnitName;
    char* ConvertToSI; /* if(size(rpnstack)>=1) push(rpnstack, (ConvertToSI*pop(rpnstack))); */
    char* ConvertFromSI; /* if(size(rpnstack)>=1) push(rpnstack, (ConvertFromSI*pop(rpnstack))); */
};

UnitDefinition Units[] =
{
    /* Length, SIunit = meter, all exact, except parsecs, light years */
    {(char*) "2", (char*) "Length", (char*) "angstroms", (char*) "(1/(10*1000*1000*1000))", (char*) "(10*1000*1000*1000)"},
    {(char*) "2", (char*) "Length", (char*) "nanometers", (char*) "(1/(1000*1000*1000))", (char*) "(1000*1000*1000)"},
    {(char*) "2", (char*) "Length", (char*) "microns", (char*) "(1/(1000*1000))", (char*) "(1000*1000)"},
    {(char*) "2", (char*) "Length", (char*) "millimeters", (char*) "(1/1000)", (char*) "1000"},
    {(char*) "2", (char*) "Length", (char*) "centimeters", (char*) "(1/100)", (char*) "100"},
    {(char*) "2", (char*) "Length", (char*) "meters", (char*) "1", (char*) "1"},
    {(char*) "2", (char*) "Length", (char*) "kilometers", (char*) "1000", (char*) "0.001"},
    {(char*) "2", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "2", (char*) "Length", (char*) "mils", (char*) "(0.0254/1000)", (char*) "(1000/0.0254)"},
    {(char*) "2", (char*) "Length", (char*) "inches", (char*) "0.0254", (char*) "(1/0.0254)"},
    {(char*) "2", (char*) "Length", (char*) "feet", (char*) "0.3048", (char*) "(1/0.3048)"},
    {(char*) "2", (char*) "Length", (char*) "yards", (char*) "0.9144", (char*) "(1/0.9144)"},
    {(char*) "2", (char*) "Length", (char*) "miles", (char*) "1609.344", (char*) "(1/1609.344)"},
    {(char*) "2", (char*) "Length", (char*) "miles (nautical)", (char*) "1852", (char*) "(1/1852)"},
    {(char*) "2", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "2", (char*) "Length", (char*) "paces", (char*) "(2.5*0.3048)", (char*) "(1/(2.5*0.3048))"},
    {(char*) "2", (char*) "Length", (char*) "fathoms", (char*) "1.8288", (char*) "(1/1.8288)"},
    {(char*) "2", (char*) "Length", (char*) "rods", (char*) "(15.5*0.3048)", (char*) "(1/(15.5*0.3048))"},
    {(char*) "2", (char*) "Length", (char*) "furlongs", (char*) "201.168", (char*) "(1/201.168)"},
    {(char*) "2", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "2", (char*) "Length", (char*) "light years", (char*) "9.4607304725808e+12", (char*) "(1/9.4607304725808e+12)"},
    {(char*) "2", (char*) "Length", (char*) "parsecs", (char*) "3085677e+07", (char*) "(1/3085677e+07)"},
    /* Length, all exact, except parsecs, light years */

//    capefoot	cf	meter	0.314856
//    meter	m	meter	1
//    light-year	l.y.	meter	9,460,730,472,580,800
//    light-day	 	meter	25,902,068,371,200
//    light-hour	 	meter	1,079,252,848,800
//    light-minute	 	meter	17,987,547,480
//    light-second	 	meter	299,792,458

    /* Area, SIunit = sq meter */
    {(char*) "(2 * 2)", (char*) "Area", (char*) "sq millimeters", (char*) "0.000001", (char*) "(1000*1000)"},
    {(char*) "(2 * 2)", (char*) "Area", (char*) "sq centimeters", (char*) "(1/(100*100))", (char*) "(100*100)"},
    {(char*) "(2 * 2)", (char*) "Area", (char*) "sq meters", (char*) "1", (char*) "1"},
    {(char*) "(2 * 2)", (char*) "Area", (char*) "sq kilometers", (char*) "(1000*1000)", (char*) "(1/(1000*1000))"},
    {(char*) "(2 * 2)", (char*) "Area", (char*) "hectares", (char*) "10000", (char*) "(1/10000)"},
    {(char*) "(2 * 2)", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "(2 * 2)", (char*) "Area", (char*) "sq inches", (char*) "6.4516e-04", (char*) "(1/6.4516e-04)"},
    {(char*) "(2 * 2)", (char*) "Area", (char*) "sq feet", (char*) "9.290304e-02", (char*) "(1/9.290304e-02)"},
    {(char*) "(2 * 2)", (char*) "Area", (char*) "sq yards", (char*) "0.83612736", (char*) "(1/0.83612736)"},
    {(char*) "(2 * 2)", (char*) "Area", (char*) "sq rods", (char*) "((15.5*0.3048)*(15.5*0.3048))", (char*) "(1/((15.5*0.3048)*(15.5*0.3048)))"},
    {(char*) "(2 * 2)", (char*) "Area", (char*) "sq miles", (char*) "(1609.344*1609.344)", (char*) "(1/(1609.344*1609.344))"},
    {(char*) "(2 * 2)", (char*) "Area", (char*) "acres", (char*) "4046.8564224", (char*) "(1/4046.8564224)"},
    /* Area */

    /* Volume, SIunit = cu meter, all exact */
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "cu millimeters", (char*) "(1/(1000*1000*1000))", (char*) "(1000*1000*1000)"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "cu centimeters", (char*) "(1/(100*100*100))", (char*) "(100*100*100)"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "cu meters", (char*) "1", (char*) "1"},
    {(char*) "(2 * 2 * 2)", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "milliliters", (char*) "(1/(1000*1000))", (char*) "(1000*1000)"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "liters", (char*) "(1/1000)", (char*) "1000"},
    {(char*) "(2 * 2 * 2)", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "cu inches", (char*) "(1/61023.74409)", (char*) "61023.74409"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "cu feet", (char*) "2.8316846592e-02", (char*) "(1/2.8316846592e-02)"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "cu yards", (char*) "0.764554857984", (char*) "(1/0.764554857984)"},
    {(char*) "(2 * 2 * 2)", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "USfluid_ounce", (char*) "0.0295735295625e-03", (char*) "(1/0.0295735295625e-03)"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "USpint (dry)", (char*) "0.5506104713575e-03", (char*) "(1/0.5506104713575e-03)"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "USpint (liq)", (char*) "0.473176473e-03", (char*) "(1/0.473176473e-03)"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "USquart (dry)", (char*) "1.101220942715e-03", (char*) "(1/1.101220942715e-03)"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "USquart (liq)", (char*) "0.946352946e-03", (char*) "(1/0.946352946e-03)"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "USgallon (dry)", (char*) "4.40488377086e-03", (char*) "(1/4.40488377086e-03)"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "USgallon (liq)", (char*) "3.785411784e-03", (char*) "(1/3.785411784e-03)"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "USbushels", (char*) "(35.23907016688/1000)", (char*) "(1/(35.23907016688/1000))"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "barrels (oil)", (char*) "(158.987294928/1000)", (char*) "(1/(158.987294928/1000))"},
    {(char*) "(2 * 2 * 2)", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "UKfluid_ounce", (char*) "0.0284130625e-03", (char*) "(1/0.0284130625e-03)"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "UKpint", (char*) "0.56826125e-03", (char*) "(1/0.56826125e-03)"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "UKgallon", (char*) "4.54609e-03", (char*) "(1/4.54609e-03)"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "UKbushels", (char*) "(36.36872/1000)", (char*) "(1/(36.36872/1000))"},
    {(char*) "(2 * 2 * 2)", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "acre inches", (char*) "(4046.8564224*0.0254)", (char*) "(1/(4046.8564224*0.0254)"},
    {(char*) "(2 * 2 * 2)", (char*) "Volume", (char*) "acre feet", (char*) "(4046.8564224*0.3048)", (char*) "(1/(4046.8564224*0.3048)"},
    /* Volume, all exact */

    /* Time, SIUnti = second */
    {(char*) "3", (char*) "Time", (char*) "nanoseconds", (char*) "(1/(1000*1000*1000))", (char*) "(1000*1000*1000)"},
    {(char*) "3", (char*) "Time", (char*) "microseconds", (char*) "(1/(1000*1000))", (char*) "(1000*1000)"},
    {(char*) "3", (char*) "Time", (char*) "milliseconds", (char*) "(1/1000)", (char*) "1000"},
    {(char*) "3", (char*) "Time", (char*) "seconds", (char*) "1", (char*) "1"},
    {(char*) "3", (char*) "Time", (char*) "seconds (sidereal)", (char*) "0.99726956", (char*) "(1/0.99726956)"},
    {(char*) "3", (char*) "Time", (char*) "minutes", (char*) "60", (char*) "(1/60)"},
    {(char*) "3", (char*) "Time", (char*) "minutes (sidereal)", (char*) "59.83617361", (char*) "(1/59.83617361)"},
    {(char*) "3", (char*) "Time", (char*) "hours", (char*) "(60*60)", (char*) "(1/(60*60))"},
    {(char*) "3", (char*) "Time", (char*) "hours (sidereal)", (char*) "3590.170417", (char*) "(1/3590.170417)"},
    {(char*) "3", (char*) "Time", (char*) "days", (char*) "(24*60*60)", (char*) "(1/(24*60*60))"},
    {(char*) "3", (char*) "Time", (char*) "days (sidereal)", (char*) "86164.09", (char*) "(1/86164.09)"},
    {(char*) "3", (char*) "Time", (char*) "weeks", (char*) "(7*24*60*60)", (char*) "(1/(7*24*60*60))"},
    {(char*) "3", (char*) "Time", (char*) "weeks (sidereal)", (char*) "(31449892.85/52)", (char*) "(52/31449892.85)"},
    {(char*) "3", (char*) "Time", (char*) "months (sidereal)", (char*) "(31449892.85/12)", (char*) "(12/31449892.85)"},
    {(char*) "3", (char*) "Time", (char*) "years", (char*) "(365*24*60*60)", (char*) "(1/(365*24*60*60))"},
    {(char*) "3", (char*) "Time", (char*) "years (sidereal)", (char*) "31449892.85", (char*) "(1/31449892.85)"},
    {(char*) "3", (char*) "Time", (char*) "decades", (char*) "(10*365*24*60*60)", (char*) "(1/(10*365*24*60*60))"},
    {(char*) "3", (char*) "Time", (char*) "centuries", (char*) "(100*365*24*60*60)", (char*) "(1/(100*365*24*60*60))"},
    {(char*) "3", (char*) "Time", (char*) "millennia", (char*) "(1000*365*24*60*60)", (char*) "(1/(1000*365*24*60*60))"},
    /* Time */

    /* Velocity, SIunit = meters/second */
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "millimeters/sec", (char*) "(1/1000)", (char*) "1000"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "centimeters/sec", (char*) "(1/100)", (char*) "100"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "centimeters/min", (char*) "(1/(60*100)", (char*) "(60*100)"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "meters/sec", (char*) "1", (char*) "1"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "meters/min", (char*) "(1/60)", (char*) "60"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "meters/hour", (char*) "(1/(60*60))", (char*) "(60*60)"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "kilometers/sec", (char*) "1000", (char*) "(1/1000)"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "kilometers/hour", (char*) "(1000/(60*60))", (char*) "(1/(1000/(60*60)))"},
    {(char*) "(2 / 3)", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "inches/sec", (char*) "0.0254", (char*) "(1/0.0254)"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "inches/min", (char*) "(0.0254/60)", (char*) "(60/0.0254)"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "feet/sec", (char*) "0.3048", (char*) "(1/0.3048)"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "feet/min", (char*) "(0.3048/60)", (char*) "(60/0.3048)"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "feet/hour", (char*) "(0.3048/(60*60))", (char*) "((60*60)/0.3048)"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "yards/sec", (char*) "0.9144", (char*) "(1/0.9144)"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "yards/min", (char*) "(0.9144/60)", (char*) "(60/0.9144)"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "yards/hour", (char*) "(0.9144/(60*60))", (char*) "((60*60)/0.9144)"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "miles/sec", (char*) "1609.344", (char*) "(1/1609.344)"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "miles/min", (char*) "(1609.344/60)", (char*) "(60/1609.344)"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "miles/hour", (char*) "(1609.344/(60*60))", (char*) "((60*60)/1609.344)"},
    {(char*) "(2 / 3)", (char*) "Velocity", (char*) "knots (nm/hr)", (char*) "(1852/(60*60))", (char*) "((60*60)/1852)"},
    /* Velocity */

//    speed-of-light (vacuum)	c	meter per second	299792458

    /* Acceleration, SIunit = meters/second/second */
    {(char*) "(2 / (3 * 3))", (char*) "Acceleration", (char*) "centimeters/sec/sec", (char*) "0.01", (char*) "(1/0.01)"},
    {(char*) "(2 / (3 * 3))", (char*) "Acceleration", (char*) "meters/sec/sec", (char*) "1", (char*) "1"},
    {(char*) "(2 / (3 * 3))", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "(2 / (3 * 3))", (char*) "Acceleration", (char*) "inches/sec/sec", (char*) "0.0254", (char*) "(1/0.0254)"},
    {(char*) "(2 / (3 * 3))", (char*) "Acceleration", (char*) "feet/sec/sec", (char*) "0.3048", (char*) "(1/0.3048)"},
    {(char*) "(2 / (3 * 3))", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "(2 / (3 * 3))", (char*) "Acceleration", (char*) "miles/hr/sec", (char*) "0.44704", (char*) "(1/0.44704)"},
    {(char*) "(2 / (3 * 3))", (char*) "Acceleration", (char*) "miles/min/sec", (char*) "26.8244", (char*) "(1/26.8244)"},
    {(char*) "(2 / (3 * 3))", (char*) "Acceleration", (char*) "miles/sec/sec", (char*) "1609.344", (char*) "(1/1609.344)"},
    {(char*) "(2 / (3 * 3))", (char*) "Acceleration", (char*) "knots/sec", (char*) "0.5144444", (char*) "(1/0.5144444)"},
    /* Acceleration */

//    foot per hour per second	ft/(h·s)	meter per second squared	8.46667E-05
//    foot per minute per second	ft/(min·s)	meter per second squared	0.00508
//    galileo	Gal	meter per second squared	0.01
//    gravity (standard)	gn	meter per second squared	9.80665
//    inch per hour per second	in/(h·s)	meter per second squared	7.05556E-06
//    inch per minute per second	in/(min·s)	meter per second squared	4.23333E-04
//    meter per second squared	m/s2	meter per second squared	1

    /* Mass, SIunit = kg */
    {(char*) "5", (char*) "Mass", (char*) "grams", (char*) "(1/1000)", (char*) "1000"},
    {(char*) "5", (char*) "Mass", (char*) "kg", (char*) "1", (char*) "1"},
    {(char*) "5", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "5", (char*) "Mass", (char*) "pounds (av)", (char*) "0.45359237", (char*) "(1/0.45359237)"},
    /* Mass */

//    carat (metric)	ct	gram	0.2
//    point (metric)	pt	gram	0.002
//    dram (avdp)	dr	gram	1.771845195
//    dram (troy)	dr	gram	3.8879346
//    grain (metric)	gr	gram	0.05
//    grain (troy)	gr	gram	0.06479891
//    gram	g	gram	1
//    hundredweight (long)	hwt	gram	50802.34544
//    hundredweight (short)	hwt	gram	45359.237
//    kilogram	kg	gram	1000
//    megagram	Mg	gram	1000000
//    milligram	mg	gram	0.001
//    ounce (avdp)	oz	gram	28.34952313
//    ounce (troy)	oz	gram	31.1034768
//    pennyweight	dwt	gram	1.55517384
//    pound (avdp)	lb	gram	453.59237
//    pound (metric)	lb	gram	500
//    pound (troy)	lb	gram	373.2417216
//    slug	slug	gram	14593.903
//    stone	st	gram	6350.29318
//    ton-assay (long)	l AT	gram	32.666667
//    ton-assay (short)	sh AT	gram	29.166667
//    ton (long)	l tn	gram	1016046.909
//    ton (short)	sh tn	gram	907184.74
//    ton-metric	t	gram	1000000
//    tonne (U.S. metric ton)	t	gram	1000000

    /* Energy, SIunit = joule */
    {(char*) "7", (char*) "Energy", (char*) "erg", (char*) "0.0000001", (char*) "(1/0.0000001)"},
    {(char*) "7", (char*) "Energy", (char*) "joules", (char*) "1", (char*) "1"},
    {(char*) "7", (char*) "Energy", (char*) "watt-second", (char*) "1", (char*) "1"},
    {(char*) "7", (char*) "Energy", (char*) "watt-hour", (char*) "(60*60)", (char*) "(1/(60*60))"},
    {(char*) "7", (char*) "Energy", (char*) "kilowatt-hour", (char*) "(1000*60*60)", (char*) "(1/(1000*60*60))"},
    {(char*) "7", (char*) "Energy", (char*) "megajoules", (char*) "(1000*1000)", (char*) "(1/(1000*1000))"},
    {(char*) "7", (char*) "Energy", (char*) "calories (mean)", (char*) "4.19002", (char*) "(1/4.19002)"},
    {(char*) "7", (char*) "Energy", (char*) "kilocalories (mean)", (char*) "4190.02", (char*) "(1/4190.02)"},
    {(char*) "7", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "7", (char*) "Energy", (char*) "inch-pound-force", (char*) "0.112984829", (char*) "(1/0.112984829)"},
    {(char*) "7", (char*) "Energy", (char*) "foot-pound-force", (char*) "1.355818", (char*) "(1/1.355818)"},
    {(char*) "7", (char*) "Energy", (char*) "BTU (mean)", (char*) "1055.87", (char*) "(1/1055.87)"},
    /* Energy */

//    British thermal unit [IT]	BTUIT	joule	1055.056
//    British thermal unit [th]	BTUth	joule	1054.35
//    British thermal unit [mean]	BTUmean	joule	1055.87
//    British thermal unit [39°F]	BTU39°F	joule	1059.67
//    British thermal unit [59°F]	BTU59°F	joule	1054.8
//    British thermal unit [60°F]	BTU60°F	joule	1054.68
//    calorie [IT]	calIT	joule	4.1868
//    calorie [th]	calth	joule	4.184
//    calorie [mean]	calmean	joule	4.19002
//    calorie [15°C]	cal15°C	joule	4.1858
//    calorie [20°C]	cal20°C	joule	4.1819
//    electronvolt	eV	joule	1.60218E-19
//    foot-poundal	ft·pdl	joule	0.04214011
//    joule	J	joule	1
//    kilocalorie [IT]	kcalIT	joule	4186.8
//    kilocalorie [th]	kcalth	joule	4184
//    kilocalorie [mean]	kcalmean	joule	4190.02
//    quad (IT)	quad	joule	1.05506E+18
//    therm (EC)	therm	joule	105506000
//    therm (U.S.)	therm	joule	105480400
//    ton-of-coal-equivalent	TOC	joule	29307600000
//    ton-of-oil-equivalent	TOE	joule	41868000000
//    ton-of-TNT-equivalent	tTNT	joule	4184000000

    /* Power, SIunit = watt */
    {(char*) "(7 / 2)", (char*) "Power", (char*) "watts", (char*) "1", (char*) "1"},
    {(char*) "(7 / 2)", (char*) "Power", (char*) "kilowatts", (char*) "1000", (char*) "(1/1000)"},
    {(char*) "(7 / 2)", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "(7 / 2)", (char*) "Power", (char*) "horsepower", (char*) "745.69987158227022", (char*) "(1/745.69987158227022)"},
    /* Power */

//    BTU [IT] per hour	BTUIT/h	watt	0.2930711
//    BTU [IT] per minute	BTUIT/min	watt	0.2930711*60
//    BTU [IT] per second	BTUIT/s	watt	0.2930711*60*60
//    calorie [IT] per hour	calIT/h	watt	4.1868/60/60
//    calorie [IT] per minute	calIT/min	watt	4.1868/60
//    calorie [IT] per second	calIT/sec	watt	4.1868
//    BTU [th] per hour	BTUth/h	watt	0.2928751
//    BTU [th] per minute	BTUth/min	watt	0.2928751*60
//    BTU [th] per second	BTUth/s	watt	0.2928751*60*60
//    calorie [th] per hour	calth/h	watt	4.184/60/60
//    calorie [th] per minute	calth/min	watt	4.184/60
//    calorie [th] per second	calth/s	watt	4.184
//    cheval-vapeur	cv	watt	735.49875
//    erg per hour	erg/h	watt	0.0000001/60/60
//    erg per minute	erg/min	watt	0.0000001/60
//    erg per second	erg/s	watt	0.0000001
//    foot-pound-force per hour	ft·lbf/h	watt	1.355818/60/60
//    foot-pound-force per minute	ft·lbf/min	watt	1.355818/60
//    foot-pound-force per second	ft·lbf/s	watt	1.355818
//    foot-poundal per hour	ft·pdl/h	watt	0.04214011/60/60
//    foot-poundal per minute	ft·pdl/min	watt	0.04214011/60
//    foot-poundal per second	ft·pdl/s	watt	0.04214011
//    horsepower (550 ft � lbf/s)	hp	watt	745.6999
//    horsepower (boiler)	hp	watt	9809.5
//    horsepower (electric)	hp	watt	746
//    horsepower (metric)	hp	watt	735.49875
//    horsepower (U.K.)	hp	watt	745.7
//    horsepower (water)	hp	watt	746.043
//    joule per hour	J/h	watt	1/60/60
//    joule per minute	J/min	watt	1/60
//    joule per second	J/s	watt	1
//    pferdestarke	PS	watt	735.49875
//    watt	W	watt	1

    /* Force, SIunit = newton */
    {(char*) "11", (char*) "Force", (char*) "dynes", (char*) "0.00001", (char*) "(1/0.00001)"},
    {(char*) "11", (char*) "Force", (char*) "newtons", (char*) "1", (char*) "1"},
    {(char*) "11", (char*) "Force", (char*) "kilogram-force", (char*) "9.80665", (char*) "(1/9.80665)"},
    {(char*) "11", (char*) "Force", (char*) "kilonewtons", (char*) "1000", (char*) "(1/1000)"},
    {(char*) "11", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "11", (char*) "Force", (char*) "poundal", (char*) "0.138255", (char*) "(1/0.138255)"},
    {(char*) "11", (char*) "Force", (char*) "ounce-force", (char*) "0.2780139", (char*) "(1/0.2780139)"},
    {(char*) "11", (char*) "Force", (char*) "pound-force", (char*) "4.448222", (char*) "(1/4.448222)"},
    {(char*) "11", (char*) "Force", (char*) "ton-force", (char*) "(2000*4.448222)", (char*) "(1/(2000*4.448222))"},
    /* Force */

//    kilopond	kp	newton	9.80665
//    kip	kip	newton	4448.222
//    newton	N	newton	1

    /* Pressure, SIunit = pascal */
    {(char*) "13", (char*) "Pressure", (char*) "pascal", (char*) "1", (char*) "1"},
    {(char*) "13", (char*) "Pressure", (char*) "hectopascal", (char*) "100", (char*) "(1/100)"},
    {(char*) "13", (char*) "Pressure", (char*) "kilopascal", (char*) "1000", (char*) "(1/1000)"},
    {(char*) "13", (char*) "Pressure", (char*) "centimeters of mercury", (char*) "1333.22", (char*) "(1/1333.22)"},
    {(char*) "13", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "13", (char*) "Pressure", (char*) "inches of mercury", (char*) "3386.389", (char*) "(1/3386.389)"},
    {(char*) "13", (char*) "Pressure", (char*) "pounds/sq inch", (char*) "6894.757", (char*) "(1/6894.757)"},
    /* Pressure */

// Pressure
//    atmosphere-standard	atm	pascal	101325
//    atmosphere-technical	at	pascal	98066.5
//    bar	bar	pascal	100000
//    decibar	dbar	pascal	1000
//    millibar	mbar	pascal	100
//    barye (cgs unit)	barye	pascal	0.1
//    centimeter of water (4 °C)	cmH2O	pascal	98.0638
//    foot of mercury (conventional)	ftHg	pascal	40636.66
//    foot of water (39.2 °F)	ftH2O	pascal	2988.98
//    inch of water (39.2 °F)	inH2O	pascal	248.082
//    kilogram-force per square millimeter	kgf/mm2	pascal	9806650
//    kip per square inch	kip/in2	pascal	6894757
//    millimeter of mercury	mmHg	pascal	133.3224
//    millimeter of water (3.98 °C)	mmH2O	pascal	9.80638
//    pascal	Pa	pascal	1
//    pound per square foot	lb/ft2	pascal	47.88025
//    poundal per square foot	pdl/ft2	pascal	1.488164
//    short ton per square foot	sh tn/ft2	pascal	95760.518
//    torr	torr	pascal	133.3224

    /* Angle, SIunit = radian */
    {(char*) "17", (char*) "Angle", (char*) "arcsec", (char*) "((pi/180)/(60*60))", (char*) "((60*60)/(pi/180)"},
    {(char*) "17", (char*) "Angle", (char*) "arcmin", (char*) "((pi/180)/60)", (char*) "(60/(pi/180))"},
    {(char*) "17", (char*) "Angle", (char*) "degrees", (char*) "(pi/180)", (char*) "(1/(pi/180))"},
    {(char*) "17", (char*) "Angle", (char*) "radians", (char*) "1", (char*) "1"},
    {(char*) "17", (char*) "Angle", (char*) "revolution", (char*) "(2*Pi)", (char*) "(1/(2*Pi))"},
    {(char*) "17", (char*) "", (char*) "", (char*) "", (char*) ""},
    {(char*) "17", (char*) "Angle", (char*) "octant", (char*) "((2*Pi)/8)", (char*) "(8/(2*Pi))"},
    {(char*) "17", (char*) "Angle", (char*) "sextant", (char*) "((2*Pi)/6)", (char*) "(6/(2*Pi))"},
    {(char*) "17", (char*) "Angle", (char*) "quadrant", (char*) "((2*Pi)/4)", (char*) "(4/(2*Pi))"},
    /* Angle */

//    gon	gon	degree	360/400	0.9	radian	2π/400	0.01570796
//    mil	mil	degree	360/6400	0.05625	radian	2π/6400	9.817477e-4

    /* Temperature, SIunit = Kelvin, all exact */
    {(char*) "19", (char*) "Temperature", (char*) "degrees F", (char*) "if(size(rpnstack)>=1) push(rpnstack, ((pop(rpnstack)-32)*(5/9)+273.15));", (char*) "if(size(rpnstack)>=1) push(rpnstack, ((pop(rpnstack)-273.15)*(9/5)+32));"},
    {(char*) "19", (char*) "Temperature", (char*) "degrees C", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)+273.15));", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)-273.15));"},
    {(char*) "19", (char*) "Temperature", (char*) "degrees K", (char*) "if(size(rpnstack)>=1) push(rpnstack, pop(rpnstack));", (char*) "if(size(rpnstack)>=1) push(rpnstack, pop(rpnstack));"},
    /* Temperature, all exact */

    /* must be last conversion */ {(char*) "", (char*) "", (char*) "", (char*) "", (char*) ""} /* must be last conversion */
};

struct UnitsConversionDefinition {
    int Index;
    char* Category;
    char* Conversion;
    char* Factor;
    char* Program;
};

UnitsConversionDefinition UnitsConversions[] =
{
    /* Length, all exact, except parsecs, light years */
    {1, (char*) "Length", (char*) "centimeters to inches", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/2.54));", (char*) "( ?cm / 2.54 /*cm:in*/ )"},
    {1, (char*) "Length", (char*) "meters to feet", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/0.3048));", (char*) "( ?m / 0.3048 /*m:ft*/ )"},
    {1, (char*) "Length", (char*) "meters to yards", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/0.9144));", (char*) "( ?m / 0.9144 /*m:yd*/ )"},
    {1, (char*) "Length", (char*) "kilometers to miles", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/1.609344));", (char*) "( ?km / 1.609344 /*km:mi*/ )"},
    {1, (char*) "Length", (char*) "kilometers to miles {nautical)", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/1.852));", (char*) "( ?km / 1.852 /*km:nmi*/ )"},
    {1, (char*) "Length", (char*) "kilometers to light years", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/9.4607304725808e+12));", (char*) "( ?km / 9.4607304725808e+12 /*km:ly*/ )"},
    {1, (char*) "Length", (char*) "kilometers to parsecs", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/3085677e+07));", (char*) "( ?km / 3085677e+07 /*km:pa*/ )"},
    {1, (char*) "", (char*) "", (char*) "", (char*) ""},
    {1, (char*) "Length", (char*) "inches to centimeters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (2.54*pop(rpnstack)));", (char*) "( ?in * 2.54 /*in:cm*/ )"},
    {1, (char*) "Length", (char*) "feet to meters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.3048*pop(rpnstack)));", (char*) "( ?m * 0.3048 /*ft:m*/ )"},
    {1, (char*) "Length", (char*) "yards to meters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.9144*pop(rpnstack)));", (char*) "( ?yd * 0.9144 /*yd:m*/ )"},
    {1, (char*) "Length", (char*) "miles to kilometers", (char*) "if(size(rpnstack)>=1) push(rpnstack, (1.609344*pop(rpnstack)));", (char*) "( ?mi * 1.609344 /*mi:km*/ )"},
    {1, (char*) "Length", (char*) "miles {nautical) to kilometers", (char*) "if(size(rpnstack)>=1) push(rpnstack, (1.852*pop(rpnstack)));", (char*) "( ?nmi * 1.852 /*nmi :km*/ )"},
    {1, (char*) "Length", (char*) "light years to kilometers", (char*) "if(size(rpnstack)>=1) push(rpnstack, (9.4607304725808e+12*pop(rpnstack)));", (char*) "( ?ly * 9.4607304725808e+12 /*ly:km*/ )"},
    {1, (char*) "Length", (char*) "parsecs to kilometers", (char*) "if(size(rpnstack)>=1) push(rpnstack, (3085677e+07*pop(rpnstack)));", (char*) "( ?pa * 3085677e+07 /*pa:km*/ )"},
    {1, (char*) "", (char*) "", (char*) "", (char*) ""},
    {1, (char*) "Length", (char*) "inches to feet", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/12));", (char*) "( ?in / 12 /*in:ft*/ )"},
    {1, (char*) "Length", (char*) "inches to yards", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/36));", (char*) "( ?in / 36 /*in:yd*/ )"},
    {1, (char*) "Length", (char*) "feet to pace", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/2.5));", (char*) "( ?ft / 2.5 /*ft:pace*/ )"},
    {1, (char*) "Length", (char*) "feet to rod", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/16.5));", (char*) "( ?ft / 16.5 /*ft:rod*/ )"},
    {1, (char*) "Length", (char*) "feet to miles", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/5280));", (char*) "( ?ft / 5280 /*ft:mi*/ )"},
    {1, (char*) "Length", (char*) "yards to miles", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/1760));", (char*) "( ?yd / 1760 /*yd:mi*/ )"},

    {1, (char*) "Length", (char*) "inches to points", (char*) "if(size(rpnstack)>=1) push(rpnstack, (72.272*pop(rpnstack)));", (char*) "( ?in * 72.272 /*in:pt*/ )"},
    {1, (char*) "Length", (char*) "feet to inches", (char*) "if(size(rpnstack)>=1) push(rpnstack, (12*pop(rpnstack)));", (char*) "( ?ft * 12 /*ft:in*/ )"},
    {1, (char*) "Length", (char*) "yards to inches", (char*) "if(size(rpnstack)>=1) push(rpnstack, (36*pop(rpnstack)));", (char*) "( ?yd * 36 /*yd:in*/ )"},
    {1, (char*) "Length", (char*) "pace to feet", (char*) "if(size(rpnstack)>=1) push(rpnstack, (2.5*pop(rpnstack)));", (char*) "( ?pace * 2.5 /*pace:ft*/ )"},
    {1, (char*) "Length", (char*) "rod to feet", (char*) "if(size(rpnstack)>=1) push(rpnstack, (15.5*pop(rpnstack)));", (char*) "( ?rd * 16.5 /*rd:ft*/ )"},
    {1, (char*) "Length", (char*) "miles to feet", (char*) "if(size(rpnstack)>=1) push(rpnstack, (5280*pop(rpnstack)));", (char*) "( ?mi * 5280 /*mi:ft*/ )"},
    {1, (char*) "Length", (char*) "miles to yards", (char*) "if(size(rpnstack)>=1) push(rpnstack, (1760*pop(rpnstack)));", (char*) "( ?mi * 1760 /*mi:yd*/ )"},
    /* Length, all exact, except parsecs, light years */

    /* Area */
    {2, (char*) "Area", (char*) "sq millimeters to sq inches", (char*) "if(size(rpnstack)>=1) push(rpnstack, (1.550003e-03*pop(rpnstack)));", (char*) "( ?sqmm * 1.550003e-03 /*sqmm:sqin*/ )"},
    {2, (char*) "Area", (char*) "sq centimeters to sq inches", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.1550003*pop(rpnstack)));", (char*) "( ?sqcm * 0.1550003 /*sqcm:sqin*/ )"},
    {2, (char*) "Area", (char*) "sq centimeters to sq feet", (char*) "if(size(rpnstack)>=1) push(rpnstack, (1.076391e-03*pop(rpnstack)));", (char*) "( ?sqcm * 1.076391e-03 /*sqcm:sqft*/ )"},
    {2, (char*) "Area", (char*) "sq meters to sq feet", (char*) "if(size(rpnstack)>=1) push(rpnstack, (1.076391e+01*pop(rpnstack)));", (char*) "(1.076391e /*sqm:sqft*/+01 * ?sqm )"},
    {2, (char*) "Area", (char*) "sq meters to sq yards", (char*) "if(size(rpnstack)>=1) push(rpnstack, (1.1959900463*pop(rpnstack)));", (char*) "( ?sqm * 1.1959900463 /*sqm:sqyd*/ )"},
    {2, (char*) "Area", (char*) "sq meters to acres", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/4046.8564224));", (char*) "( ?sqm / 4046.8564224 /*sqm:ac*/ )"},
    {2, (char*) "Area", (char*) "hectares to acres", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/0.40468564224));", (char*) "( ?ha / 0.40468564224 /*ha:ac*/ )"},
    {2, (char*) "", (char*) "", (char*) "", (char*) ""},
    {2, (char*) "Area", (char*) "sq inches to sq millimeters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (6.4516e+02*pop(rpnstack)));", (char*) "(6.4516e /*sqin:sqmm*/+02 * ?sqin )"},
    {2, (char*) "Area", (char*) "sq inches to sq centimeters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (6.4516*pop(rpnstack)));", (char*) "( ?sqin * 6.4516 /*sqin:sqcm*/ )"},
    {2, (char*) "Area", (char*) "sq feet to sq centimeters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (9.290304e+02*pop(rpnstack)));", (char*) "(9.290304e /*sqft:sqcm*/+02 * ?sqft )"},
    {2, (char*) "Area", (char*) "sq feet to sq meters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (9.290304e-02*pop(rpnstack)));", (char*) "( ?sqft * 9.290304e-02 /*sqft:sqm*/ )"},
    {2, (char*) "Area", (char*) "sq yards to sq meters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.83612736*pop(rpnstack)));", (char*) "( ?sqyd * 0.83612736 /*sqyd:sqm*/ )"},
    {2, (char*) "Area", (char*) "acres to sq meters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (4046.8564224*pop(rpnstack)));", (char*) "( ?ac * 4046.8564224 /*ac:sqm*/ )"},
    {2, (char*) "Area", (char*) "acres to hectares", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.40468564224*pop(rpnstack)));", (char*) "( ?ac * 0.40468564224 /*ac:ha*/ )"},
    {2, (char*) "", (char*) "", (char*) "", (char*) ""},
    {2, (char*) "Area", (char*) "sq inches to sq feet", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/144));", (char*) "( ?sqin / 144 /*sqin:sqft*/ )"},
    {2, (char*) "Area", (char*) "sq inches to sq yards", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/1296));", (char*) "( ?sqin / 1296 /*sqin:sqyd*/ )"},
    {2, (char*) "Area", (char*) "sq feet to acres", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/43560));", (char*) "( ?sqft / 43560 /*sqft:ac*/ )"},
    {2, (char*) "Area", (char*) "sq yards to acres", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/4840));", (char*) "( ?sqyd / 4840 /*sqyd:ac*/ )"},
    {2, (char*) "Area", (char*) "acres to sq yards", (char*) "if(size(rpnstack)>=1) push(rpnstack, (4840*pop(rpnstack)));", (char*) "( ?ac * 4840 /*ac:sqyd*/ )"},
    {2, (char*) "Area", (char*) "acres to sq feet", (char*) "if(size(rpnstack)>=1) push(rpnstack, (43560*pop(rpnstack)));", (char*) "( ?ac * 43560 /*ac:sqft*/ )"},
    {2, (char*) "Area", (char*) "sq yards to sq inches", (char*) "if(size(rpnstack)>=1) push(rpnstack, (1296*pop(rpnstack)));", (char*) "( ?sqyd * 1296 /*sqyd:sqin*/ )"},
    {2, (char*) "Area", (char*) "sq feet to sq inches", (char*) "if(size(rpnstack)>=1) push(rpnstack, (144*pop(rpnstack)));", (char*) "( ?sqft * 144 /*sqft:sqin*/ )"},
    /* Area */

    /* Volume, all exact */
    {3, (char*) "Volume", (char*) "cu centimeters to cu inches", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/16.387064));", (char*) "( ?cucm / 16.387064 /*cucm:cuin*/ )"},
    {3, (char*) "Volume", (char*) "cu meters to cu inches", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/1.6387064e-05));", (char*) "( ?cum / 1.6387064e-05 /*cum:cuin*/ )"},
    {3, (char*) "Volume", (char*) "cu meters to cu feet", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/2.8316846592e-02));", (char*) "( ?cum / 2.8316846592e-02 /*cum:cuft*/ )"},
    {3, (char*) "Volume", (char*) "cu meters to cu yards", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/0.764554857984));", (char*) "( ?cum / 0.764554857984 /*cum:cuyd*/ )"},
    {3, (char*) "Volume", (char*) "liters to cu feet", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/2.8316846592e+01));", (char*) "( ?l / 2.8316846592e+01 /*l:cuft*/ )"},
    {3, (char*) "Volume", (char*) "liters to barrels (oil)", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/158.987294928));", (char*) "( ?l / 158.987294928 /*l:barrel*/ )"},
    {3, (char*) "Volume", (char*) "liters to bushels (UK)", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/36.36872));", (char*) "( ?l / 36.36872 /*l:bu_uk*/ )"},
    {3, (char*) "Volume", (char*) "liters to bushels (US)", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/35.23907016688));", (char*) "( ?l / 35.23907016688 /*l:bu_us*/ )"},
    {3, (char*) "", (char*) "", (char*) "", (char*) ""},
    {3, (char*) "Volume", (char*) "cu inches to cu centimeters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (16.387064*pop(rpnstack)));", (char*) "( ?cuin * 16.38706 /*cuin:cucm*/ )"},
    {3, (char*) "Volume", (char*) "cu inches to cu meters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (1.6387064e-05*pop(rpnstack)));", (char*) "( ?cuin * 61023.74409 /*cuin:cum*/ )"},
    {3, (char*) "Volume", (char*) "cu feet to cu meters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (2.8316846592e-02*pop(rpnstack)));", (char*) "( ?cuft * 2.831685e-02 /*cuft:cum*/ )"},
    {3, (char*) "Volume", (char*) "cu yards to cu meters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.764554857984*pop(rpnstack)));", (char*) "( ?cuyd * 0.764554857984 /*cuyd:cum*/ )"},
    {3, (char*) "Volume", (char*) "cu feet to liters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (2.8316846592e+01*pop(rpnstack)));", (char*) "( ?cuft * 2.8316846592e+01 /*cuft:l*/ )"},
    {3, (char*) "Volume", (char*) "barrels (oil) to liters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (158.987294928*pop(rpnstack)));", (char*) "( ?barrel * 158.987294928 /*barrel:l*/ )"},
    {3, (char*) "Volume", (char*) "bushels (UK) to liters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (36.36872*pop(rpnstack)));", (char*) "( ?bu_uk * 36.36872 /*bu_uk:l*/ )"},
    {3, (char*) "Volume", (char*) "bushels (US) to liters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (35.23907016688*pop(rpnstack)));", (char*) "( ?bu_us * 35.23907016688 /*bu_us:l*/ )"},
    {3, (char*) "", (char*) "", (char*) "", (char*) ""},
    {3, (char*) "Volume", (char*) "cu inches to cu feet", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/1728));", (char*) "( ?cuin * 5.787037037e-04 /*cuin:cuft*/ )"},
    {3, (char*) "Volume", (char*) "cu inches to cu yards", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack/46656)));", (char*) "( ?cuin * 2.14334705e-05 /*cuin:cuyd*/ )"},
    {3, (char*) "Volume", (char*) "cu feet to cu inches", (char*) "if(size(rpnstack)>=1) push(rpnstack, (1728*pop(rpnstack)));", (char*) "( ?cuft * 1728 /*cuft:cuin*/ )"},
    {3, (char*) "Volume", (char*) "cu yards to cu inches", (char*) "if(size(rpnstack)>=1) push(rpnstack, (46656*pop(rpnstack)));", (char*) "( ?cuyd * 46656 /*cuyd:cuin*/ )"},
    /* Volume, all exact */

    /* Capacity, all exact */
    {4, (char*) "Capacity", (char*) "liters to UKfluid_ounce", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/0.0284130625));", (char*) "( ?l / 0.0284130625 /*l:floz_uk*/ )"},
    {4, (char*) "Capacity", (char*) "liters to USfluid_ounce", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/0.0295735295625));", (char*) "( ?l / 0.0295735295625 /*l:floz_us*/ )"},
    {4, (char*) "Capacity", (char*) "liters to UKpint", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/0.56826125));", (char*) "( ?l / 0.56826125 /*l:pint_uk*/ )"},
    {4, (char*) "Capacity", (char*) "liters to USpint (dry)", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/0.0.5506104713575));", (char*) "( ?l / 0.5506104713575 /*l:pint_us_dry*/ )"},
    {4, (char*) "Capacity", (char*) "liters to USpint (liq)", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/0.473176473));", (char*) "( ?l / 0.473176473 /*l:pint_us_liq*/ )"},
    {4, (char*) "Capacity", (char*) "liters to USquart (dry)", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/1.101220942715));", (char*) "( ?l / 1.101220942715 /*l:qt_us_dry*/ )"},
    {4, (char*) "Capacity", (char*) "liters to USquart (liq)", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/0.946352946));", (char*) "( ?l / 0.946352946 /*l:qt_us_liq*/ )"},
    {4, (char*) "Capacity", (char*) "liters to UKgallon", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/4.54609));", (char*) "( ?l / 4.54609 /*l:gal_uk*/ )"},
    {4, (char*) "Capacity", (char*) "liters to USgallon (dry)", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/4.40488377086));", (char*) "( ?l / 4.40488377086 /*l:gal_us_dry*/ )"},
    {4, (char*) "Capacity", (char*) "liters to USgallon (liq)", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/3.785411784));", (char*) "( ?l / 3.785411784 /*l:gal_us_liq*/ )"},
    {4, (char*) "Capacity", (char*) "cu meters to USgallon (liq)", (char*) "if(size(rpnstack)>=1) push(rpnstack, (pop(rpnstack)/3.785411784e-03));", (char*) "( ?cum / 3.785411784e-03 /*cum:gal_us_liq*/ )"},
    {4, (char*) "", (char*) "", (char*) "", (char*) ""},
    {4, (char*) "Capacity", (char*) "UKfluid_ounce to liters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.0284130625*pop(rpnstack)));", (char*) "( ?floz_uk * 0.0284130625 /*floz_uk:l*/ )"},
    {4, (char*) "Capacity", (char*) "USfluid_ounce to liters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.0295735295625*pop(rpnstack)));", (char*) "( ?floz_us * 0.0295735295625 /*floz_us:l*/ )"},
    {4, (char*) "Capacity", (char*) "UKpint to liters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.56826125*pop(rpnstack)));", (char*) "( ?pint_uk * 0.56826125 /*pint_uk:l*/ )"},
    {4, (char*) "Capacity", (char*) "USpint (dry) to liters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.0.5506104713575*pop(rpnstack)));", (char*) "( ?pint_us_dry * 0.5506104713575 /*pint_us_dry:l*/ )"},
    {4, (char*) "Capacity", (char*) "USpint (liq) to liters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.473176473*pop(rpnstack)));", (char*) "( ?pint_us_liq * 0.473176473 /*pint_us_liq:l*/ )"},
    {4, (char*) "Capacity", (char*) "USquart (dry) to liters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (1.101220942715*pop(rpnstack)));", (char*) "( ?qt_us_dry * 1.101220942715 /*qt_us_dry:l*/ )"},
    {4, (char*) "Capacity", (char*) "USquart (liq) to liters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.946352946*pop(rpnstack)));", (char*) "( ?qt_us_liq * 0.946352946 /*qt_us_liq:l*/ )"},
    {4, (char*) "Capacity", (char*) "UKgallon to liters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (4.54609*pop(rpnstack)));", (char*) "( ?gal_uk * 4.54609 /*gal_uk:l*/ )"},
    {4, (char*) "Capacity", (char*) "USgallon (dry) to liters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (4.40488377086*pop(rpnstack)));", (char*) "( ?gal_us_dry * 4.40488377086 /*gal_us_dry:l*/ )"},
    {4, (char*) "Capacity", (char*) "USgallon (liq) to liters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (3.785411784*pop(rpnstack)));", (char*) "( ?gal_us_liq * 3.785411784 /*gal_us_liq:l*/ )"},
    {4, (char*) "Capacity", (char*) "USgallon (liq) to cu meters", (char*) "if(size(rpnstack)>=1) push(rpnstack, (3.785411784e-03*pop(rpnstack)));", (char*) "( ?gal_us_liq * 3.785411784e-03 /*gal_us_liq:cum*/ )"},
    /* Capacity, all exact */

    /* Mass/Force */
    {5, (char*) "Mass/Force", (char*) "kg to pound (av)", (char*) "if(size(rpnstack)>=1) push(rpnstack, (2.20462262*pop(rpnstack)));", (char*) "( ?kg * 2.20462262 /*kg:lb*/ )"},
    {5, (char*) "", (char*) "", (char*) "", (char*) ""},
    {5, (char*) "Mass/Force", (char*) "pound (av) to kg", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.45359237*pop(rpnstack)));", (char*) "( ?lb * 0.45359237 /*lb:kg*/ )"},
    /* Mass/Force */

    /* Energy/Power */
    {6, (char*) "Energy/Power", (char*) "watts to horsepower", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.13410220895950279e-02*pop(rpnstack)));", (char*) "( ?w * 0.13410220895950279e-02 /*w:hp*/ )"},
    {6, (char*) "", (char*) "", (char*) "", (char*) ""},
    {6, (char*) "Energy/Power", (char*) "horsepower to watts", (char*) "if(size(rpnstack)>=1) push(rpnstack, (745.69987158227022*pop(rpnstack)));", (char*) "( ?hp * 745.69987158227022 /*hp:w*/ )"},
    /* Energy/Power */

    /* Angle */
    {7, (char*) "Angle", (char*) "arcsec to degrees", (char*) "if(size(rpnstack)>=1) push(rpnstack, (2.777777777777778e-04*pop(rpnstack)));", (char*) "( ?arcs * 2.777777777777778e-04 /*arcs:deg*/ )"},
    {7, (char*) "Angle", (char*) "arcmin to degrees", (char*) "if(size(rpnstack)>=1) push(rpnstack, (1.666666666666667e-02*pop(rpnstack)));", (char*) "( ?arcmin * 1.666666666666667e-02 /*arcmin:deg*/ )"},
    {7, (char*) "Angle", (char*) "grads to degrees", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.9*pop(rpnstack)));", (char*) "( ?grad * 0.9 /*grad:deg*/ )"},
    {7, (char*) "", (char*) "", (char*) "", (char*) ""},
    {7, (char*) "Angle", (char*) "degrees to arcsec", (char*) "if(size(rpnstack)>=1) push(rpnstack, (3600*pop(rpnstack)));", (char*) "( ?deg * 3600 /*deg:arcs*/ )"},
    {7, (char*) "Angle", (char*) "degrees to arcmin", (char*) "if(size(rpnstack)>=1) push(rpnstack, (360*pop(rpnstack)));", (char*) "( ?deg * 60 /*deg:arcmin*/ )"},
    {7, (char*) "Angle", (char*) "degrees to grads", (char*) "if(size(rpnstack)>=1) push(rpnstack, (1.111111111111111*pop(rpnstack)));", (char*) "( ?deg * 1.111111111111111 /*deg:grad*/ )"},
    /* Angle */

    /* Time/Speed */
    {8, (char*) "Time/Speed", (char*) "seconds to years", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.317097919837645865e-07*pop(rpnstack)));", (char*) "( ?s * 0.317097919837645865e-0 /*s:yr*/ )"},
    {8, (char*) "Time/Speed", (char*) "years to seconds", (char*) "if(size(rpnstack)>=1) push(rpnstack, (31536000*pop(rpnstack)));", (char*) "( ?yr * 31536000 /*yr:s*/ )"},
    {8, (char*) "", (char*) "", (char*) "", (char*) ""},
    {8, (char*) "Time/Speed", (char*) "miles/hour to knots", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.86897624*pop(rpnstack)));", (char*) "( ?mph * 0.86897624 /*mph:kt*/ )"},
    {8, (char*) "Time/Speed", (char*) "miles/hour to meters/sec", (char*) "if(size(rpnstack)>=1) push(rpnstack, (0.44704*pop(rpnstack)));", (char*) "( ?mph * 0.44704 /*mph:mps*/ )"},
    {8, (char*) "Time/Speed", (char*) "meters/sec to miles/hour", (char*) "if(size(rpnstack)>=1) push(rpnstack, (2.236936*pop(rpnstack)));", (char*) "( ?mps * 2.236936 /*mps:mph*/ )"},
    {8, (char*) "Time/Speed", (char*) "knots to miles/hour", (char*) "if(size(rpnstack)>=1) push(rpnstack, (1.1507794*pop(rpnstack)));", (char*) "( ?kt * 1.1507794 /*kt:mph*/ )"},
    /* Time/Speed */

    /* Temperature, all exact */
    {9, (char*) "Temperature", (char*) "degrees C to degrees F", (char*) "if(size(rpnstack)>=1) push(rpnstack, (((9/5)*pop(rpnstack))+32));", (char*) "(32 + ((9/5) * ?degC /*C:F*/ ))"},
    {9, (char*) "", (char*) "", (char*) "", (char*) ""},
    {9, (char*) "Temperature", (char*) "degrees F to degrees C", (char*) "if(size(rpnstack)>=1) push(rpnstack, ((5/9)*(pop(rpnstack)-32)));", (char*) "((5/9) * (-32 + ?degF /*F:C*/ ))"},
    /* Temperature, all exact */

    /* must be last conversion */ {-1, (char*) "", (char*) "", (char*) "", (char*) ""} /* must be last conversion */
};
