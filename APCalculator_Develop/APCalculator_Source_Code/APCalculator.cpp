#include <QtGui>
#include <QApplication>

// OS-X:
// $ cd ~/Documents/CalculatorDevelop/build-APCalculator-Desktop_Qt_5_6_1_clang_64bit-Release
// $ /Developer/5.6/clang_64/bin/macdeployqt APCalculator.app -dmg

/*-------Application Sizing------*/
int APCalculator_FontSize;
int Button_FontSize;

int APCalculator_WindowHeight;
int APCalculator_WindowWidth;
int ValueStack_StackColumnWidth;
int ValueStack_MemoryColumnWidth;
int ValueStack_Height;
int ValueStack_RowHeight;
int APCalculator_ButtonHeight;

int RPN_GroupBox_MinHeight;
    /* RPN_GroupBox->setMinimumHeight(218); */
    /* RPN_GroupBox->setMinimumHeight(ValueStack_Height + 28); */

int Algebraic_GroupBox_MinHeight;
int Program_GroupBox_MinHeight;

int Solver_Name_ColumnWidth;
int Solver_Solve_ColumnWidth;
int Solver_Value_ColumnWidth;
/*-------Application Sizing------*/

#include "Calculator_UI.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    application.setApplicationName(APP_NAME);
    application.setApplicationVersion(APP_VERSION);

    QDesktopWidget* desktop = QApplication::desktop();

    int dpi = desktop->physicalDpiX();
    /* qDebug() << dpi; */
    if ((dpi < 100) && (0 == 1)) {
        APCalculator_FontSize = 9;

#ifdef Q_OS_MAC
        APCalculator_WindowHeight = 398;
        APCalculator_WindowWidth = 324;
#else
        APCalculator_WindowHeight = 398;
        APCalculator_WindowWidth = 324;

        ValueStack_StackColumnWidth = 300;
#endif
        /* Alpha row headers are wider than numeric row headers */
        ValueStack_MemoryColumnWidth = ValueStack_StackColumnWidth - 2;
#ifdef Q_OS_MAC
        ValueStack_Height = 194;
#else
        ValueStack_Height = 194;
#endif
        ValueStack_RowHeight = 19;
        APCalculator_ButtonHeight = 22;

        RPN_GroupBox_MinHeight = 218;

        Algebraic_GroupBox_MinHeight = 220;
        Program_GroupBox_MinHeight = 240;

        Solver_Name_ColumnWidth = 150;
        Solver_Solve_ColumnWidth = 20;
        Solver_Value_ColumnWidth = 150;
    }
    else {
#ifdef Q_OS_MAC
        APCalculator_FontSize = 15 /* 10 */ ;
        Button_FontSize = 13;
#else
        APCalculator_FontSize = 10 /* 10 */ ;
        Button_FontSize = 12;
#endif


#ifdef Q_OS_MAC
        APCalculator_WindowHeight = 452 /* 454 */ ;
        APCalculator_WindowWidth = 416 /* 400 */ ;

        ValueStack_StackColumnWidth = 396 /* 374 */ ;
#else
        APCalculator_WindowHeight = 458 /* 454 */ ;
        APCalculator_WindowWidth = 418 /* 400 */ ;

        ValueStack_StackColumnWidth = 392 /* 374 */ ;
#endif
        /* Alpha row headers are wider than numeric row headers */
        ValueStack_MemoryColumnWidth = ValueStack_StackColumnWidth - 0 /* 2 */ ;
#ifdef Q_OS_MAC
        ValueStack_Height = 232 /* 214 */ ;
        ValueStack_RowHeight = 23 /* 21 */ ;
#else
        ValueStack_Height = 214 /* 214 */ ;
        ValueStack_RowHeight = 21 /* 21 */ ;
#endif
        APCalculator_ButtonHeight = 26;

        RPN_GroupBox_MinHeight = ValueStack_Height + 28;

        Algebraic_GroupBox_MinHeight = 264;
        Program_GroupBox_MinHeight = 288;

        Solver_Name_ColumnWidth = 196;
        Solver_Solve_ColumnWidth = 22;
        Solver_Value_ColumnWidth = 196;
    }

    QFont fnt = application.font();
#ifdef Q_OS_MAC
    fnt.setBold(true);
#endif
    fnt.setPointSizeF(APCalculator_FontSize);
    application.setFont(fnt);

    APCalcClass apcalc;
    apcalc.show();
    apcalc.APCalcClass_PostInitialize(application.applicationDirPath(), application.arguments());

    int return_code = application.exec();

    apcalc.APCalcClass_PreTerminate();
    apcalc.deleteLater();

    return return_code;
}
