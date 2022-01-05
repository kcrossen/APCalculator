#include <QtGui>

#include "Calculator_UI.h"

extern "C" {
#include "libAPCalc.h"
#include "History.h"
}

/* setWindowTitle(tr("AP Calculator 2014-12-22")); */

APCalcClass::APCalcClass ( ) {
    setContentsMargins(0, 0, 0, 0);

    setMinimumSize(APCalculator_WindowWidth, APCalculator_WindowHeight);
    setMaximumSize(APCalculator_WindowWidth, APCalculator_WindowHeight);
    resize(APCalculator_WindowWidth, APCalculator_WindowHeight);
    setWindowTitle(tr("Arbitrary Precision Calculator 2022.01.05"));

    // Windows
    APCalc_MenuBar = new QMenuBar;
    APCalc_MenuBar->setContentsMargins(0, 0, 0, 0);

    createActions();
    createMenus(APCalc_MenuBar);

    Cyan_Brush = new QBrush(QColor::fromRgb(0, 255, 255, 64));
    Yellow_Brush = new QBrush(QColor::fromRgb(255, 255, 0, 64));

    ValueStack_TableWidget = new QTableWidget(ValueStack_RowCount, 2, this);
    ValueStack_TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ValueStack_TableWidget->setColumnWidth(ValueStack_StackColumn, (ValueStack_StackColumnWidth - 2));
    ValueStack_TableWidget->setColumnWidth(ValueStack_MemoryColumn, 0);
    ValueStack_TableWidget->horizontalHeader()->hide();
    ValueStack_TableWidget->setMinimumHeight(ValueStack_Height);
    ValueStack_TableWidget->setMaximumHeight(ValueStack_Height);
    ValueStack_TableWidget->setContentsMargins(0, 0, 0, 0);
    ValueStack_TableWidget->setFocusPolicy(Qt::NoFocus);
    char ch[8];
    ch[1] = (char)0;
    for (int r = 0; r < ValueStack_RowCount; r++) {
        ValueStack_TableWidget->setRowHeight(r, ValueStack_RowHeight);
        ch[0] = (char)((int)'0' + ValueStack_RowCount - r - 1);
        QTableWidgetItem *hdr_itm = new QTableWidgetItem(tr(ch));
        hdr_itm->setFlags(Qt::NoItemFlags);
        ValueStack_TableWidget->setVerticalHeaderItem(r, hdr_itm);
        ValueStack_setCellText((r + 1), ValueStack_StackColumn, (char*) "");
        ValueStack_setCellText((r + 1), ValueStack_MemoryColumn, (char*) "");
    }

    connect(ValueStack_TableWidget, SIGNAL(cellClicked(int,int)),
            this, SLOT(ValueStack_CellClicked(int,int)));

    ValueEntry_LineEdit = new LineEdit(this);
    ValueEntry_LineEdit->setMinimumWidth(APCalculator_WindowWidth - 4);
    ValueEntry_LineEdit->setMaximumWidth(APCalculator_WindowWidth - 4);
    QRegExp ValueEntry_rx(PeriodRadix_ValidValue);
    ValueEntry_LineEdit->setValidator(new QRegExpValidator(ValueEntry_rx, ValueEntry_LineEdit));
    connect(ValueEntry_LineEdit, SIGNAL(returnPressed()),
            this, SLOT(RPN_ValueEntry_returnPressed()));
    connect(ValueEntry_LineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(RPN_ValueEntry_textChanged(QString)));
    connect(ValueEntry_LineEdit, SIGNAL(keyPressed(int)),
            this, SLOT(RPN_keyPressed(int)));
    ValueEntry_LineEdit->setFocus();

    RPN_GroupBox = new QGroupBox(this);
    RPN_GroupBox->setMinimumHeight(RPN_GroupBox_MinHeight);
    RPN_GroupBox->setContentsMargins(1, 0, 0, 0);
    QGridLayout *RPN_GridLayout = new QGridLayout();
    RPN_GridLayout->setContentsMargins(0, 0, 0, 0);
    RPN_GridLayout->setVerticalSpacing(0);
    RPN_GridLayout->addWidget(ValueStack_TableWidget, 0, 0);
    RPN_GridLayout->addWidget(ValueEntry_LineEdit, 1, 0);
    RPN_GroupBox->setLayout(RPN_GridLayout);

    // Algebraic Mode
    Algebraic_Value_PlainTextEdit = new QPlainTextEdit(this);
    Algebraic_Value_PlainTextEdit->setMinimumWidth(APCalculator_WindowWidth - 8);
    Algebraic_Value_PlainTextEdit->setMinimumHeight(64);
    Algebraic_Value_PlainTextEdit->setContentsMargins(0, 0, 0, 0);
    Algebraic_Value_PlainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    Algebraic_Value_PlainTextEdit->setReadOnly(true);

    Algebraic_PlainTextEdit = new PlainTextEdit(this);
    Algebraic_PlainTextEdit->setMinimumWidth(APCalculator_WindowWidth - 8);
    Algebraic_PlainTextEdit->setMinimumHeight(162);
    Algebraic_PlainTextEdit->setContentsMargins(0, 0, 0, 0);
    Algebraic_PlainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    connect(Algebraic_PlainTextEdit, SIGNAL(focusIn()),
            this, SLOT(Algebraic_focusIn()));
    connect(Algebraic_PlainTextEdit, SIGNAL(focusOut()),
            this, SLOT(Algebraic_focusOut()));
    connect(Algebraic_PlainTextEdit, SIGNAL(PlainTextChanged()),
            this, SLOT(Algebraic_textChanged()));
    connect(Algebraic_PlainTextEdit, SIGNAL(keyPressed(int)),
            this, SLOT(Algebraic_keyPressed(int)));

    Algebraic_ValueEntry_LineEdit = new LineEdit(this);
    Algebraic_ValueEntry_LineEdit->setContentsMargins(0, 0, 0, 0);
    QRegExp Algebraic_ValueEntry_rx(PeriodRadix_ValidValue);
    Algebraic_ValueEntry_LineEdit->setValidator(new QRegExpValidator(Algebraic_ValueEntry_rx, Algebraic_ValueEntry_LineEdit));
    connect(Algebraic_ValueEntry_LineEdit, SIGNAL(returnPressed()),
            this, SLOT(Algebraic_ValueEntry_returnPressed()));
    connect(Algebraic_ValueEntry_LineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(Algebraic_ValueEntry_textChanged(QString)));
    connect(Algebraic_ValueEntry_LineEdit, SIGNAL(keyPressed(int)),
            this, SLOT(Algebraic_keyPressed(int)));

    Algebraic_GroupBox = new QGroupBox(this);
    Algebraic_GroupBox->setMinimumHeight(Algebraic_GroupBox_MinHeight);
    QGridLayout *Algebraic_GridLayout = new QGridLayout();
    Algebraic_GridLayout->setContentsMargins(0, 0, 0, 0);
    Algebraic_GridLayout->setVerticalSpacing(0);
    Algebraic_GridLayout->addWidget(Algebraic_Value_PlainTextEdit, 0, 0);
    Algebraic_GridLayout->addWidget(Algebraic_PlainTextEdit, 1, 0);
    Algebraic_GridLayout->addWidget(Algebraic_ValueEntry_LineEdit, 2, 0);
    Algebraic_GroupBox->setLayout(Algebraic_GridLayout);

    // Program Mode
    Program_PlainTextEdit = new PlainTextEdit(this);
    Program_PlainTextEdit->setMinimumWidth(APCalculator_WindowWidth - 8);
    Program_PlainTextEdit->setMinimumHeight(124);
    Program_PlainTextEdit->setContentsMargins(0, 0, 0, 0);
    Program_PlainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    connect(Program_PlainTextEdit, SIGNAL(keyPressed(int)),
            this, SLOT(Program_keyPressed(int)));

    Program_Value_PlainTextEdit = new QPlainTextEdit(this);
    Program_Value_PlainTextEdit->setMinimumWidth(APCalculator_WindowWidth - 8);
    Program_Value_PlainTextEdit->setMinimumHeight(122); // 116
    Program_Value_PlainTextEdit->setContentsMargins(0, 0, 0, 0);
    Program_Value_PlainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    Program_Value_PlainTextEdit->setReadOnly(true);

    Program_GroupBox = new QGroupBox(this);
    Program_GroupBox->setMinimumHeight(Program_GroupBox_MinHeight);
    QGridLayout *Program_GridLayout = new QGridLayout();
    Program_GridLayout->setContentsMargins(0, 0, 0, 0);
    Program_GridLayout->setVerticalSpacing(0);
    Program_GridLayout->addWidget(Program_PlainTextEdit, 0, 0);
    Program_GridLayout->addWidget(Program_Value_PlainTextEdit, 1, 0);
    Program_GroupBox->setLayout(Program_GridLayout);

    // Solver Mode
    Solver_PlainTextEdit = new QPlainTextEdit(this);
    Solver_PlainTextEdit->setMinimumWidth(APCalculator_WindowWidth - 8);
    Solver_PlainTextEdit->setMinimumHeight(22);
    Solver_PlainTextEdit->setContentsMargins(0, 0, 0, 0);
    Solver_PlainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);

    SolverData_TableWidget = new QTableWidget(SolverData_RowCount, 3, this);
    SolverData_TableWidget->setColumnWidth(Solver_Name_Column, Solver_Name_ColumnWidth);
    SolverData_TableWidget->setColumnWidth(Solver_Solve_Column, Solver_Solve_ColumnWidth);
    SolverData_TableWidget->setColumnWidth(Solver_Value_Column, Solver_Value_ColumnWidth);
    SolverData_TableWidget->verticalHeader()->hide();
    SolverData_TableWidget->horizontalHeader()->hide();
    SolverData_TableWidget->setMinimumHeight(292);
    SolverData_TableWidget->setMaximumHeight(292);
    SolverData_TableWidget->setContentsMargins(0, 0, 0, 0);
    for (int r = 0; r < SolverData_RowCount; r++) {
        SolverData_TableWidget->setRowHeight(r, SolverData_RowHeight);
        SolverData_setCellText((r + 1), Solver_Name_Column, (char*) "");
        SolverData_setCellText((r + 1), Solver_Solve_Column, (char*) "?");
        SolverData_setCellText((r + 1), Solver_Value_Column, (char*) "");
    }
    connect(SolverData_TableWidget, SIGNAL(cellClicked(int,int)),
            this, SLOT(SolverData_CellClicked(int,int)));

    Solver_ValueEntry_LineEdit = new LineEdit(SolverData_TableWidget);
    QRegExp Solver_ValueEntry_rx(PeriodRadix_ValidValue);
    Solver_ValueEntry_LineEdit->setValidator(new QRegExpValidator(Solver_ValueEntry_rx, Solver_ValueEntry_LineEdit));
    connect(Solver_ValueEntry_LineEdit, SIGNAL(returnPressed()),
            this, SLOT(Solver_ValueEntry_returnPressed()));
    connect(Solver_ValueEntry_LineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(Solver_ValueEntry_textChanged(QString)));
    connect(Solver_ValueEntry_LineEdit, SIGNAL(keyPressed(int)),
            this, SLOT(Solver_ValueEntry_keyPressed(int)));

    Calculator_Mode = RPN_Mode;
    RadixMark_Mode = RadixMark_Period;
    Radix_Mark = (char*) ".";
    Standard_Digit_Separator = QChar((char) ',');
    // three-per-em space (0x2004) 1/3 em, easily visible,
    // four-per-em space (0x2005) 1/4 em, easily visible,
    // punctuation space (0x2008) width of '.', easily visible,
    // thin space (0x2009) easily visible,
    // hair space (0x200A)  too thin to see easily,
    // zero width space (0x200B) too thin to see easily
    Narrow_Space = QChar(0x2009);
    Digit_Separator = Narrow_Space;

    Angle_Mode = Angle_Degrees;
    Buttons_Index = 0;
    Recall_Mode = RecallMode_Eval;
    Suppress_DigitGrouping = false;

    CreateButtons();
    CalculatorButtons_SetText(Calculator_Mode, Buttons_Index);
    Buttons_GroupBox = new QGroupBox(this);

    QGridLayout *buttons_GridLayout = RPNButtons_GridLayout();
    Buttons_GroupBox->setLayout(buttons_GridLayout);

    History_Index = 0;

    Program_Defines = "";

    Algebraic_FocusOwner = FocusParagraph;

    RPN_Mode_UI();
    // For testing:
    // Algebraic_Mode_UI();
    // Solver_Mode_UI();
}

