#include "Calculator_UI.h"

extern "C" {
#include "libAPCalc.h"
#include "History.h"
// #include "RegExp.h"
}

static int userMark;
static char cmdstr[MAXCMD+1+1+1];

char*
APCalcClass::LoadSolver(char* SolverText) {

    char* str = InitializeSolver(SolverText);

    // set_run_state(RUN_TOP_LEVEL);

    userMark = user_mark();

    str = str_trim(str);

    user_line(std_in, str);

    user_clear();

    (void) openstring(str, strlen(str));
    int err = 0;
    err = execute_commands(true);
    closeinput();

    user_flush();

    if (user_count((std_in | std_out | std_err), userMark) > 0) {
        str = user_return((std_in | std_out | std_err), userMark, (char*) "", (char*) "\t", (char*) "\r\n");
    }

    return str;
}

#define MaxVarName 500

struct Solver_DataRow_Descriptor {
    QString DataRow_Name;
    QString DataRow_Value;
    QString DataRow_Comment;
};

// This solves a bug in Qt 4.7.0 in which for a QTableWidget...
// ...when one cell on a row is edited (only one column is editable), ...
// ...the value for all of the columns on the edited row...
// ...char* txt = TableWidget->item(Row, Column)->text().toLatin1().data()...
// ...can be the same as the value of the edited cell.
// If no cell is edited, the values for all cells will be returned as expected.

Solver_DataRow_Descriptor Solver_DataRow[SolverData_RowCount];
int Solver_DataRow_Count = 0;
int Solver_SolvableDataRow_Count = 0;

QString Solver_Function_Name = "";
QString Solver_Function_Comment = "";

void
Initialize_Solver_DataRows() {
    for (int r = 1; r <= SolverData_RowCount; r++) {
        Solver_DataRow[r - 1].DataRow_Name = "";
        Solver_DataRow[r - 1].DataRow_Value = "";
        Solver_DataRow[r - 1].DataRow_Comment = "";
    }
    Solver_DataRow_Count = 0;
    Solver_SolvableDataRow_Count = 0;
    Solver_Function_Name = "";
    Solver_Function_Comment = "";
}

bool
APCalcClass::Solve_Comment_Contains(int Row, QString Content) {
    return Solver_DataRow[Row - 1].DataRow_Comment.contains(Content);
}

char*
APCalcClass::InitializeSolver(char* SolverText) {
    Initialize_Solver_DataRows();
    int solver_idx = 0;

    QRegExp name_rx("([a-zA-Z_]+)" "([ ]+/[*][^*]*[*]/)?");
    QRegExp value_rx(PeriodRadix_ValidValue);
    QRegExp function_rx("[a-zA-Z_]+");
    QRegExp comment_rx("/[*]([^*]*)[*]/");
    QRegExp semicolon_rx(";");

    QString solver_txt(SolverText);

    while (true) {
        int name_idx = solver_txt.indexOf(name_rx, solver_idx);
        solver_idx = name_idx + name_rx.cap(0).length();
        solver_txt.indexOf(value_rx, solver_idx);
        solver_txt.indexOf(function_rx, solver_idx);
        int comment_idx = solver_txt.indexOf(comment_rx, solver_idx);
        int semicolon_idx = solver_txt.indexOf(semicolon_rx, solver_idx);

        solver_idx = semicolon_idx + 1;

        if (name_rx.cap(1) == "define") {
            Solver_Function_Name = function_rx.cap(0);
            name_rx.cap(0).indexOf(comment_rx);
            Solver_Function_Comment = comment_rx.cap(1);
            break;
        }

        Solver_DataRow[Solver_DataRow_Count].DataRow_Name = name_rx.cap(0);
        Solver_DataRow[Solver_DataRow_Count].DataRow_Value =
          value_rx.cap(0).remove(",");
        if (comment_idx < semicolon_idx)
            Solver_DataRow[Solver_DataRow_Count].DataRow_Comment = comment_rx.cap(1);
        Solver_DataRow_Count = Solver_DataRow_Count + 1;
    }

    for (int r = 1; r <= Solver_DataRow_Count; r++) {
        if (Solve_Comment_Contains(r, (char*) "?"))
            Solver_SolvableDataRow_Count = Solver_SolvableDataRow_Count + 1;
    }

    // If there are variables, but none are "solvable", handle differently

    if (Solver_SolvableDataRow_Count == 0) {
        Solver_DataRow[Solver_DataRow_Count].DataRow_Name = Solver_Function_Name;
        Solver_DataRow[Solver_DataRow_Count].DataRow_Name.append("_");
        Solver_DataRow[Solver_DataRow_Count].DataRow_Value = "0";
        if (not Solver_Function_Comment.contains("?"))
            Solver_Function_Comment.prepend("?");
        Solver_DataRow[Solver_DataRow_Count].DataRow_Comment = Solver_Function_Comment;
        Solver_DataRow_Count = Solver_DataRow_Count + 1;
    }

    for (int r = 1; r <= SolverData_RowCount; r++) {
        SolverData_setCellText
          (r, Solver_Name_Column, Solver_DataRow[r - 1].DataRow_Name);
        if (Solver_DataRow[r - 1].DataRow_Comment.contains("?"))
            SolverData_setCellText(r, Solver_Solve_Column, "?");
        else
            SolverData_setCellText(r, Solver_Solve_Column, "");
        SolverData_setCellText
          (r, Solver_Value_Column, Solver_DataRow[r - 1].DataRow_Value);
    }

    return SolverText;
}

