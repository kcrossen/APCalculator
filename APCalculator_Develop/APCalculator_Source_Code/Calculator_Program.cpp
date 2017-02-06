#include <QtGui>

#include "Calculator_UI.h"

extern "C" {
#include "libAPCalc.h"
#include "History.h"
}

static int userMark;

void
APCalcClass::Program_ButtonExecute(ButtonDefinition *Execute_Button) {
    int hist_idx = 0;

    switch (Execute_Button->ButtonType) {
        case btntypNone: break;

        case btntypShift:
            Buttons_Index = (Buttons_Index + 1) % Program_ButtonSets;
            CalculatorButtons_SetText(Calculator_Mode, Buttons_Index);
            break;

        case btntypFunction:
        case btntypProgram:
            Program_PlainTextEdit->insertPlainText(Execute_Button->Program);
            if (Execute_Button->ParameterAction == FindParameter)
                Program_FindQuestionMark();
            Program_PlainTextEdit->setFocus();
            break;
        case btntypProgramImmediate:
            Program_PlainTextEdit->setPlainText(Execute_Button->Program);
            if (Execute_Button->ParameterAction == FindParameter)
                Program_FindQuestionMark();
            Program_Evaluate();
            Program_PlainTextEdit->setFocus();
            break;
        case btntypEval:
            Program_Evaluate();
            Program_PlainTextEdit->setFocus();
            break;
        case btntypClear:
            Program_PlainTextEdit->clear();
            Program_Value_PlainTextEdit->clear();
            Program_PlainTextEdit->setFocus();
            break;

        case btntypPrevEval:
            hist_idx = History_Index;
            while (hist_idx > 1) {
                hist_idx = hist_idx - 1;
                if (recall_history_mode(hist_idx) == Program_Mode) {
                    History_Index = hist_idx;
                    break;
                }
            }
            if (recall_history_mode(History_Index) != Program_Mode) break;
            if (Recall_Mode == RecallMode_Eval) {
                Program_PlainTextEdit->setPlainText(recall_history(History_Index));
                Program_Value_PlainTextEdit->clear();
            }
            else if (Recall_Mode == RecallMode_Eval_Value) {
                Program_PlainTextEdit->setPlainText(recall_history(History_Index));
                Program_Value_PlainTextEdit->setPlainText(recall_history_value(History_Index));
            }
            break;
        case btntypNextEval:
            hist_idx = History_Index;
            while (hist_idx < saved_history_count()) {
                hist_idx = hist_idx + 1;
                if (recall_history_mode(hist_idx) == Program_Mode) {
                    History_Index = hist_idx;
                    break;
                }
            }
            if (recall_history_mode(History_Index) != Program_Mode) break;
            if (Recall_Mode == RecallMode_Eval) {
                Program_PlainTextEdit->setPlainText(recall_history(History_Index));
                Program_Value_PlainTextEdit->clear();
            }
            else if (Recall_Mode == RecallMode_Eval_Value) {
                Program_PlainTextEdit->setPlainText(recall_history(History_Index));
                Program_Value_PlainTextEdit->setPlainText(recall_history_value(History_Index));
            }
            break;
        case btntypAns:
            hist_idx = saved_history_count();
            do {
                if (recall_history_mode(hist_idx) == Program_Mode) break;
                hist_idx = hist_idx - 1;
            } while (hist_idx > 1);
            if (recall_history_mode(hist_idx) != Program_Mode) break;
            Program_PlainTextEdit->setPlainText(recall_history_value(hist_idx));
            Program_Value_PlainTextEdit->clear();
            break;

        default: break;
    }
}

void
APCalcClass::Program_FindQuestionMark() {
    Program_PlainTextEdit->find("?", QTextDocument::FindBackward);
    Program_PlainTextEdit->moveCursor(QTextCursor::Right, QTextCursor::KeepAnchor);
    QString last_ch = Program_PlainTextEdit->textCursor().selectedText().right(1).toLower();
    while ((last_ch >= ("a")) && (last_ch <= ("z"))) {
        Program_PlainTextEdit->moveCursor(QTextCursor::Right, QTextCursor::KeepAnchor);
        last_ch = Program_PlainTextEdit->textCursor().selectedText().right(1).toLower();
    }
    Program_PlainTextEdit->moveCursor(QTextCursor::Left, QTextCursor::KeepAnchor);
}

#define evalalgTabReplace "  "

