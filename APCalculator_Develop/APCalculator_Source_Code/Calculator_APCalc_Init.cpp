#include "Calculator_UI.h"
#include "APCalc_Init.h"

extern "C" {
#include "libAPCalc.h"
}

void
APCalcClass::InitializeCalc(void) {

    libcalc_call_me_first();

    user_init();

    reinitialize();

    int userMark = user_mark();

    ProgramCalc(APCalc_Config);

    ProgramCalc(APCalc_SolverFunction);

    ProgramCalc(APCalc_UtilityFunctions);

    ProgramCalc(APCalc_DateFunctions);

    ProgramCalc((char*) "base(10);base2(0);");

    ProgramCalc(APCalc_DegreeAwareTrig);

    ReportErrors(userMark);
}

void
APCalcClass::CalcPrecision(int Precision) {
    QString pgm_precis = APCalc_Precis;
    pgm_precis.replace("@", QString::number(Precision, 10));
    ProgramAPCalculator(pgm_precis);
}

void
APCalcClass::ProgramCalc(char* ProgramText) {
    int err;

    (void) openstring(ProgramText, strlen(ProgramText));
    err = execute_commands(true);
    closeinput();
}

void
APCalcClass::TerminateCalc(void) {
    user_term();
    libcalc_call_me_last();
}

void
APCalcClass::ProgramAPCalculator(QString Program_String) {
    int userMark = user_mark();

    ProgramCalc(Program_String.toLatin1().data());

    ReportErrors(userMark);
}

void
APCalcClass::ReportErrors(int userMark) {
    // Report any errors...
    // ...switch to Algebraic mode to view.
    if (user_count(std_err, userMark) > 0) {
        char* str = user_return(std_err, userMark, (char*) "", (char*) "\t", (char*) "\r\n");
        char cmdstr[MAXCMD+1+1+1];
        strcat(cmdstr, (char*) "\r\n");
        strcat(cmdstr, str);
        Algebraic_Value_PlainTextEdit->setPlainText(cmdstr);
        free(str);
    }
}
