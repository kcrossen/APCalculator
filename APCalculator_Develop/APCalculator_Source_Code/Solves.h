#include "Finance.h"
#include "Geometry.h"

struct SolveDefinition {
    int Index;
    char* Category;
    char* SolveName;
    char* SolveProgram;
};

SolveDefinition Solves[] =
{
    {1, (char*)"Finance", (char*)"Time Value of Money", (char*) SolverFinance_TVM},
    {1, (char*)"Finance", (char*)"TVM (Odd Period)", (char*) SolverFinance_TVM_Odd},
    {1, (char*)"", (char*)"", (char*)""},
    //{1, (char*)"Finance", (char*)"Bonds Semiannual <= 6mo", (char*) SolverFinance_Bond_Semiannual_LTE_6mo},
    //{1, (char*)"Finance", (char*)"Bonds Semiannual > 6mo", (char*) SolverFinance_Advance_Payments},
    //{1, (char*)"", (char*)"", (char*)""},
    {1, (char*)"Finance", (char*)"Advance Payments", (char*) SolverFinance_Advance_Payments},
    {1, (char*)"", (char*)"", (char*)""},
    {1, (char*)"Finance", (char*)"Discounted Notes Price", (char*) SolverFinance_Discounted_Notes_Price},
    {1, (char*)"Finance", (char*)"Discounted Notes Yield", (char*) SolverFinance_Discounted_Notes_Yield},
    {1, (char*)"", (char*)"", (char*)""},
    {1, (char*)"Finance", (char*)"Interest Rate Conversion", (char*) SolverFinance_Interest_Rate_Conversion},
    {1, (char*)"Finance", (char*)"Int Rate Conv (Continuous)", (char*) SolverFinance_Interest_Rate_Conversion_Continuous_Compounding},

    {2, (char*)"Dates", (char*)"Elapsed Days", (char*) SolverDates_Elspsed_Days},
    {2, (char*)"Dates", (char*)"Add Days", (char*) SolverDates_Add_Days},

    {3, (char*)"Geometry", (char*)"Sides of Right Triangle", (char*) SolverGeometrySidesofRightTriangle},
    {3, (char*)"Geometry", (char*)"Area of Circle", (char*) SolverGeometryAreaofCircle},
    {3, (char*)"Geometry", (char*)"Volume of Sphere", (char*) SolverGeometryVolumeofSphere},

    /* must be last conversion */ {-1, (char*)"", (char*)"", (char*)""} /* must be last conversion */
};