char*
APCalcClass::GetSolverProgram(int SolveForRow) {
#define MaxIterations "1000"
#define MaxSolverProgram 10000
    char* cp_pgm = (char*)malloc(MaxSolverProgram);
    memset(cp_pgm, '\0', MaxSolverProgram);

    char varnam[100];
    char* cp_varnam;

    char varval[100];
    char* cp_varval;

    if (Solver_SolvableDataRow_Count > 0) {
        strcpy(cp_pgm, "define solver_function() {return ");
        strcat(cp_pgm, Solver_Function_Name.toLatin1().data());
        strcat(cp_pgm, "();}\r\n");
    }

    for (int r = 1; r <= SolverData_RowCount; r++) {
        cp_varnam = SolverData_CellText(r, Solver_Name_Column, varnam);
        cp_varval = SolverData_CellText(r, Solver_Value_Column, varval);
        if ((cp_varnam != NULL) && (cp_varval != NULL)) {
            if ((strlen(cp_varnam) > 0) && (strlen(cp_varval) > 0)) {
                strcat(cp_pgm, cp_varnam);
                strcat(cp_pgm, " = ");
                strcat(cp_pgm, cp_varval);
                strcat(cp_pgm, (char*) ";\r\n");
            }
        }
    }

    if (Solver_SolvableDataRow_Count > 0) {
        strcat(cp_pgm, "solution = solver(&");
        cp_varnam = SolverData_CellText(SolveForRow, Solver_Name_Column, varnam);
        strcat(cp_pgm, cp_varnam);
        strcat(cp_pgm, ", ");
        cp_varval = SolverData_CellText(SolveForRow, Solver_Value_Column, varval);
        strcat(cp_pgm, cp_varval);
        strcat(cp_pgm, ", ");
        strcat(cp_pgm, cp_varval);
        strcat(cp_pgm, ", " MaxIterations ", epsilon()); \n round(solution, (solution_digits - digits(solution)));");
    }
    else {
        strcat(cp_pgm, "solution = ");
        strcat(cp_pgm, Solver_Function_Name.toLatin1().data());
        strcat(cp_pgm, "();\r\n");
        strcat(cp_pgm, "round(solution, (solution_digits - digits(solution)));");
    }

    return cp_pgm;
}

static int SolverData_EditRow = -1;

static bool SolverData_SuppressDigitGrouping = false;