APCalcClass::~APCalcClass ( ) {
}

void APCalcClass::RPN_Mode_UI() {
    CalculatorButtons_SetText(Calculator_Mode, Buttons_Index);

    QGridLayout *buttons_GridLayout = RPNButtons_GridLayout();
    delete Buttons_GroupBox->layout();
    Buttons_GroupBox->setLayout(buttons_GridLayout);

    QVBoxLayout *windowLayout = new QVBoxLayout();
    windowLayout->setContentsMargins(0, 0, 0, 0);
    // Windows
    windowLayout->setMenuBar(APCalc_MenuBar);
    windowLayout->addWidget(RPN_GroupBox, 0) ;
    windowLayout->addWidget(Buttons_GroupBox, 0);
    delete layout();
    setLayout(windowLayout);

    Equation_Menu->setEnabled(false);

    Algebraic_GroupBox->setVisible(false);
    Program_GroupBox->setVisible(false);
    Solver_PlainTextEdit->setVisible(false);
    SolverData_TableWidget->setVisible(false);
    Solver_ValueEntry_LineEdit->setVisible(false);

    RPN_GroupBox->setVisible(true);
    Buttons_GroupBox->setVisible(true);

    ValueEntry_LineEdit->setFocus();
}

void APCalcClass::Algebraic_Mode_UI() {
    CalculatorButtons_SetText(Calculator_Mode, Buttons_Index);

    QGridLayout *buttons_GridLayout = AlgebraicButtons_GridLayout();
    delete Buttons_GroupBox->layout();
    Buttons_GroupBox->setLayout(buttons_GridLayout);

    QVBoxLayout *windowLayout = new QVBoxLayout();
    windowLayout->setContentsMargins(0, 0, 0, 0);
    // Windows
    windowLayout->setMenuBar(APCalc_MenuBar);
    windowLayout->addWidget(Algebraic_GroupBox, 0) ;
    windowLayout->addWidget(Buttons_GroupBox, 0);
    delete layout();
    setLayout(windowLayout);

    Equation_Menu->setEnabled(true);

    Program_GroupBox->setVisible(false);
    RPN_GroupBox->setVisible(false);
    Solver_PlainTextEdit->setVisible(false);
    SolverData_TableWidget->setVisible(false);
    Solver_ValueEntry_LineEdit->setVisible(false);

    Algebraic_GroupBox->setVisible(true);
    Buttons_GroupBox->setVisible(true);

    if (Algebraic_FocusOwner == FocusLine)
        Algebraic_ValueEntry_LineEdit->setFocus();
    else if (Algebraic_FocusOwner == FocusParagraph)
        Algebraic_PlainTextEdit->setFocus();
}

