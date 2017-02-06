#include <QtGui>

#include "Calculator_UI.h"
#include "Solves.h"
#include "Equations.h"
#include "Units.h"
#include "Constants.h"

extern "C" {
#include "History.h"
}

void APCalcClass::createActions() {
    file_OpenIni_Action = new QAction(tr("Open INI..."), this);
    file_OpenIni_Action->setStatusTip(tr("Open an initialization file"));
    connect(file_OpenIni_Action, SIGNAL(triggered()), this, SLOT(File_OpenIni()));

    file_SaveIniAs_Action = new QAction(tr("Save INI As..."), this);
    file_SaveIniAs_Action->setStatusTip(tr("Save an initialization file"));
    connect(file_SaveIniAs_Action, SIGNAL(triggered()), this, SLOT(File_SaveIniAs()));

    file_ImportDefines_Action = new QAction(tr("Import Defines..."), this);
    connect(file_ImportDefines_Action, SIGNAL(triggered()), this, SLOT(File_ImportDefines()));

    file_ExportDefines_Action = new QAction(tr("Export Defines..."), this);
    connect(file_ExportDefines_Action, SIGNAL(triggered()), this, SLOT(File_ExportDefines()));

    file_ClearDefines_Action = new QAction(tr("Clear Defines"), this);
    connect(file_ClearDefines_Action, SIGNAL(triggered()), this, SLOT(File_ClearDefines()));

    file_ImportHistory_Action = new QAction(tr("Import History..."), this);
    connect(file_ImportHistory_Action, SIGNAL(triggered()), this, SLOT(File_ImportHistory()));

    file_ExportHistory_Action = new QAction(tr("Export History..."), this);
    connect(file_ExportHistory_Action, SIGNAL(triggered()), this, SLOT(File_ExportHistory()));

    file_ClearHistory_Action = new QAction(tr("Clear History"), this);
    connect(file_ClearHistory_Action, SIGNAL(triggered()), this, SLOT(File_ClearHistory()));

    file_Exit_Action = new QAction(tr("Exit"), this);
    connect(file_Exit_Action, SIGNAL(triggered()), this, SLOT(File_Exit()));

    mode_Algebraic_Action = new QAction(tr("Algebraic"), this);
    mode_Algebraic_Action->setCheckable(true);
    connect(mode_Algebraic_Action, SIGNAL(triggered()), this, SLOT(Mode_Algebraic()));

    mode_AlgebraicInteractive_Action = new QAction(tr("Algebraic Interactive"), this);
    mode_AlgebraicInteractive_Action->setCheckable(true);
    connect(mode_AlgebraicInteractive_Action, SIGNAL(triggered()), this, SLOT(Mode_AlgebraicInteractive()));

    mode_Program_Action = new QAction(tr("Program"), this);
    mode_Program_Action->setCheckable(true);
    connect(mode_Program_Action, SIGNAL(triggered()), this, SLOT(Mode_Program()));

    mode_RPN_Action = new QAction(tr("RPN"), this);
    mode_RPN_Action->setCheckable(true);
    mode_RPN_Action->setChecked(true);
    connect(mode_RPN_Action, SIGNAL(triggered()), this, SLOT(Mode_RPN()));

    mode_PeriodRadixMark_Action = new QAction(tr("Period Radix Mark"), this);
    mode_PeriodRadixMark_Action->setCheckable(true);
    mode_PeriodRadixMark_Action->setChecked(true);
    connect(mode_PeriodRadixMark_Action, SIGNAL(triggered()), this, SLOT(Mode_PeriodRadixMark()));

    mode_CommaRadixMark_Action = new QAction(tr("Comma Radix Mark"), this);
    mode_CommaRadixMark_Action->setCheckable(true);
    connect(mode_CommaRadixMark_Action, SIGNAL(triggered()), this, SLOT(Mode_CommaRadixMark()));

    mode_StandardDigitGroup_Action = new QAction(tr("Standard Digit Group"), this);
    mode_StandardDigitGroup_Action->setCheckable(true);
    mode_StandardDigitGroup_Action->setChecked(false);
    connect(mode_StandardDigitGroup_Action, SIGNAL(triggered()), this, SLOT(Mode_StandardDigitGroup()));


    mode_SpaceDigitGroup_Action = new QAction(tr("Space Digit Group"), this);
    mode_SpaceDigitGroup_Action->setCheckable(true);
    mode_SpaceDigitGroup_Action->setChecked(true);
    connect(mode_SpaceDigitGroup_Action, SIGNAL(triggered()), this, SLOT(Mode_SpaceDigitGroup()));

    mode_Degrees_Action = new QAction(tr("Degrees"), this);
    mode_Degrees_Action->setCheckable(true);
    mode_Degrees_Action->setChecked(true);
    connect(mode_Degrees_Action, SIGNAL(triggered()), this, SLOT(Mode_Degrees()));

    mode_Radians_Action = new QAction(tr("Radians"), this);
    mode_Radians_Action->setCheckable(true);
    connect(mode_Radians_Action, SIGNAL(triggered()), this, SLOT(Mode_Radians()));

    mode_DisplayDecimal_Action = new QAction(tr("Decimal"), this);
    mode_DisplayDecimal_Action->setCheckable(true);
    mode_DisplayDecimal_Action->setChecked(true);
    connect(mode_DisplayDecimal_Action, SIGNAL(triggered()), this, SLOT(Mode_DisplayDecimal()));

    mode_DisplayScientific_Action = new QAction(tr("Scientific"), this);
    mode_DisplayScientific_Action->setCheckable(true);
    connect(mode_DisplayScientific_Action, SIGNAL(triggered()), this, SLOT(Mode_DisplayScientific()));

    mode_DisplayHexadecimal_Action = new QAction(tr("Hexadecimal"), this);
    mode_DisplayHexadecimal_Action->setCheckable(true);
    connect(mode_DisplayHexadecimal_Action, SIGNAL(triggered()), this, SLOT(Mode_DisplayHexadecimal()));

    mode_DisplayBinary_Action = new QAction(tr("Binary"), this);
    mode_DisplayBinary_Action->setCheckable(true);
    connect(mode_DisplayBinary_Action, SIGNAL(triggered()), this, SLOT(Mode_DisplayBinary()));

    mode_DisplayDecimalHexadecimal_Action = new QAction(tr("Decimal/Hexadecimal"), this);
    mode_DisplayDecimalHexadecimal_Action->setCheckable(true);
    connect(mode_DisplayDecimalHexadecimal_Action, SIGNAL(triggered()), this, SLOT(Mode_DisplayDecimalHexadecimal()));

    mode_DisplayDecimalBinary_Action = new QAction(tr("Decimal/Binary"), this);
    mode_DisplayDecimalBinary_Action->setCheckable(true);
    connect(mode_DisplayDecimalBinary_Action, SIGNAL(triggered()), this, SLOT(Mode_DisplayDecimalBinary()));

    mode_RecallEval_Action = new QAction(tr("Recall Eval"), this);
    mode_RecallEval_Action->setCheckable(true);
    mode_RecallEval_Action->setChecked(true);
    connect(mode_RecallEval_Action, SIGNAL(triggered()), this, SLOT(Mode_RecallEval()));

    mode_RecallEvalValue_Action = new QAction(tr("Recall Eval and Value"), this);
    mode_RecallEvalValue_Action->setCheckable(true);
    connect(mode_RecallEvalValue_Action, SIGNAL(triggered()), this, SLOT(Mode_RecallEvalValue()));

    solve_ShowSolve_Action = new QAction(tr("Show Solve"), this);
    solve_ShowSolve_Action->setEnabled(false);
    connect(solve_ShowSolve_Action, SIGNAL(triggered()), this, SLOT(Solve_ShowSolve()));

    solve_Import_Action = new QAction(tr("Import..."), this);
    connect(solve_Import_Action, SIGNAL(triggered()), this, SLOT(Solve_Import()));
}

