typedef struct {
    int Index;
    char* Category;
    char* EquationName;
    char* EquationProgram;
} EquationDefinition;

EquationDefinition Equations[] =
{
    {1, (char*) "Math", (char*) "Normal Probability", (char*) "(1/((2*pi)^0.5))*e^(-0.5*abs(?z)^2)"},
    {1, (char*) "", (char*) "", (char*) ""},

    {2, (char*) "Geometry", (char*) "Circumference of Circle", (char*) "(2*pi * ?Radius)"},
    {2, (char*) "Geometry", (char*) "Area of Circle", (char*) "(pi * (?Radius^2))"},
    {2, (char*) "Geometry", (char*) "Volume of Sphere", (char*) "((4*pi/3) * (?Radius^3))"},

    /* must be last conversion */ {-1, (char*) "", (char*) "", (char*) ""} /* must be last conversion */
};