void
APCalcClass::Program_Evaluate() {
    char* out_err_str = NULL;
    char* out_str = NULL;
    char* err_str = NULL;
    int err;

    // char* evalstr = Program_PlainTextEdit->toPlainText().toLatin1().data();
    QString eval = Program_PlainTextEdit->toPlainText();
    if (eval.length() <= 0) return;

    userMark = user_mark();

    user_line(std_in, eval.toLatin1().data());

    user_clear();

    if (Angle_Mode == Angle_Degrees) {
        eval.replace(QRegExp("\\bsin(\\s|\\n)*\\("), "sind(");
        eval.replace(QRegExp("\\bcos(\\s|\\n)*\\("), "cosd(");
        eval.replace(QRegExp("\\btan(\\s|\\n)*\\("), "tand(");
        eval.replace(QRegExp("\\bsec(\\s|\\n)*\\("), "secd(");
        eval.replace(QRegExp("\\bcsc(\\s|\\n)*\\("), "cscd(");
        eval.replace(QRegExp("\\bcot(\\s|\\n)*\\("), "cotd(");

        eval.replace(QRegExp("\\bsinh(\\s|\\n)*\\("), "sinhd(");
        eval.replace(QRegExp("\\bcosh(\\s|\\n)*\\("), "coshd(");
        eval.replace(QRegExp("\\btanh(\\s|\\n)*\\("), "tanhd(");
        eval.replace(QRegExp("\\bsech(\\s|\\n)*\\("), "sechd(");
        eval.replace(QRegExp("\\bcsch(\\s|\\n)*\\("), "cschd(");
        eval.replace(QRegExp("\\bcoth(\\s|\\n)*\\("), "cothd(");

        eval.replace(QRegExp("\\basin(\\s|\\n)*\\("), "asind(");
        eval.replace(QRegExp("\\bacos(\\s|\\n)*\\("), "acosd(");
        eval.replace(QRegExp("\\batan(\\s|\\n)*\\("), "atand(");
        eval.replace(QRegExp("\\basec(\\s|\\n)*\\("), "asecd(");
        eval.replace(QRegExp("\\bacsc(\\s|\\n)*\\("), "acscd(");
        eval.replace(QRegExp("\\bacot(\\s|\\n)*\\("), "acotd(");

        eval.replace(QRegExp("\\basinh(\\s|\\n)*\\("), "asinhd(");
        eval.replace(QRegExp("\\bacosh(\\s|\\n)*\\("), "acoshd(");
        eval.replace(QRegExp("\\batanh(\\s|\\n)*\\("), "atanhd(");
        eval.replace(QRegExp("\\basech(\\s|\\n)*\\("), "asechd(");
        eval.replace(QRegExp("\\bacsch(\\s|\\n)*\\("), "acschd(");
        eval.replace(QRegExp("\\bacoth(\\s|\\n)*\\("), "acothd(");

        eval.replace(QRegExp("\\batan2(\\s|\\n)*\\("), "atan2d(");
    }
    eval.replace("\n", "\\\n");
    openstring(eval.toLatin1().data(), strlen(eval.toLatin1().data()));
    err = execute_commands(true);
    closeinput();

    user_flush();

    out_err_str = NULL;

    if (user_count((std_out | std_err), userMark) > 0) {
        out_err_str = user_return((std_out | std_err), userMark, (char*) "", (char*) evalalgTabReplace, (char*) "\r\n");
    }

    out_str = NULL;

    if (user_count((std_out), userMark) > 0) {
        out_str = user_return((std_out), userMark, (char*) "", (char*) evalalgTabReplace, (char*) "\r\n");
    }

    err_str = NULL;

    if (user_count((std_err), userMark) > 0) {
        err_str = user_return((std_err), userMark, (char*) "", (char*) evalalgTabReplace, (char*) "\r\n");
    }

    if (out_err_str != NULL) {
        if (strlen(out_err_str) > 0) {
            eval = Program_PlainTextEdit->toPlainText();
            save_history_program(eval.toLatin1().data(), out_err_str);
            History_Index = saved_history_count() + 1;
        }
    }

    Program_Value_PlainTextEdit->clear();

    if (out_str != NULL) {
        if (strlen(out_str) > 0) {
            Program_Value_PlainTextEdit->appendPlainText(out_str);
        }
    }

    if (err_str != NULL) {
        if (strlen(err_str) > 0) {
            Program_Value_PlainTextEdit->appendPlainText(err_str);
        }
    }

    if (out_err_str != NULL) free(out_err_str);
    if (out_str != NULL) free(out_str);
    if (err_str != NULL) free(err_str);

    if ((err_str == NULL) &&
        (Program_PlainTextEdit->toPlainText().indexOf(QRegExp("^define\\s+")) >= 0)) {
        Program_Defines.append(Program_PlainTextEdit->toPlainText());
        Program_Defines.append("\n");
    }
}

void
APCalcClass::Program_keyPressed(int Key) {
    if (Key == Qt::Key_Escape) {
        Program_AdHocEvaluate();
    }
}