void APCalcClass::createMenus ( QMenuBar* menuBar ) {
    // QMenuBar *menuBar = new QMenuBar(this);

    File_Menu = new QMenu("File", this);
    File_Menu->addAction(file_OpenIni_Action);
    File_Menu->addAction(file_SaveIniAs_Action);
    File_Menu->addSeparator();
    File_Menu->addAction(file_ImportDefines_Action);
    File_Menu->addAction(file_ExportDefines_Action);
    File_Menu->addAction(file_ClearDefines_Action);
    File_Menu->addSeparator();
    File_Menu->addAction(file_ImportHistory_Action);
    File_Menu->addAction(file_ExportHistory_Action);
    File_Menu->addAction(file_ClearHistory_Action);
    File_Menu->addSeparator();
    File_Menu->addAction(file_Exit_Action);
    menuBar->addMenu(File_Menu);

    Mode_Menu = new QMenu("Mode", this);
    Mode_Menu->addAction(mode_Algebraic_Action);
    Mode_Menu->addAction(mode_AlgebraicInteractive_Action);
    Mode_Menu->addAction(mode_Program_Action);
    Mode_Menu->addAction(mode_RPN_Action);
    Mode_Menu->addSeparator();
    Mode_Menu->addAction(mode_PeriodRadixMark_Action);
    Mode_Menu->addAction(mode_CommaRadixMark_Action);
    Mode_Menu->addSeparator();
    Mode_Menu->addAction(mode_StandardDigitGroup_Action);
    Mode_Menu->addAction(mode_SpaceDigitGroup_Action);
    Mode_Menu->addSeparator();
    Mode_Menu->addAction(mode_Degrees_Action);
    Mode_Menu->addAction(mode_Radians_Action);
    Mode_Menu->addSeparator();
    Mode_Menu->addAction(mode_DisplayDecimal_Action);
    Mode_Menu->addAction(mode_DisplayScientific_Action);
    Mode_Menu->addAction(mode_DisplayHexadecimal_Action);
    Mode_Menu->addAction(mode_DisplayBinary_Action);
    Mode_Menu->addAction(mode_DisplayDecimalHexadecimal_Action);
    Mode_Menu->addAction(mode_DisplayDecimalBinary_Action);
    Mode_Menu->addSeparator();
    Mode_Menu->addAction(mode_RecallEval_Action);
    Mode_Menu->addAction(mode_RecallEvalValue_Action);
    menuBar->addMenu(Mode_Menu);

    Solve_Menu = new QMenu("Solve", this);
    Solve_Menu->addAction(solve_Import_Action);
    Solve_Menu->addSeparator();
    Create_SolveMenu(Solve_Menu);
    Solve_Menu->addSeparator();
    Solve_Menu->addAction(solve_ShowSolve_Action);
    menuBar->addMenu(Solve_Menu);

    Equation_Menu = new QMenu("Equation", this);
    Create_EquationMenu(Equation_Menu);
    menuBar->addMenu(Equation_Menu);

//    Unit_Menu = new QMenu("Unit", this);
//    Create_UnitMenu(Unit_Menu);
//    menuBar->addMenu(Unit_Menu);

    UnitPlus_Menu = new QMenu("Unit", this);
    Create_UnitPlusMenu(UnitPlus_Menu);
    menuBar->addMenu(UnitPlus_Menu);

    Constant_Menu = new QMenu("Constant", this);
    Create_ConstantMenu(Constant_Menu);
    menuBar->addMenu(Constant_Menu);

    menuBar->setMinimumWidth(this->width());
    menuBar->setMinimumHeight(24);
}

static QString XML_Document = "";

#define CloseTag true

typedef struct {
    QString ElementName;
    bool ElementTagClosed;
} ElementDefinition;