void APCalcClass::Program_Mode_UI() {
    CalculatorButtons_SetText(Calculator_Mode, Buttons_Index);

    QGridLayout *buttons_GridLayout = ProgramButtons_GridLayout();
    delete Buttons_GroupBox->layout();
    Buttons_GroupBox->setLayout(buttons_GridLayout);

    QVBoxLayout *windowLayout = new QVBoxLayout();
    windowLayout->setContentsMargins(0, 0, 0, 0);
    // Windows
    windowLayout->setMenuBar(APCalc_MenuBar);
    windowLayout->addWidget(Program_GroupBox, 0) ;
    windowLayout->addWidget(Buttons_GroupBox, 0);
    delete layout();
    setLayout(windowLayout);

    Equation_Menu->setEnabled(true);

    Algebraic_GroupBox->setVisible(false);
    RPN_GroupBox->setVisible(false);
    Solver_PlainTextEdit->setVisible(false);
    SolverData_TableWidget->setVisible(false);
    Solver_ValueEntry_LineEdit->setVisible(false);

    Program_GroupBox->setVisible(true);
    for (int r = 1; r <= 6; r++)
        Button_SetText(r, 7, btntypNone, (char*) "", (char*) "");
    Buttons_GroupBox->setVisible(true);

    Program_PlainTextEdit->setFocus();
}

