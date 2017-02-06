#ifndef APCalcClass_H
#define APCalcClass_H

#include <QApplication>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QToolButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QBrush>
#include <QColor>
#include <QFont>

QT_BEGIN_NAMESPACE
class QMenuBar;
class QMenu;
class QTableWidget;
class QTableWidgetItem;
class QLineEdit;
class QPlainTextEdit;
class QTextCursor;
class QToolButton;
class QGridLayout;
class QGroupBox;
class QBrush;
class QColor;
class QFont;
QT_END_NAMESPACE

#include "LineEdit.h"
#include "PlainTextEdit.h"

/*-------Application Sizing------*/
extern int APCalculator_FontSize;
extern int Button_FontSize;

extern int APCalculator_WindowHeight;
extern int APCalculator_WindowWidth;
extern int ValueStack_StackColumnWidth;
extern int ValueStack_MemoryColumnWidth;
extern int ValueStack_Height;
extern int ValueStack_RowHeight;
extern int APCalculator_ButtonHeight;

extern int RPN_GroupBox_MinHeight;

extern int Algebraic_GroupBox_MinHeight;
extern int Program_GroupBox_MinHeight;

extern int Solver_Name_ColumnWidth;
extern int Solver_Solve_ColumnWidth;
extern int Solver_Value_ColumnWidth;
/*-------Application Sizing------*/

class APCalcClass : public QWidget
{
    Q_OBJECT

public:
    APCalcClass ( );
    ~APCalcClass ( );

    void APCalcClass_PostInitialize(QString Application_Path, QStringList Application_Arguments);
    void APCalcClass_PreTerminate();

private:
#define PeriodRadix_ValidValue "(0[bB][01]+)" "|" "(0[xX][0-9a-fA-F]+)" "|" "(0[.]?)" "|" \
                               "(((-?[1-9,][0-9,]*([.][0-9]*)?)|(-?0?[.][0-9]+))([eE][+-]?[0-9]+)?[iI]?)"
#define CommaRadix_ValidValue "(0[bB][01]+)" "|" "(0[xX][0-9a-fA-F]+)" "|" "(0[,]?)" "|" \
                               "(((-?[1-9.][0-9.]*([,][0-9]*)?)|(-?0?[,][0-9]+))([eE][+-]?[0-9]+)?[iI]?)"

#include "Modes.h"

    void InitializeCalc(void);
    void ProgramCalc(char* ProgramText);
    void TerminateCalc(void);

    void CalcPrecision(int Precision);

    void ProgramAPCalculator(QString Program_String);
    void ReportErrors(int userMark);

/* Menus */
private slots:
/*-------File----------*/
    void File_OpenIni();
    void File_SaveIniAs();

    void File_ImportDefines();
    void File_ExportDefines();
    void File_ClearDefines();

    void File_ImportHistory();
    void File_ExportHistory();
    void File_ClearHistory();

    void File_Exit();
/*-------Mode----------*/
    void Mode_Algebraic();
    void Mode_AlgebraicInteractive();
    void Mode_Program();
    void Mode_RPN();

    void Mode_PeriodRadixMark();
    void Mode_CommaRadixMark();
    void Mode_StandardDigitGroup();
    void Mode_SpaceDigitGroup();

    void Mode_Degrees();
    void Mode_Radians();

    void Mode_DisplayDecimal();
    void Mode_DisplayScientific();
    void Mode_DisplayHexadecimal();
    void Mode_DisplayBinary();
    void Mode_DisplayDecimalHexadecimal();
    void Mode_DisplayDecimalBinary();

    void Mode_RecallEval();
    void Mode_RecallEvalValue();
/*-------Solve---------*/
    void Solve_ShowSolve();
    void Solve_Import();
    void SolveClick();
/*-------Equation------*/
    void EquationClick();
/*-------Unit----------*/
//    void UnitClick();
    void UnitPlusClick();
    void UnitPlusConvertClick();
/*-------Constant------*/
    void ConstantClick();

private:
    void createActions();
    void createMenus ( QMenuBar* menuBar );

    QMenuBar* APCalc_MenuBar;

    QMenu *File_Menu;
    QAction *file_OpenIni_Action;
    QAction *file_SaveIniAs_Action;
    QAction *file_ImportDefines_Action;
    QAction *file_ExportDefines_Action;
    QAction *file_ClearDefines_Action;
    QAction *file_ImportHistory_Action;
    QAction *file_ExportHistory_Action;
    QAction *file_ClearHistory_Action;
    QAction *file_Exit_Action;

    QMenu *Mode_Menu;
    QAction *mode_Algebraic_Action;
    QAction *mode_AlgebraicInteractive_Action;
    QAction *mode_Program_Action;
    QAction *mode_RPN_Action;