QList<ElementDefinition> ElementStack;

static
void XML_Prolog() {
    XML_Document = "";
    XML_Document.append("<?xml version=\"1.0\"?>\n");
    ElementStack.clear();
}

static
void XML_Element_Tag(QString New_ElementName, bool New_CloseTag = false) {
    ElementDefinition new_element;
    new_element.ElementName = New_ElementName;
    new_element.ElementTagClosed = false;
    ElementStack.append(new_element);
    QString prolog = ElementStack.last().ElementName;
    prolog.prepend("<");
    if (New_CloseTag) {
        prolog.append(">\n");
        ElementStack.last().ElementTagClosed = true;
    }
    XML_Document.append(prolog);
}

static
void XML_Element_Attribute(QString AttributeName, QString AttributeValue) {
    if (ElementStack.count() > 0) {
        if (ElementStack.last().ElementTagClosed == false) {
            QString attribute = " ";
            attribute.append(AttributeName);
            attribute.append("=\"");
            attribute.append(AttributeValue);
            attribute.append("\"");
            XML_Document.append(attribute);
        }
    }
}

//static
//void XML_Element_CloseTag(QString Tag_ElementName) {
//    if (ElementStack.count() > 0) {
//        if (ElementStack.last().ElementName == Tag_ElementName) {
//            ElementStack.last().ElementTagClosed = true;
//            XML_Document.append(">\n");
//        }
//    }
//}

static
QString XML_EscapeData(QString DataToEscape) {
    QString escaped_data = DataToEscape;
    escaped_data.replace("&", "&amp;");
    escaped_data.replace("<", "&lt;");
    escaped_data.replace(">", "&gt;");
    return escaped_data;
}

static
QString XML_Data(QString EscapedData) {
    QString data = EscapedData;
    data.replace("&quot;", "\"");
    data.replace("&apos;", "'");
    data.replace("&gt;", ">");
    data.replace("&lt;", "<");
    data.replace("&amp;", "&");
    return data;
}

static
void XML_Element_Data(QString ElementData) {
    if (ElementStack.count() > 0) {
        if (ElementStack.last().ElementTagClosed == true) {
            XML_Document.append(XML_EscapeData(ElementData));
        }
    }
}

static
void XML_Element_CloseElement(QString Tag_ElementName) {
    if (ElementStack.count() > 0) {
        if (ElementStack.last().ElementName == Tag_ElementName) {
            QString epilog = "";
            if (ElementStack.last().ElementTagClosed == false)
                epilog = "/>\n";
            else {
                epilog = ElementStack.last().ElementName;
                epilog.prepend("</");
                epilog.append(">\n");
            }
            XML_Document.append(epilog);
            ElementStack.removeLast();
        }
    }
}

QString Default_Directory;

void
APCalcClass::Set_DefaultDirectory(QString New_DefaultDirectory) {
    Default_Directory = New_DefaultDirectory;
}

void APCalcClass::File_OpenIni() {
    QString ini_filename =
              QFileDialog::getOpenFileName(this,
                                           tr("Open Initialization File"), Default_Directory,
                                           tr("Initialization Files (*.ini);;All Files (*.*)"));
    if (ini_filename.length() > 0) ImportInitializationFile(ini_filename);
}

void
APCalcClass::ImportInitializationFile(QString Initialization_FileName) {
    if (Initialization_FileName.length() > 0) {
        QFile ini_File(Initialization_FileName);
        if (!ini_File.open(QIODevice::ReadOnly | QIODevice::Text)) return;

        QTextStream ini_TextStream(&ini_File);
        QString ini_String("");
        while (!ini_TextStream.atEnd()) {
            QString ini_Line = ini_TextStream.readLine();
            ini_String.append("\n");
            ini_String.append(ini_Line);

            if (ini_Line.startsWith("<Configure Precision=\"")) {
                int ini_idx = ini_Line.indexOf("<Configure Precision=\"");
                ini_Line.remove(0, strlen("<Configure Precision=\""));
                ini_idx = ini_Line.indexOf("\"");

                QString precis_str = ini_Line.left(ini_idx);
                bool valid_precis;
                int precis_value = precis_str.toInt(&valid_precis, 10);
                if (valid_precis && (precis_value > 0))
                    CalcPrecision(precis_value);
            }
            else if (ini_Line.startsWith("<Mode MenuItem=\"")) {
                int ini_idx = ini_Line.indexOf("<Mode MenuItem=\"");
                ini_Line.remove(0, strlen("<Mode MenuItem=\""));
                ini_idx = ini_Line.indexOf("\"");

                QString mode_str = ini_Line.left(ini_idx);
                mode_str = mode_str.trimmed();
                for (int a = 1; a <= Mode_Menu->actions().count(); a++) {
                    if (mode_str == Mode_Menu->actions().at(a - 1)->text()) {
                        Mode_Menu->actions().at(a - 1)->activate(QAction::Trigger);
                        break;
                    }
                }
            }
            else if (ini_Line.startsWith("<Directory Default=\"")) {
                int ini_idx = ini_Line.indexOf("<Directory Default=\"");
                ini_Line.remove(0, strlen("<Directory Default=\""));
                ini_idx = ini_Line.indexOf("\"");

                QString dir_str = ini_Line.left(ini_idx);
                Default_Directory = dir_str.trimmed();
            }
        }
        int ini_idx = ini_String.indexOf("<Define>");
        if (ini_idx >= 0) {
            ini_String.remove(0, (ini_idx + strlen((char*) "<Define>")));
            ini_idx = ini_String.indexOf("</Define>");
            if (ini_idx >= 0) ini_String.remove(ini_idx, ini_String.length());
            if (ini_String.startsWith("\n")) ini_String.remove(0, 1);
            if (ini_String.endsWith("\n")) ini_String.chop(1);
            ini_String = ini_String.trimmed();
            Program_Defines.append("\n");
            Program_Defines.append(XML_Data(ini_String));
            ProgramAPCalculator(Program_Defines);
        }
    }
}