void APCalcClass::Solver_Mode_UI() {
    QVBoxLayout *windowLayout = new QVBoxLayout();
    windowLayout->setContentsMargins(0, 0, 0, 0);
    // Windows
    windowLayout->setMenuBar(APCalc_MenuBar);
    windowLayout->addWidget(SolverData_TableWidget, 0);
    windowLayout->addWidget(Solver_PlainTextEdit, 0) ;
    delete layout();
    setLayout(windowLayout);

    Equation_Menu->setEnabled(false);

    RPN_GroupBox->setVisible(false);
    Algebraic_GroupBox->setVisible(false);
    Buttons_GroupBox->setVisible(false);

    Solver_PlainTextEdit->setVisible(true);
    SolverData_TableWidget->setVisible(true);
    Solver_ValueEntry_LineEdit->setVisible(false);

    Solver_PlainTextEdit->setFocus();
}

void APCalcClass::APCalcClass_PostInitialize(QString Application_Path,
                                             QStringList Application_Arguments) {
    Q_UNUSED ( Application_Arguments )
    InitializeCalc();

    Set_DefaultDirectory(Application_Path);

#ifdef Q_OS_MAC
    // QString ini_filename = "~/Documents/APCalculator/APCalculator.ini";
    QDir ini_dir("_");
    QString ini_filename = ini_dir.homePath() + "/Documents/APCalculator/APCalculator.ini";
#else
    QString ini_filename = Application_Path;
    if (Application_Arguments.count() > 1 /* The 1st arg is the exe path */ ) {
        // The 2nd arg is the first command line item
        QFileInfo f_info(Application_Arguments.at(1));
        if (f_info.canonicalPath().length() == 0) {
            ini_filename.append("/");
            ini_filename.append(Application_Arguments.at(1));
        }
        else ini_filename = Application_Arguments.at(1);
    }
    else ini_filename.append("/APCalculator.ini");
#endif

    QFileInfo ini_info(ini_filename);
    if (ini_info.exists()) ImportInitializationFile(ini_filename);

    switch (Calculator_Mode) {
    case RPN_Mode:
        ValueEntry_LineEdit->setFocus();
        break;
    case Algebraic_Mode:
    case Algebraic_Interactive_Mode:
        Algebraic_PlainTextEdit->setFocus();
        break;
    case Program_Mode:
        Program_PlainTextEdit->setFocus();
        break;
    }
}