void
APCalcClass::SolverData_CellClicked(int Row, int Column) {

    /*
    char str[1000];
    str[0] = '\0';
    char buffer [33];
    itoa (Row, buffer, 10);
    strcat(str, buffer);
    strcat(str, ", ");
    itoa (Column, buffer, 10);
    strcat(str, buffer);
    Solver_PlainTextEdit->setPlainText(str);
    */

    int varRow = Row + 1;
    char txt[100];

    if (Column == Solver_Solve_Column) {
        SolverData_EndEdit(true);

        if (Solve_Comment_Contains(varRow, (char*) "?")) {
            // solve for variable
            char* cp = NULL;
            cp = GetSolverProgram(varRow);

            cmdstr[0] = '\0';

            // set_run_state(RUN_TOP_LEVEL);

            userMark = user_mark();

            user_line(std_in, cp);

            user_clear();

            (void) openstring(cp, strlen(cp));
            int err = 0;
            err = execute_commands(true);
            closeinput();

            user_flush();

            char* use_str;
            if (user_count((std_in | std_out | std_err), userMark) > 0) {
                use_str = user_return((std_in | std_out | std_err), userMark, (char*) "", (char*) "\t", (char*) "\r\n");
                strcpy(cmdstr, use_str);
                free(use_str);
            }

            if ((user_count(std_out, userMark) > 0) &&
                (user_count(std_err, userMark) == 0)) {
                use_str =
                  user_return_line
                    (std_out, userMark, user_count(std_out, userMark));
                use_str = str_trim(use_str);
                use_str = str_skipchar(use_str, '~');
                use_str = str_skipspace(use_str);
                QString display_operand = DisplayValue(use_str);
                if (Solve_Comment_Contains(varRow, (char*) "D")) display_operand = use_str;
                SolverData_setCellText
                  (varRow, Solver_Value_Column, display_operand.toLatin1().data());
                free(use_str);
            }

            Solver_PlainTextEdit->setPlainText(cmdstr);

            if (cp != NULL) free(cp);
        }
    }
    else if (Column == Solver_Value_Column) {
        char* cp = SolverData_CellText(varRow, Solver_Name_Column, txt);
        if (strlen(cp) > 0) {
            SolverData_BeginEdit(Row);
        }
    }
}

void
APCalcClass::SolverData_BeginEdit(int Row) {
    SolverData_EndEdit(true);

    if (Solve_Comment_Contains((Row + 1), (char*) "D"))
        SolverData_SuppressDigitGrouping = true;
    else
        SolverData_SuppressDigitGrouping = false;

    QRect solverdata_Rect;
    solverdata_Rect.setTop((Row * SolverData_RowHeight) + 1);
    solverdata_Rect.setLeft(SolverData_TableWidget->columnWidth(Solver_Name_Column) + 1 +
                            SolverData_TableWidget->columnWidth(Solver_Solve_Column) + 1);
    solverdata_Rect.setHeight(SolverData_RowHeight);
    solverdata_Rect.setWidth(SolverData_TableWidget->columnWidth(Solver_Value_Column));
    Solver_ValueEntry_LineEdit->setGeometry(solverdata_Rect);

    Solver_ValueEntry_LineEdit->setText(SolverData_TableWidget->item(Row, Solver_Value_Column)->text());
    Solver_ValueEntry_LineEdit->selectAll();

    Solver_ValueEntry_LineEdit->setVisible(true);

    Solver_ValueEntry_LineEdit->setFocus();

    SolverData_EditRow = Row + 1;
}

void
APCalcClass::SolverData_EndEdit(bool Save_Edits) {
    if ((SolverData_EditRow >= 1) && (SolverData_EditRow <= SolverData_RowCount)) {
        if (Save_Edits)
            SolverData_setCellText(SolverData_EditRow, Solver_Value_Column,
                                   Solver_ValueEntry_LineEdit->text().toLatin1().data());
        Solver_ValueEntry_LineEdit->setVisible(false);
        SolverData_EditRow = -1;
    }
}

