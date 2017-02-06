struct ConstantDefinition {
    int Index;
    char* Category;
    char* ConstantName;
    char* ConstantValue;
    char* ConstantUnits;
};

ConstantDefinition Constants[] =
{
    {1, (char*) "Physics", (char*) "Speed of Light", (char*) "299792458", (char*) "m/s"},
    {1, (char*) "Physics", (char*) "Gravitational Constant", (char*) "6.67428e-11", (char*) "m^3/(kg * s^2)"},
    {1, (char*) "Physics", (char*) "Acceleration of Gravity (m/s^2)", (char*) "9.80665", (char*) "m/s^2"},
    {1, (char*) "Physics", (char*) "Acceleration of Gravity (ft/s^2)", (char*) "32.17398", (char*) "ft/s^2"},
    {1, (char*) "", (char*) "", (char*) "", (char*) ""},
    {1, (char*) "Physics", (char*) "Charge of Electron", (char*) "1.602176487e-19", (char*) "C"},
    {1, (char*) "Physics", (char*) "Mass of Electron", (char*) "9.10938215e-31", (char*) "kg"},
    {1, (char*) "Physics", (char*) "Mass of Proton", (char*) "1.672621637e-27", (char*) "kg"},
    {1, (char*) "Physics", (char*) "Mass of Neutron", (char*) "1.674927211e-27", (char*) "kg"},
    {1, (char*) "", (char*) "", (char*) "", (char*) ""},
    {1, (char*) "Physics", (char*) "Avogadro Constant", (char*) "6.02214179e23", (char*) "mol^-1"},
    {1, (char*) "Physics", (char*) "Planck Constant", (char*) "6.62606896e-34", (char*) "J-s"},
    
    {2, (char*) "Geography", (char*) "Radius of Earth (equat, km)", (char*) "6378.388", (char*) "km"},
    {2, (char*) "Geography", (char*) "Radius of Earth (polar, km)", (char*) "6356.912", (char*) "km"},
    {2, (char*) "", (char*) "", (char*) "", (char*) ""},
    {2, (char*) "Geography", (char*) "Radius of Earth (equat, mi)", (char*) "3963.34", (char*) "mi"},
    {2, (char*) "Geography", (char*) "Radius of Earth (polar, mi)", (char*) "3949.99", (char*) "mi"},

    {9, (char*) "Orders of Magnitude", (char*) "yotta", (char*) "(10^24)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "zetta", (char*) "(10^21)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "exa", (char*) "(10^18)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "peta", (char*) "(10^15)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "tera", (char*) "(10^12)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "giga", (char*) "(10^9)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "mega", (char*) "(10^6)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "kilo", (char*) "(10^3)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "hecto", (char*) "(10^2)", (char*) ""},
    {9, (char*) "", (char*) "", (char*) "", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "centi", (char*) "(10^-2)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "milli", (char*) "(10^-3)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "micro", (char*) "(10^-6)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "nano", (char*) "(10^-9)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "pico", (char*) "(10^-12)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "femto", (char*) "(10^-15)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "atto", (char*) "(10^-18)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "zepto", (char*) "(10^-21)", (char*) ""},
    {9, (char*) "Orders of Magnitude", (char*) "yocto", (char*) "(10^-24)", (char*) ""},

    {19, (char*) "Data Magnitude", (char*) "kibi", (char*) "(1024)", (char*) ""},
    {19, (char*) "Data Magnitude", (char*) "mebi", (char*) "(1024^2)", (char*) ""},
    {19, (char*) "Data Magnitude", (char*) "gibi", (char*) "(1024^3)", (char*) ""},
    {19, (char*) "Data Magnitude", (char*) "tebi", (char*) "(1024^4)", (char*) ""},
    {19, (char*) "Data Magnitude", (char*) "pebi", (char*) "(1024^5)", (char*) ""},
    {19, (char*) "Data Magnitude", (char*) "exbi", (char*) "(1024^6)", (char*) ""},
    {19, (char*) "Data Magnitude", (char*) "zebi", (char*) "(1024^7)", (char*) ""},
    {19, (char*) "Data Magnitude", (char*) "yobi", (char*) "(1024^8)", (char*) ""},

    /* must be last conversion */ {-1, (char*) "", (char*) "", (char*) "", (char*) ""} /* must be last conversion */
};