void APCalcClass::APCalcClass_PreTerminate() {
    delete Cyan_Brush;
    delete Yellow_Brush;
}

QString
APCalcClass::Normalize_ValueEntry(QString ValueEntry) {
    QString normalize_value = RemoveDigitGrouping(ValueEntry);
    return normalize_value.replace(',', '.');
}

QString
APCalcClass::DisplayValue(char* cp_Value) {
    QString value_string = cp_Value;
    if (RadixMark_Mode == RadixMark_Comma) value_string.replace('.', ',');
    if (value_string.indexOf(QRegExp("0[xX][0-9A-Fa-f]+")) >= 0) {
        value_string = value_string.toUpper();
        value_string = value_string.replace("0X", "0x");
    }
    else if (value_string.indexOf(QRegExp("0[bB][01]+")) >= 0) {
        QRegExp rx("0[bB][01]+");
        value_string = value_string.replace("0B", "0b");
    }
    return DigitGroup(value_string);
}

// There are three forms of digit grouping:
// Left of radix mark ('.' or ',') i.e. integer part of decimal number:
//     digits grouped in thousands w/ other radix mark
// Right of radix mark ('.' or ',') i.e. fractional part of decimal number:
//     digits separated in thousandths w/ thin space
// Hexadecimal or binary integer (0x... or 0b...):
//     digits separated in thousandths w/ thin space
QString
APCalcClass::DigitGroup(QString RawDigits) {
    QString raw = RawDigits.trimmed();

    if (raw.startsWith("0b") || raw.startsWith("0B") ||
        raw.startsWith("0x") || raw.startsWith("0X")) {
        // Binary and Hexadecimal may only be used for...
        // real integer values (no fractional or imaginary part)
        return DigitGroup_BinHex(raw);
    }
    else {
        int img_idx = 0;
        if (raw.endsWith('i')) {
            // There is certainly an imaginary part...
            // ...now test for real part
            img_idx = raw.indexOf(QRegExp("\\d[+-]\\d"));
            if (img_idx > 0) img_idx = img_idx + 1;
            // img_idx now points to separation between real and imaginary parts
        }

        if (img_idx > 0) {
            // Complex number w/ both real and imaginary parts
            QString raw_real = raw.left(img_idx).trimmed();
            QString raw_imaginary = raw.right(raw.length() - img_idx).trimmed();
            return DigitGroup_Decimal(raw_real) + ' ' + DigitGroup_Decimal(raw_imaginary);
        }
        else return DigitGroup_Decimal(raw);
    }
}