    QAction *mode_PeriodRadixMark_Action;
    QAction *mode_CommaRadixMark_Action;

    QAction *mode_StandardDigitGroup_Action;
    QAction *mode_SpaceDigitGroup_Action;

    QAction *mode_Degrees_Action;
    QAction *mode_Radians_Action;

    QAction *mode_DisplayDecimal_Action;
    QAction *mode_DisplayScientific_Action;
    QAction *mode_DisplayHexadecimal_Action;
    QAction *mode_DisplayBinary_Action;
    QAction *mode_DisplayDecimalHexadecimal_Action;
    QAction *mode_DisplayDecimalBinary_Action;

    QAction *mode_RecallEval_Action;
    QAction *mode_RecallEvalValue_Action;

    QMenu *Solve_Menu;
    QAction *solve_Import_Action;
    void Create_SolveMenu(QMenu* SolveMenu);
    QAction *solve_ShowSolve_Action;

    QMenu *Equation_Menu;
    void Create_EquationMenu(QMenu* EquationMenu);

//    QMenu *Unit_Menu;
//    void Create_UnitMenu(QMenu* UnitMenu);

    QMenu *UnitPlus_Menu;
    QAction *UnitName;
    void Create_UnitPlusMenu(QMenu* UnitMenu);
    QString Unit_ConvertToSI;
    QString Unit_Conversion_Program;
    QList<QMenu*> To_Unit_Menu_List;

    QMenu *Constant_Menu;
    void Create_ConstantMenu(QMenu* ConstantMenu);

    void Set_DefaultDirectory(QString New_DefaultDirectory);

/* Modes */
private:
    void ImportInitializationFile(QString Initialization_FileName);
    void ExportInitializationFile(QString Initialization_FileName);

    void RPN_Mode_UI();
    void Algebraic_Mode_UI();
    void Program_Mode_UI();
    void Solver_Mode_UI();

    void Set_ValueEntry_Validator(char* ValueEntry_Validator);

    APCalc_Calculator_Mode Calculator_Mode;
    int Buttons_Index;

    APCalc_Angle_Mode Angle_Mode;

    APCalc_RadixMark_Mode RadixMark_Mode;
    char* Radix_Mark;
    QChar Standard_Digit_Separator; // ['.', ','] This will be whichever is not Radix Mark
    QChar Digit_Separator;
    QChar Narrow_Space;

    APCalc_Recall_Mode Recall_Mode;

    int Suppress_DigitGrouping;

/* RPN, Algebraic */
private slots:
    void ValueStack_CellClicked(int Row, int Column);

private:
#define ValueStack_RowCount 10
#define ValueStack_StackColumn 0
#define ValueStack_MemoryColumn 1

    QGroupBox *RPN_GroupBox;

    QTableWidget *ValueStack_TableWidget;
    QString ValueStack_CellText(int Row, int Column);
    void ValueStack_setCellText(int Row, int Column, QString Text);
    void ValueStack_ColumnVisible(int Column);

    LineEdit *ValueEntry_LineEdit;

private slots:
    void RPN_keyPressed(int Key);
    void RPN_ValueEntry_returnPressed();
    void RPN_ValueEntry_textChanged(QString newText);

private:
    QGroupBox *Algebraic_GroupBox;

    PlainTextEdit *Algebraic_PlainTextEdit;
    QPlainTextEdit *Algebraic_Value_PlainTextEdit;
    LineEdit *Algebraic_ValueEntry_LineEdit;

    void Algebraic_AdHocEvaluate();

private slots:
    void Algebraic_focusIn();
    void Algebraic_focusOut();

    void Algebraic_textChanged();

    void Algebraic_moveCursorLeft();
    void Algebraic_moveCursorRight();

    void Algebraic_keyPressed(int Key);

    void Algebraic_ValueEntry_returnPressed();
    void Algebraic_ValueEntry_textChanged(QString newText);

private:
    QGroupBox *Program_GroupBox;

    PlainTextEdit *Program_PlainTextEdit;
    QPlainTextEdit *Program_Value_PlainTextEdit;

    void Program_AdHocEvaluate();

private slots:
    void Program_keyPressed(int Key);

/* Buttons */
public slots:
    void Clicked_Button();

public:
    enum APCalc_ButtonType
           {btntypNone,
            btntypChar,
            btntypRadixMark,
            btntypDelete,
            btntypPush,
            btntypPop,
            btntypSwap,
            btntypUndo,
            btntypRedo,
            btntypBase,

           // btntypInvSign

            btntypProgram,
            btntypFunction,
            btntypProgramImmediate,

            btntypAdd,
            btntypSubtract,
            btntypMultiply,
            btntypDivide,
            btntypChangeSign,