void
APCalcClass::Solver_ValueEntry_returnPressed() {
    int edit_row = SolverData_EditRow;

    SolverData_EndEdit(true);

    if ((edit_row >= 1) && (edit_row < SolverData_RowCount))
        SolverData_BeginEdit(edit_row);
}

void
APCalcClass::Solver_ValueEntry_textChanged(QString newText) {
    if (not SolverData_SuppressDigitGrouping)
        LineEdit_textChanged(Solver_ValueEntry_LineEdit, newText);
}

void
APCalcClass::Solver_ValueEntry_keyPressed(int Key) {
    if (Key == Qt::Key_Escape) SolverData_EndEdit(true);
}

void
APCalcClass::Solver_DisplayDataValues() {
    char varval[100];
    char* cp_varval;

    SolverData_EndEdit(true);

    for (int r = 1; r <= SolverData_RowCount; r++) {
        cp_varval = SolverData_CellText(r, Solver_Value_Column, varval);
        if (strlen(cp_varval) > 0) {
            QString display_operand = DisplayValue(cp_varval);
            if (Solve_Comment_Contains(r, (char*) "D"))  display_operand = cp_varval;
            SolverData_setCellText
              (r, Solver_Value_Column, display_operand.toLatin1().data());
        }
        else SolverData_setCellText(r, Solver_Value_Column, (char*) "");
    }
}

void
APCalcClass::SolverData_setCellText(int Row, int Column, QString Text) {
    if (Column == Solver_Value_Column) {
        if (strlen(Text.toLatin1().data()) > 0) {
            if (Solve_Comment_Contains(Row, (char*) "I")) {
                Text = Normalize_ValueEntry(Text);
                int fract_idx = Text.indexOf(QRegExp("[.eEi][eEi0-9-]*"));
                if (fract_idx > 0)
                   Text.remove(fract_idx, Text.length());
                else if (fract_idx == 0)
                   Text = "0";
            }
        }
    }
    QTableWidgetItem *data_itm = new QTableWidgetItem(Text);
    if (Column == Solver_Value_Column) {
        if (strlen(Text.toLatin1().data()) > 0)
            Solver_DataRow[Row - 1].DataRow_Value = Normalize_ValueEntry(Text);
        else Solver_DataRow[Row - 1].DataRow_Value = "";

        data_itm->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        if (((Row - 1) % 2) == 0)
            data_itm->setBackground(*Cyan_Brush);
        else
            data_itm->setBackground(Qt::white);
        data_itm->setFlags(Qt::ItemIsEnabled);
    }
    else {
        if (Column == Solver_Name_Column) {
            data_itm->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            data_itm->setBackground(Qt::lightGray);
        }
        else {
            data_itm->setTextAlignment(Qt::AlignCenter);
            data_itm->setBackground(Qt::gray);
            if (strlen(Text.toLatin1().data()) > 0) data_itm->setToolTip("Solve For");
        }
        data_itm->setFlags(Qt::NoItemFlags);
    }
    data_itm->setForeground(Qt::black);

    QTableWidgetItem *prev_itm = SolverData_TableWidget->item((Row - 1), Column);
    delete prev_itm;
    SolverData_TableWidget->setItem((Row - 1), Column, data_itm);
}

char*
APCalcClass::SolverData_CellText(int Row, int Column, char* CellText) {
    if (Column == Solver_Name_Column) {
        strcpy(CellText, Solver_DataRow[Row - 1].DataRow_Name.toLatin1().data());
        return CellText;
    }
    else if (Column == Solver_Value_Column) {
        strcpy(CellText, Solver_DataRow[Row - 1].DataRow_Value.toLatin1().data());
        return CellText;
    }
    else {
        // This works as expected if no cell has been edited...
        // ...after editing, all cells on the same row will return...
        // ...the edited value
        QTableWidgetItem *data_itm =
          SolverData_TableWidget->item((Row - 1), Column);
        strcpy(CellText, data_itm->text().toLatin1().data());
        return CellText;
    }
}