QString
APCalcClass::DigitGroup_Decimal(QString RawDigits) {
    QString raw = RawDigits;
    QString approx = "";
    QString sign = "";
    QString digits = "";
    QString exponent = "";
    QString imaginary = "";
    QString comment = "";

    if (raw.left(1) == "~") {
        approx.append(raw.left(1));
        raw.remove(0, 1);
    }

    if ((raw.left(1) == "+") || (raw.left(1) == "-")) {
        sign.append(raw.left(1));
        raw.remove(0, 1);
    }

    if (raw.contains('e')) {
        int exp_idx = raw.indexOf('e');
        exponent = raw.mid(exp_idx);
        raw = raw.left(exp_idx);
    }

    if (raw.endsWith('i')) {
        imaginary = raw.right(1);
        raw.chop(1);
    }

    if (raw.contains("/*")) {
        int com_idx = raw.indexOf("/*");
        comment = raw.mid(com_idx);
        raw = raw.left(com_idx);
    }

    while (((raw.left(1) >= ("0")) && (raw.left(1) <= ("9"))) ||
           (raw.left(1) == ("|"))) {
        digits.append(raw.left(1));
        raw.remove(0, 1);
    }

    if (digits.length() > 0) {
        // Digit separators after radix mark and before exponent
        int radix_idx = -1;
        if (RadixMark_Mode == RadixMark_Period)
            radix_idx = raw.indexOf('.');
        else
            radix_idx = raw.indexOf(',');
        if (radix_idx >= 0) {
            for (int ch_idx = (radix_idx + 4); ch_idx < raw.length(); ) {
                raw.insert(ch_idx, Narrow_Space);
                ch_idx = ch_idx + 4;
            }
        }
        // Digit separators after radix mark and before exponent

        QString grouped_digits = raw;
        while (digits.length() > 3) {
            grouped_digits.prepend(digits.right(3));
            grouped_digits.prepend(Digit_Separator);
            digits.chop(3);
        }
        grouped_digits.prepend(digits);
        grouped_digits.prepend(sign);
        grouped_digits.prepend(approx);

        grouped_digits.append(exponent);
        grouped_digits.append(imaginary);
        grouped_digits.append(comment);
        return grouped_digits;
    }
    else return RawDigits;
}