void APCalcClass::File_SaveIniAs() {
    QString ini_filename =
              QFileDialog::getSaveFileName(this,
                                           tr("Save Initialization To File"), Default_Directory,
                                           tr("Initialization Files (*.ini);;All Files (*.*)"));
    if (ini_filename.length() > 0) ExportInitializationFile(ini_filename);
}

void
APCalcClass::ExportInitializationFile(QString Initialization_FileName) {
    QFile ini_File(Initialization_FileName);
    if (!ini_File.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream ini_TextStream(&ini_File);
    XML_Prolog();
    XML_Element_Tag("APCalculateInitialization", CloseTag);
    XML_Element_Tag("Modes", CloseTag);
    for (int a = 1; a <= Mode_Menu->actions().count(); a++) {
        if (Mode_Menu->actions().at(a - 1)->isChecked()) {
            XML_Element_Tag("Mode");
            // QString mode_str = Mode_Menu->actions().at(a - 1)->text();
            XML_Element_Attribute("MenuItem", Mode_Menu->actions().at(a - 1)->text());
            XML_Element_CloseElement("Mode");
        }
    }
    XML_Element_CloseElement("Modes");

    if (Program_Defines.length() > 0) {
        XML_Element_Tag("Define", CloseTag);
        XML_Element_Data(Program_Defines.trimmed());
        XML_Element_Data("\n");
        XML_Element_CloseElement("Define");
    }

    XML_Element_CloseElement("APCalculateInitialization");
    ini_TextStream << XML_Document;
}

void APCalcClass::File_ImportDefines() {
    QString defines_filename =
              QFileDialog::getOpenFileName(this,
                                           tr("Open Defines File"), Default_Directory,
                                           tr("Defines Files (*.def);;All Files (*.*)"));
    if (defines_filename.length() > 0) {
        QFile defines_File(defines_filename);
        if (!defines_File.open(QIODevice::ReadOnly | QIODevice::Text)) return;

        QTextStream defines_TextStream(&defines_File);
        QString defines_String("");
        while (!defines_TextStream.atEnd()) {
            defines_String.append(defines_TextStream.readLine());
            defines_String.append((char*) "\n");
        }
        ProgramAPCalculator(defines_String);
        Program_Defines.append(defines_String.trimmed());
        Program_Defines.append("\n");
    }
}

void
APCalcClass::File_ExportDefines() {
    QString defines_filename =
            QFileDialog::getSaveFileName(this,
                                         tr("Save Defines To File"), Default_Directory,
                                         tr("Defines Files (*.def);;All Files (*.*)"));
    if (defines_filename.length() > 0) {
        QFile defines_File(defines_filename);
        if (!defines_File.open(QIODevice::WriteOnly | QIODevice::Text)) return;

        QTextStream defines_TextStream(&defines_File);
        defines_TextStream << Program_Defines.trimmed() << "\n";
    }
}

void
APCalcClass::File_ClearDefines() {
    Program_Defines.clear();
}

void
APCalcClass::File_ImportHistory() {
    QString history_filename =
              QFileDialog::getOpenFileName(this,
                                           tr("Open History File"), Default_Directory,
                                           tr("History Files (*.his);;All Files (*.*)"));
    if (history_filename.length() > 0) {
        QFile history_File(history_filename);
        if (!history_File.open(QIODevice::ReadOnly | QIODevice::Text)) return;

        QTextStream history_TextStream(&history_File);
        QString history_String("");
        while (!history_TextStream.atEnd()) {
            history_String.append(history_TextStream.readLine());
            history_String.append((char*) "\r\n");
        }
        import_history(history_String.toLatin1().data());
        History_Index = saved_history_count() + 1;
    }
}

void
APCalcClass::File_ExportHistory() {
    QString history_filename =
              QFileDialog::getSaveFileName(this,
                                           tr("Save History To File"), Default_Directory,
                                           tr("History Files (*.his);;All Files (*.*)"));
    if (history_filename.length() > 0) {
        QFile history_File(history_filename);
        if (!history_File.open(QIODevice::WriteOnly | QIODevice::Text)) return;

        QTextStream history_TextStream(&history_File);
        QString history_String(export_history());
        history_TextStream << history_String;
    }
}

void
APCalcClass::File_ClearHistory() { clear_history(); }

void
APCalcClass::File_Exit() { QCoreApplication::exit(0); }

void
APCalcClass::Mode_Algebraic() {
    // Otherwise value entry in process may be lost
    SolverData_EndEdit(true);

    Calculator_Mode = Algebraic_Mode;
    Buttons_Index = 0;

    Algebraic_Mode_UI();

    // UnitPlus_Menu->setEnabled(false);

    mode_Algebraic_Action->setChecked(true);
    mode_AlgebraicInteractive_Action->setChecked(false);
    mode_Program_Action->setChecked(false);
    mode_RPN_Action->setChecked(false);
}

void
APCalcClass::Mode_AlgebraicInteractive() {
    // Otherwise value entry in process may be lost
    SolverData_EndEdit(true);

    Calculator_Mode = Algebraic_Interactive_Mode;
    Buttons_Index = 0;

    Algebraic_Mode_UI();

    // UnitPlus_Menu->setEnabled(false);

    mode_Algebraic_Action->setChecked(false);
    mode_AlgebraicInteractive_Action->setChecked(true);
    mode_Program_Action->setChecked(false);
    mode_RPN_Action->setChecked(false);
}

void
APCalcClass::Mode_Program() {
    // Otherwise value entry in process may be lost
    SolverData_EndEdit(true);

    Calculator_Mode = Program_Mode;
    Buttons_Index = 0;

    Program_Mode_UI();

    mode_Algebraic_Action->setChecked(false);
    mode_AlgebraicInteractive_Action->setChecked(false);
    mode_Program_Action->setChecked(true);
    mode_RPN_Action->setChecked(false);
}

void
APCalcClass::Mode_RPN() {
    // Otherwise value entry in process may be lost
    SolverData_EndEdit(true);

    Calculator_Mode = RPN_Mode;
    Buttons_Index = 0;

    RPN_Mode_UI();

    // UnitPlus_Menu->setEnabled(true);

    mode_Algebraic_Action->setChecked(false);
    mode_AlgebraicInteractive_Action->setChecked(false);
    mode_Program_Action->setChecked(false);
    mode_RPN_Action->setChecked(true);
}

void APCalcClass::Mode_PeriodRadixMark() {
    // Can't allow radix mark to change in middle of edit
    ValueEntry_LineEdit->clear();
    Algebraic_ValueEntry_LineEdit->clear();
    SolverData_EndEdit(false);

    RadixMark_Mode = RadixMark_Period;
    Radix_Mark = (char*) ".";
    Standard_Digit_Separator = QChar((char) ',');
    Set_ValueEntry_Validator((char*) PeriodRadix_ValidValue);

    if (mode_SpaceDigitGroup_Action->isChecked())
        Digit_Separator = Narrow_Space;
    else
        Digit_Separator = Standard_Digit_Separator;

    if (Calculator_Mode == RPN_Mode) CalculatorButtons_SetText(Calculator_Mode, Buttons_Index);
    RPN_DisplayStackMemory(NULL);
    Solver_DisplayDataValues();

    mode_PeriodRadixMark_Action->setChecked(true);
    mode_CommaRadixMark_Action->setChecked(false);
}

void APCalcClass::Mode_CommaRadixMark() {
    // Can't allow radix mark to change in middle of edit
    ValueEntry_LineEdit->clear();
    SolverData_EndEdit(false);

    RadixMark_Mode = RadixMark_Comma;
    Radix_Mark = (char*) ",";
    Standard_Digit_Separator = QChar((char) '.');
    Set_ValueEntry_Validator((char*) CommaRadix_ValidValue);

    if (mode_SpaceDigitGroup_Action->isChecked())
        Digit_Separator = Narrow_Space;
    else
        Digit_Separator = Standard_Digit_Separator;

    if (Calculator_Mode == RPN_Mode) CalculatorButtons_SetText(Calculator_Mode, Buttons_Index);
    RPN_DisplayStackMemory(NULL);
    Solver_DisplayDataValues();

    mode_PeriodRadixMark_Action->setChecked(false);
    mode_CommaRadixMark_Action->setChecked(true);
}

void APCalcClass::Mode_StandardDigitGroup() {
    Digit_Separator = Standard_Digit_Separator;

    mode_StandardDigitGroup_Action->setChecked(true);
    mode_SpaceDigitGroup_Action->setChecked(false);
}

void APCalcClass::Mode_SpaceDigitGroup() {
    Digit_Separator = Narrow_Space;

    mode_StandardDigitGroup_Action->setChecked(false);
    mode_SpaceDigitGroup_Action->setChecked(true);
}

void APCalcClass::Set_ValueEntry_Validator(char* ValueEntry_Validator) {
    ValueEntry_LineEdit->setValidator(0);
    Algebraic_ValueEntry_LineEdit->setValidator(0);
    Solver_ValueEntry_LineEdit->setValidator(0);
    QRegExp ValueEntry_rx(ValueEntry_Validator);
    ValueEntry_LineEdit->setValidator(new QRegExpValidator(ValueEntry_rx, ValueEntry_LineEdit));
    Algebraic_ValueEntry_LineEdit->setValidator(new QRegExpValidator(ValueEntry_rx, Algebraic_ValueEntry_LineEdit));
    Solver_ValueEntry_LineEdit->setValidator(new QRegExpValidator(ValueEntry_rx, Solver_ValueEntry_LineEdit));
}

void APCalcClass::Mode_Degrees() {
    Angle_Mode = Angle_Degrees;
    ProgramCalc((char*) "fromangle=deg2rad;toangle=rad2deg;");
    mode_Degrees_Action->setChecked(true);
    mode_Radians_Action->setChecked(false);
}

void APCalcClass::Mode_Radians() {
    Angle_Mode = Angle_Radians;
    ProgramCalc((char*) "fromangle=1;toangle=1;");
    mode_Degrees_Action->setChecked(false);
    mode_Radians_Action->setChecked(true);
}

void APCalcClass::Mode_DisplayDecimal() {
    ProgramCalc((char*) "base(10);base2(0);");
    RPN_DisplayStackMemory(NULL);
    mode_DisplayDecimal_Action->setChecked(true);
    mode_DisplayScientific_Action->setChecked(false);
    mode_DisplayHexadecimal_Action->setChecked(false);
    mode_DisplayBinary_Action->setChecked(false);
    mode_DisplayDecimalHexadecimal_Action->setChecked(false);
    mode_DisplayDecimalBinary_Action->setChecked(false);
}

void APCalcClass::Mode_DisplayScientific() {
    ProgramCalc((char*) "base(1e20);base2(0);");
    RPN_DisplayStackMemory(NULL);
    mode_DisplayDecimal_Action->setChecked(false);
    mode_DisplayScientific_Action->setChecked(true);
    mode_DisplayHexadecimal_Action->setChecked(false);
    mode_DisplayBinary_Action->setChecked(false);
    mode_DisplayDecimalHexadecimal_Action->setChecked(false);
    mode_DisplayDecimalBinary_Action->setChecked(false);
}

void APCalcClass::Mode_DisplayHexadecimal() {
    ProgramCalc((char*) "base(16);base2(0);");
    RPN_DisplayStackMemory(NULL);
    mode_DisplayDecimal_Action->setChecked(false);
    mode_DisplayScientific_Action->setChecked(false);
    mode_DisplayHexadecimal_Action->setChecked(true);
    mode_DisplayBinary_Action->setChecked(false);
    mode_DisplayDecimalHexadecimal_Action->setChecked(false);
    mode_DisplayDecimalBinary_Action->setChecked(false);
}

void APCalcClass::Mode_DisplayBinary() {
    ProgramCalc((char*) "base(2);base2(0);");
    RPN_DisplayStackMemory(NULL);
    mode_DisplayDecimal_Action->setChecked(false);
    mode_DisplayScientific_Action->setChecked(false);
    mode_DisplayHexadecimal_Action->setChecked(false);
    mode_DisplayBinary_Action->setChecked(true);
    mode_DisplayDecimalHexadecimal_Action->setChecked(false);
    mode_DisplayDecimalBinary_Action->setChecked(false);
}

void APCalcClass::Mode_DisplayDecimalHexadecimal() {
    ProgramCalc((char*) "base(10);base2(16);");
    RPN_DisplayStackMemory(NULL);
    mode_DisplayDecimal_Action->setChecked(false);
    mode_DisplayScientific_Action->setChecked(false);
    mode_DisplayHexadecimal_Action->setChecked(false);
    mode_DisplayBinary_Action->setChecked(false);
    mode_DisplayDecimalHexadecimal_Action->setChecked(true);
    mode_DisplayDecimalBinary_Action->setChecked(false);
}

void APCalcClass::Mode_DisplayDecimalBinary() {
    ProgramCalc((char*) "base(10);base2(2);");
    RPN_DisplayStackMemory(NULL);
    mode_DisplayDecimal_Action->setChecked(false);
    mode_DisplayScientific_Action->setChecked(false);
    mode_DisplayHexadecimal_Action->setChecked(false);
    mode_DisplayBinary_Action->setChecked(false);
    mode_DisplayDecimalHexadecimal_Action->setChecked(false);
    mode_DisplayDecimalBinary_Action->setChecked(true);
}

void APCalcClass::Mode_RecallEval() {
    Recall_Mode = RecallMode_Eval;
    mode_RecallEval_Action->setChecked(true);
    mode_RecallEvalValue_Action->setChecked(false);
}

void APCalcClass::Mode_RecallEvalValue() {
    Recall_Mode = RecallMode_Eval_Value;
    mode_RecallEval_Action->setChecked(false);
    mode_RecallEvalValue_Action->setChecked(true);
}

void APCalcClass::Solve_Import() {
    QString solve_filename =
              QFileDialog::getOpenFileName(this,
                                           tr("Open Solve File"), Default_Directory,
                                           tr("Solve Files (*.slv);;All Files (*.*)"));
    if (solve_filename.length() > 0) {
        QFile solve_File(solve_filename);
        if (!solve_File.open(QIODevice::ReadOnly | QIODevice::Text)) return;

        QTextStream solve_TextStream(&solve_File);
        QString solve_String("");
        while (!solve_TextStream.atEnd()) {
            solve_String.append(solve_TextStream.readLine());
            solve_String.append((char*) "\r\n");
        }
        solve_ShowSolve_Action->setEnabled(true);
        Solver_Mode_UI();
        char* str = LoadSolver(solve_String.toLatin1().data());
        Solver_PlainTextEdit->setPlainText(str);
    }
}

void APCalcClass::Create_SolveMenu(QMenu* SolveMenu) {
    int s;
    int category_idx = 0;
    QMenu* cat_menu = NULL;
    for (s = 0; (Solves[s].Index >= 0); s++) {
        if (Solves[s].Index != category_idx) {
            category_idx = Solves[s].Index;
            cat_menu = SolveMenu->addMenu(Solves[s].Category);
        }
        if (strlen(Solves[s].Category) == 0)
            cat_menu->addSeparator();
        else {
            QAction* act = new QAction(Solves[s].SolveName, cat_menu);
            act->setData(Solves[s].SolveProgram);
            connect(act, SIGNAL(triggered()), this, SLOT(SolveClick()));
            cat_menu->addAction(act);
        }
    }
}

void APCalcClass::SolveClick() {
    Solver_Mode_UI();
    QAction* act = (QAction*) sender();
    solve_ShowSolve_Action->setEnabled(true);
    char* str = LoadSolver((char*) act->data().toByteArray().data());
    Solver_PlainTextEdit->setPlainText(str);
}

void APCalcClass::Solve_ShowSolve() {
    Solver_Mode_UI();
}

void APCalcClass::Create_EquationMenu(QMenu* EquationMenu) {
    int e;
    int category_idx = 0;
    QMenu* cat_menu = NULL;
    for (e = 0; (Equations[e].Index >= 0); e++) {
        if (Equations[e].Index != category_idx) {
            category_idx = Equations[e].Index;
            cat_menu = EquationMenu->addMenu(Equations[e].Category);
        }
        if (strlen(Equations[e].Category) == 0)
            cat_menu->addSeparator();
        else {
            QAction* act = new QAction(Equations[e].EquationName, cat_menu);
            act->setData(Equations[e].EquationProgram);
            connect(act, SIGNAL(triggered()), this, SLOT(EquationClick()));
            cat_menu->addAction(act);
        }
    }
}

void APCalcClass::EquationClick() {
    QAction* act = (QAction*) sender();
    Algebraic_PlainTextEdit->appendPlainText((char*) act->data().toByteArray().data());
    Algebraic_FindQuestionMark();
}

//#define Unit_FactorIndex 0
//#define Unit_ProgramIndex 1

//void APCalcClass::Create_UnitMenu(QMenu* UnitMenu) {
//    int u;
//    int category_idx = 0;
//    QMenu* cat_menu = NULL;
//    for (u = 0; (UnitsConversions[u].Index >= 0); u++) {
//        if (UnitsConversions[u].Index != category_idx) {
//            category_idx = UnitsConversions[u].Index;
//            cat_menu = UnitMenu->addMenu(UnitsConversions[u].Category);
//        }
//        if (strlen(UnitsConversions[u].Category) == 0)
//            cat_menu->addSeparator();
//        else {
//            QAction* act = new QAction(UnitsConversions[u].Conversion, cat_menu);
//            QStringList u_data;
//            u_data.append(UnitsConversions[u].Factor);
//            u_data.append(UnitsConversions[u].Program);
//            act->setData(u_data);
//            connect(act, SIGNAL(triggered()), this, SLOT(UnitClick()));
//            cat_menu->addAction(act);
//        }
//    }
//}

#define UnitPlus_Index 0
#define UnitPlus_ConvertToSI_Index 1
#define UnitPlus_ConvertFromSI_Index 2

void APCalcClass::Create_UnitPlusMenu(QMenu* UnitMenu) {
    int u;

    // QList<QMenu*> unit_menu_list;

    char* si_unit_factor = (char*) "1";

    QString category_idx = (char*) "";
    QMenu* cat_menu = NULL;
    QMenu* to_cat_menu = NULL;

    UnitName = new QAction("", UnitMenu);
    UnitMenu->addAction(UnitName);
    UnitMenu->addSeparator();

    for (u = 0; (qstrcmp(Units[u].Index, (char*) "") != 0); u++) {
        if (Units[u].Index != category_idx) {
            category_idx = Units[u].Index;
            cat_menu = UnitMenu->addMenu(Units[u].Category);

            to_cat_menu = cat_menu->addMenu((char*) "Convert To");
            to_cat_menu->setEnabled(false);
            to_cat_menu->setProperty((char*) "CategoryIndex", Units[u].Index);
            To_Unit_Menu_List.append(to_cat_menu);
            cat_menu->addSeparator();

            // unit_menu_list.append(cat_menu);
        }
        if (strlen(Units[u].Category) == 0) {
            cat_menu->addSeparator();
            to_cat_menu->addSeparator();
        }
        else {
            QStringList u_data;
            u_data.append(Units[u].Index);
            u_data.append(Units[u].ConvertToSI);
            u_data.append(Units[u].ConvertFromSI);

            QString u_name = Units[u].UnitName;
            if ((qstrcmp(Units[u].ConvertToSI, si_unit_factor) == 0) &&
                (qstrcmp(Units[u].ConvertFromSI, si_unit_factor) == 0)) {
                u_name = u_name + QString::fromUtf8(" \u2022" );
             }

            QAction* act = new QAction(u_name, cat_menu);
            act->setData(u_data);
            connect(act, SIGNAL(triggered()), this, SLOT(UnitPlusClick()));
            cat_menu->addAction(act);

            QAction* to_act = new QAction(u_name, cat_menu);
            to_act->setData(u_data);
            connect(to_act, SIGNAL(triggered()), this, SLOT(UnitPlusConvertClick()));
            to_cat_menu->addAction(to_act);
        }
    }

//    int unit_menu_list_idx = -1;
//    double to_category_idx = 0;

//    for (u = 0; (Units[u].Index >= 0); u++) {
//        if (Units[u].Index != to_category_idx) {
//            to_category_idx = Units[u].Index;
//            /* Submenu for conversions within category */
//            unit_menu_list_idx += 1;
//            unit_menu_list[unit_menu_list_idx]->addSeparator();
//            to_cat_menu =
//                unit_menu_list[unit_menu_list_idx]->addMenu(QString((char*) "To ") +
//                                                            QString(Units[u].Category));
//            to_cat_menu->setEnabled(false);
//            To_Unit_Menu_List.append(to_cat_menu);
//;        }
//        if (strlen(Units[u].Category) == 0)
//            to_cat_menu->addSeparator();
//        else {
//            QAction* act = new QAction(Units[u].UnitName, to_cat_menu);
//            QStringList u_data;
//            u_data.append(Units[u].Category);
//            u_data.append(Units[u].ConvertToSI);
//            u_data.append(Units[u].ConvertFromSI);
//            act->setData(u_data);
//            connect(act, SIGNAL(triggered()), this, SLOT(UnitPlusConvertClick()));
//            to_cat_menu->addAction(act);
//        }
//    }

//    UnitMenu->addSeparator();

//    for (u = 0; (Units[u].Index >= 0); u++) {
//        if (Units[u].Index != to_category_idx) {
//            to_category_idx = Units[u].Index;
//            to_cat_menu = UnitMenu->addMenu(QString((char*) "To ") + QString(Units[u].Category));
//            to_cat_menu->setEnabled(false);
//            To_Unit_Menu_List.append(to_cat_menu);
//;        }
//        if (strlen(Units[u].Category) == 0)
//            to_cat_menu->addSeparator();
//        else {
//            QAction* act = new QAction(Units[u].UnitName, to_cat_menu);
//            QStringList u_data;
//            u_data.append(Units[u].Category);
//            u_data.append(Units[u].ConvertToSI);
//            u_data.append(Units[u].ConvertFromSI);
//            act->setData(u_data);
//            connect(act, SIGNAL(triggered()), this, SLOT(UnitPlusConvertClick()));
//            to_cat_menu->addAction(act);
//        }
//    }
}

/* ButtonDefinition wrapper for unit conversion, some conversions require... */
/* ...more than simple multiplication, temperature conversions, for example */
static struct APCalcClass::ButtonDefinition Unit_Conversion_ButtonDefinition =
  {0, 0, APCalcClass::btntypProgram, (char*)"", (char*)"", (char*)"***", APCalcClass::NoParameter};
static APCalcClass::ButtonDefinition* Unit_Conversion_ButtonDefinition_Pointer =
  (APCalcClass::ButtonDefinition*) &Unit_Conversion_ButtonDefinition;

//void APCalcClass::UnitClick() {
//    QAction* act = (QAction*) sender();
//    QStringList u_data = act->data().toStringList();
//    if (Calculator_Mode == RPN_Mode) {
//        Unit_Conversion_ButtonDefinition_Pointer->Program =
//          (char*) u_data.at(Unit_FactorIndex).toLatin1().data();
//        RPNButton_Execute(Unit_Conversion_ButtonDefinition_Pointer);
//        /*
//        ValueStack_PushValue((char*) u_data.at(Unit_FactorIndex).toLatin1().data());
//        RPN_AdHocExecute(btntypMultiply);
//        */
//    }
//    else if ((Calculator_Mode == Algebraic_Mode) ||
//             (Calculator_Mode == Algebraic_Interactive_Mode)) {
//        Algebraic_PlainTextEdit->insertPlainText((char*) u_data.at(Unit_ProgramIndex).toLatin1().data());
//        Algebraic_FindQuestionMark();
//    }
//}

void APCalcClass::UnitPlusClick() {
    if ((Calculator_Mode == RPN_Mode) ||
        (Calculator_Mode == Algebraic_Mode) ||
        (Calculator_Mode == Algebraic_Interactive_Mode)) {
        QAction* act = (QAction*) sender();

        QStringList u_data = act->data().toStringList();
        QByteArray u_index = u_data.at(UnitPlus_Index).toLatin1().data();
        QString u_name = act->text();

        Unit_ConvertToSI.clear();
        Unit_ConvertToSI.append((char*) u_data.at(UnitPlus_ConvertToSI_Index).toLatin1().data());

        for (int m = 0; (m < To_Unit_Menu_List.count()); m++) {
            QMenu* to_menu = To_Unit_Menu_List.at(m);
            to_menu->setEnabled(to_menu->property((char*) "CategoryIndex").toByteArray() ==
                                u_index);
        }

        UnitName->setText(u_name);
    }
 }

void APCalcClass::UnitPlusConvertClick() {
    QAction* act = (QAction*) sender();
    QStringList u_data = act->data().toStringList();
    QString u_name = act->text();

    if (Calculator_Mode == RPN_Mode) {
        Unit_Conversion_Program.clear();
        if (u_data.at(UnitPlus_Index) == (char*) "Temperature") {
            Unit_Conversion_Program.append(Unit_ConvertToSI);
            Unit_Conversion_Program.append((char*) u_data.at(UnitPlus_ConvertFromSI_Index).toLatin1().data());
        }
        else {
            Unit_Conversion_Program.append((char*) "if(size(rpnstack)>=1) push(rpnstack, (");
            Unit_Conversion_Program.append(Unit_ConvertToSI);
            Unit_Conversion_Program.append((char*) "*");
            Unit_Conversion_Program.append((char*) u_data.at(UnitPlus_ConvertFromSI_Index).toLatin1().data());
            Unit_Conversion_Program.append((char*) "*pop(rpnstack)));");
        }
        Unit_Conversion_ButtonDefinition_Pointer->Program = Unit_Conversion_Program.toLatin1().data();
        RPNButton_Execute(Unit_Conversion_ButtonDefinition_Pointer);
    }
    else if ((Calculator_Mode == Algebraic_Mode) ||
             (Calculator_Mode == Algebraic_Interactive_Mode)) {
        Unit_Conversion_Program.clear();
        Unit_Conversion_Program.append((char*) "*");
        Unit_Conversion_Program.append(Unit_ConvertToSI);
        Unit_Conversion_Program.append((char*) "*");
        Unit_Conversion_Program.append((char*) u_data.at(UnitPlus_ConvertFromSI_Index).toLatin1().data());
        Algebraic_PlainTextEdit->insertPlainText(Unit_Conversion_Program);
    }

    /* Now in new units */
    Unit_ConvertToSI.clear();
    Unit_ConvertToSI.append((char*) u_data.at(UnitPlus_ConvertToSI_Index).toLatin1().data());

    UnitName->setText(u_name);
}

#define Constant_ValueIndex 0
#define Constant_UnitsIndex 1

void APCalcClass::Create_ConstantMenu(QMenu* ConstantMenu) {
    int c;
    int category_idx = 0;
    QMenu* cat_menu = NULL;
    for (c = 0; (Constants[c].Index >= 0); c++) {
        if (Constants[c].Index != category_idx) {
            category_idx = Constants[c].Index;
            cat_menu = ConstantMenu->addMenu(Constants[c].Category);
        }
        if (strlen(Constants[c].Category) == 0)
            cat_menu->addSeparator();
        else {
            QAction* act = new QAction(Constants[c].ConstantName, cat_menu);
            QStringList c_data;
            c_data.append(Constants[c].ConstantValue);
            c_data.append(Constants[c].ConstantUnits);
            act->setData(c_data);
            connect(act, SIGNAL(triggered()), this, SLOT(ConstantClick()));
            cat_menu->addAction(act);
        }
    }
}

void APCalcClass::ConstantClick() {
    QAction* act = (QAction*) sender();
    QStringList c_data = act->data().toStringList();
    if (Calculator_Mode == RPN_Mode)
        ValueStack_PushValue((char*) c_data.at(Constant_ValueIndex).toLatin1().data());
    else if ((Calculator_Mode == Algebraic_Mode) ||
             (Calculator_Mode == Algebraic_Interactive_Mode)) {
        QString c_insert = c_data.at(Constant_UnitsIndex);
        if (c_insert.length() > 0) {
            c_insert.prepend(" /*");
            c_insert.append("*/");
        }
        c_insert.prepend(c_data.at(Constant_ValueIndex));
        Algebraic_PlainTextEdit->insertPlainText((char*) c_insert.toLatin1().data());
    }
}