            btntypShift,
            btntypSTO,
            btntypRCL,
            btntypClear,
            btntypEval,

            btntypPrevEval,
            btntypNextEval,
            btntypAns,

            btntypOperator,
            btntypParens,
            btntypCursorLeft,
            btntypCursorRight,
            btntypFocusParagraph,
            btntypFocusLine,
            btntypEnter,
            btntypTrigShift,
            btntypMathShift};

    enum APCalc_ParameterAction {NoParameter, FindParameter};

    struct ButtonDefinition {
        int Row;
        int Column;
        APCalc_ButtonType ButtonType;
        QString Text;
        char* ToolTip;
        char* Program;
        APCalc_ParameterAction ParameterAction;
    };

#define ButtonRows 7
#define ButtonColumns 7

#define RPN_ButtonSets 2
#define RPN_ButtonRows 7
#define RPN_ButtonColumns 7

#define Algebraic_ButtonSets 3
#define Algebraic_ButtonRows 7
#define Algebraic_ButtonColumns 7

#define Program_ButtonSets 3
#define Program_ButtonRows 6
#define Program_ButtonColumns 6

private:
    void CreateButtons();
    QToolButton* createToolButton(const int Row, const int Column);

    QGroupBox *Buttons_GroupBox;

    QGridLayout *RPNButtons_GridLayout();
    QGridLayout *AlgebraicButtons_GridLayout();
    QGridLayout *ProgramButtons_GridLayout();

    void CalculatorButtons_SetText(APCalc_Calculator_Mode Mode, int Buttons_Index);

    void Button_SetText(int Row, int Column, int Type, QString Text, char* ToolTip);
    void Button_Execute(APCalc_Calculator_Mode Mode, int Buttons_Index, int Row, int Column);

    QString Normalize_ValueEntry(QString ValueEntry);
    void ValueStack_PushValue(char* ValueToPush);
    void RPNButton_Execute(ButtonDefinition *Execute_Button);
    void ProcessRPN(char* RPNCommands, bool SaveHistoryEnabled);
    void RPN_DisplayStackMemory(char* StackMemory_History);
    void RPN_RestoreState(char* Command_String, char* Restore_Stack_Memory);

    void RPN_AdHocExecute(APCalc_ButtonType Execute_ButtonType);

    void LineEdit_textChanged(QLineEdit *LineEdit, QString newText);

    QString DisplayValue(char* cp_Value);

    QString DigitGroup(QString RawDigits);
    QString DigitGroup_Decimal(QString RawDigits);
    QString DigitGroup_BinHex(QString RawDigits);
    QString RemoveDigitGrouping(QString GroupedDigits);
    bool IsDigitGroupingCharacter(QChar Test_Character);

    void Algebraic_ButtonExecute(ButtonDefinition *Execute_Button);
    void Algebraic_FindQuestionMark();
    void Algebraic_Evaluate(bool AlgebraicInteractive);

    void Algebraic_AdHocExecute(APCalc_ButtonType Execute_ButtonType);

    enum FocusOwner {FocusLine, FocusParagraph};
    FocusOwner Algebraic_FocusOwner;
    void Algebraic_SetFocus();
    void Algebraic_InsertText(QString InsertText);

    void Program_ButtonExecute(ButtonDefinition *Execute_Button);
    void Program_FindQuestionMark();
    void Program_Evaluate();

    void Program_AdHocExecute(APCalc_ButtonType Execute_ButtonType);

    QString Program_Defines;

/* Solve */
private:
#define SolverData_RowCount 16
#define SolverData_RowHeight 18
/* #define SolverData_RowHeight 18 */

#define Solver_Name_Column 0
#define Solver_Solve_Column 1
#define Solver_Value_Column 2

private slots:
    void SolverData_CellClicked(int Row, int Column);
    void Solver_ValueEntry_returnPressed();
    void Solver_ValueEntry_textChanged(QString newText);
    void Solver_ValueEntry_keyPressed(int Key);

private:
    QPlainTextEdit *Solver_PlainTextEdit;

    QTableWidget *SolverData_TableWidget;
    QLineEdit *Solver_ValueEntry_LineEdit;

    void SolverData_BeginEdit(int Row);
    void SolverData_EndEdit(bool Save_Edits);

    bool Solve_Comment_Contains(int Row, QString Contains);
    void Solver_DisplayDataValues();
    void SolverData_setCellText(int Row, int Column, QString Text);
    char* SolverData_CellText(int Row, int Column, char* CellText);

    char* LoadSolver(char* SolverText);
    char* GetSolverProgram(int SolveForRow);
    char* InitializeSolver(char* SolverText);

private:
    QBrush *Cyan_Brush;
    QBrush *Yellow_Brush;

/* History */
    int History_Index;
};

#endif