QString
APCalcClass::DigitGroup_BinHex(QString RawDigits) {
    QString raw = RawDigits.trimmed();
    QString sign_base = "";
    QString digits = "";

    sign_base.append(raw.left(2));
    raw.remove(0, 2);

    while (((raw.left(1) >= ("0")) && (raw.left(1) <= ("9"))) ||
           ((raw.left(1) >= ("a")) && (raw.left(1) <= ("f"))) ||
           ((raw.left(1) >= ("A")) && (raw.left(1) <= ("F"))) ||
           (raw.left(1) == ("|"))) {
        digits.append(raw.left(1));
        raw.remove(0, 1);
    }
    if (digits.length() > 0) {
        digits = digits.toUpper();
        QString grouped_digits = raw;
        while (digits.length() > 4) {
            grouped_digits.prepend(digits.right(4));
            grouped_digits.prepend(Narrow_Space);
            digits.chop(4);
        }
        grouped_digits.prepend(digits);
        grouped_digits.prepend(sign_base.toLower());
        return grouped_digits;
    }
    else return RawDigits;
}

QString
APCalcClass::RemoveDigitGrouping(QString GroupedDigits) {
    return GroupedDigits.remove(Standard_Digit_Separator).remove(Narrow_Space);
}

bool
APCalcClass::IsDigitGroupingCharacter(QChar Test_Character) {
    return ((Test_Character == Digit_Separator) ||
            (Test_Character == Narrow_Space));
}

QString
APCalcClass::ValueStack_CellText(int Row, int Column) {
    return ValueStack_TableWidget->item((Row - 1), Column)->text();
}

void
APCalcClass::ValueStack_setCellText(int Row, int Column, QString Text) {
    QTableWidgetItem *data_itm = new QTableWidgetItem(Text);
    data_itm->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    if (((Row - 1) % 2) == 0) {
        if (Column == ValueStack_StackColumn)
            data_itm->setBackground(*Cyan_Brush);
        else if (Column == ValueStack_MemoryColumn)
            data_itm->setBackground(*Yellow_Brush);
    }
    else
        data_itm->setBackground(Qt::white);
    data_itm->setForeground(Qt::black);
    data_itm->setFlags(Qt::NoItemFlags);

    QTableWidgetItem *prev_itm = ValueStack_TableWidget->item((Row - 1), Column);
    delete prev_itm;
    ValueStack_TableWidget->setItem((Row - 1), Column, data_itm);
}

void
APCalcClass::ValueStack_ColumnVisible(int Column) {
    char ch[8];
    ch[1] = (char)0;
    if (Column == ValueStack_StackColumn) {
        for (int r = 0; r < ValueStack_RowCount; r++) {
            ch[0] = (char)((int)'0' + ValueStack_RowCount - r - 1);
            QTableWidgetItem *hdr_itm = new QTableWidgetItem(tr(ch));
            hdr_itm->setFlags(Qt::NoItemFlags);

            QTableWidgetItem *prev_itm = ValueStack_TableWidget->verticalHeaderItem(r);
            delete prev_itm;
            ValueStack_TableWidget->setVerticalHeaderItem(r, hdr_itm);
        }
        ValueStack_TableWidget->setColumnWidth(ValueStack_StackColumn, ValueStack_StackColumnWidth);
        ValueStack_TableWidget->setColumnWidth(ValueStack_MemoryColumn, 0);
    }
    else if (Column == ValueStack_MemoryColumn) {
        for (int r = 0; r < ValueStack_RowCount; r++) {
            ch[0] = (char)((int)'A' + r);
            QTableWidgetItem *hdr_itm = new QTableWidgetItem(tr(ch));
            hdr_itm->setFlags(Qt::NoItemFlags);

            QTableWidgetItem *prev_itm = ValueStack_TableWidget->verticalHeaderItem(r);
            delete prev_itm;
            ValueStack_TableWidget->setVerticalHeaderItem(r, hdr_itm);
        }
        ValueStack_TableWidget->setColumnWidth(ValueStack_StackColumn, 0);
        ValueStack_TableWidget->setColumnWidth(ValueStack_MemoryColumn, ValueStack_MemoryColumnWidth);
    }
}
