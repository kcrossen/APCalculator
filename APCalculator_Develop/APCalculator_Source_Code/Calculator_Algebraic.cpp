#include <QtGui>

#include "Calculator_UI.h"

extern "C" {
#include "libAPCalc.h"
#include "History.h"
}

static int userMark;

void
APCalcClass::Algebraic_SetFocus() {
    if (Algebraic_FocusOwner == FocusLine) {
        Algebraic_ValueEntry_LineEdit->setFocus();
    }
    else if (Algebraic_FocusOwner == FocusParagraph) {
        Algebraic_PlainTextEdit->setFocus();
    }
}

void
APCalcClass::Algebraic_InsertText(QString InsertText) {
    if (Algebraic_FocusOwner == FocusLine) {
        Algebraic_ValueEntry_LineEdit->insert(InsertText);
    }
    else if (Algebraic_FocusOwner == FocusParagraph) {
        Algebraic_PlainTextEdit->insertPlainText(InsertText);
    }
}

void
APCalcClass::Algebraic_ButtonExecute(ButtonDefinition *Execute_Button) {
    char* operand = Normalize_ValueEntry(Algebraic_ValueEntry_LineEdit->text()).toLatin1().data();
    Qt::KeyboardModifiers keymod = QApplication::keyboardModifiers();

    int hist_idx = 0;

    switch (Execute_Button->ButtonType) {
        case btntypNone: break;

        case btntypBase:
        case btntypChar:
            if ((Algebraic_FocusOwner == FocusLine) &&
                (strlen(operand) == 0)) {
                if ((keymod & Qt::AltModifier) != 0) {
                    if (Execute_Button->ButtonType == btntypBase)
                        Algebraic_ValueEntry_LineEdit->insert("0b");
                }
                else if (strcmp(Execute_Button->Program, "E") == 0)
                    Algebraic_ValueEntry_LineEdit->insert("1E");
                else if (strcmp(Execute_Button->Program, "i") == 0)
                    Algebraic_ValueEntry_LineEdit->insert("1i");
                else Algebraic_ValueEntry_LineEdit->insert(Execute_Button->Program);
            }
            else if ((Execute_Button->ButtonType == btntypBase) &&
                     ((keymod & Qt::AltModifier) != 0))
                Algebraic_InsertText("0b");
            else Algebraic_InsertText(Execute_Button->Program);
            break;
        case btntypRadixMark:
            if (Algebraic_FocusOwner == FocusParagraph)
                Algebraic_InsertText(".");
            else Algebraic_InsertText(Radix_Mark);
            break;
        case btntypDelete:
            if (Algebraic_FocusOwner == FocusLine) {
                if (Algebraic_ValueEntry_LineEdit->selectedText().length() == 0)
                    Algebraic_ValueEntry_LineEdit->cursorBackward(true, 1);
                Algebraic_ValueEntry_LineEdit->del();
            }
            else {
                if (Algebraic_PlainTextEdit->textCursor().selectedText().length() == 0)
                    Algebraic_PlainTextEdit->moveCursor(QTextCursor::Left, QTextCursor::KeepAnchor);
                Algebraic_PlainTextEdit->insertPlainText("");
            }
            break;

        case btntypShift:
            Buttons_Index = (Buttons_Index + 1) % Algebraic_ButtonSets;
            CalculatorButtons_SetText(Calculator_Mode, Buttons_Index);
            break;

        case btntypFunction:
        case btntypOperator:
        case btntypParens:
            Algebraic_PlainTextEdit->insertPlainText(Execute_Button->Program);
            if (Execute_Button->ParameterAction == FindParameter)
                Algebraic_FindQuestionMark();
            Algebraic_SetFocus();
            break;
        case btntypEval:
            Algebraic_Evaluate(false);
            Algebraic_SetFocus();
            break;
        case btntypClear:
            Algebraic_PlainTextEdit->clear();
            Algebraic_ValueEntry_LineEdit->clear();
            Algebraic_Value_PlainTextEdit->clear();
            Algebraic_SetFocus();
            break;

        case btntypPrevEval:
            hist_idx = History_Index;
            while (hist_idx > 1) {
                hist_idx = hist_idx - 1;
                if (recall_history_mode(hist_idx) == Algebraic_Mode) {
                    History_Index = hist_idx;
                    break;
                }
            }
            if (recall_history_mode(History_Index) != Algebraic_Mode) break;
            if (Recall_Mode == RecallMode_Eval) {
                Algebraic_PlainTextEdit->setPlainText(recall_history(History_Index));
                Algebraic_Value_PlainTextEdit->clear();
            }
            else if (Recall_Mode == RecallMode_Eval_Value) {
                Algebraic_PlainTextEdit->setPlainText(recall_history(History_Index));
                Algebraic_Value_PlainTextEdit->setPlainText(recall_history_value(History_Index));
            }
            break;
        case btntypNextEval:
            hist_idx = History_Index;
            while (hist_idx < saved_history_count()) {
                hist_idx = hist_idx + 1;
                if (recall_history_mode(hist_idx) == Algebraic_Mode) {
                    History_Index = hist_idx;
                    break;
                }
            }
            if (recall_history_mode(History_Index) != Algebraic_Mode) break;
            if (Recall_Mode == RecallMode_Eval) {
                Algebraic_PlainTextEdit->setPlainText(recall_history(History_Index));
                Algebraic_Value_PlainTextEdit->clear();
            }
            else if (Recall_Mode == RecallMode_Eval_Value) {
                Algebraic_PlainTextEdit->setPlainText(recall_history(History_Index));
                Algebraic_Value_PlainTextEdit->setPlainText(recall_history_value(History_Index));
            }
            break;
        case btntypAns:
            hist_idx = saved_history_count();
            do {
                if (recall_history_mode(hist_idx) == Algebraic_Mode) break;
                hist_idx = hist_idx - 1;
            } while (hist_idx > 1);
            if (recall_history_mode(hist_idx) != Algebraic_Mode) break;
            if ((keymod & Qt::AltModifier) != 0) {
                QApplication::clipboard()->setText
                                             (str_trim(recall_history_value(hist_idx)));
            }
            else {
                Algebraic_PlainTextEdit->insertPlainText(str_trim(recall_history_value(hist_idx)));
                Algebraic_Value_PlainTextEdit->clear();
            }
            break;

        case btntypEnter:
            Algebraic_ValueEntry_returnPressed();
            break;

        case btntypCursorLeft:
            Algebraic_moveCursorLeft();
            break;
        case btntypCursorRight:
            Algebraic_moveCursorRight();
            break;

        case btntypFocusParagraph:
            Algebraic_FocusOwner = FocusParagraph;
            Algebraic_SetFocus();
            break;
        case btntypFocusLine:
            Algebraic_FocusOwner = FocusLine;
            Algebraic_SetFocus();
            break;

        case btntypTrigShift:
            Buttons_Index = 1;
            CalculatorButtons_SetText(Calculator_Mode, Buttons_Index);
            break;

        case btntypMathShift:
            Buttons_Index = 2;
            CalculatorButtons_SetText(Calculator_Mode, Buttons_Index);
            break;

        default: break;
    }

    if ((Buttons_Index > 0) &&
        ((Execute_Button->ButtonType != btntypTrigShift) &&
         (Execute_Button->ButtonType != btntypMathShift))) {
        Buttons_Index = 0;
        CalculatorButtons_SetText(Calculator_Mode, Buttons_Index);
    }
}

void
APCalcClass::Algebraic_FindQuestionMark() {
    Algebraic_PlainTextEdit->find("?", QTextDocument::FindBackward);
    Algebraic_PlainTextEdit->moveCursor(QTextCursor::Right, QTextCursor::KeepAnchor);
    QString last_ch = Algebraic_PlainTextEdit->textCursor().selectedText().right(1).toLower();
    while ((last_ch >= ("a")) && (last_ch <= ("z"))) {
        Algebraic_PlainTextEdit->moveCursor(QTextCursor::Right, QTextCursor::KeepAnchor);
        last_ch = Algebraic_PlainTextEdit->textCursor().selectedText().right(1).toLower();
    }
    Algebraic_PlainTextEdit->moveCursor(QTextCursor::Left, QTextCursor::KeepAnchor);
}

#define evalalgTabReplace "  "

void
APCalcClass::Algebraic_Evaluate(bool AlgebraicInteractive) {
    char* out_err_str = NULL;
    char* out_str = NULL;
    char* err_str = NULL;
    int err;

    // char* evalstr = Algebraic_PlainTextEdit->toPlainText().toLatin1().data();
    QString eval = Algebraic_PlainTextEdit->text();
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

    if (AlgebraicInteractive == false) {
        if (out_err_str != NULL) {
            if (strlen(out_err_str) > 0) {
                eval = Algebraic_PlainTextEdit->text();
                save_history_algebraic(eval.toLatin1().data(), out_err_str);
                History_Index = saved_history_count() + 1;
            }
        }
    }

    Algebraic_Value_PlainTextEdit->clear();

    if (out_str != NULL) {
        if (strlen(out_str) > 0) {
            QString display_operand = DisplayValue(str_trim(out_str));
            Algebraic_Value_PlainTextEdit->setPlainText(display_operand.trimmed());
        }
    }

    if (AlgebraicInteractive == false) {
        if (err_str != NULL) {
            if (strlen(err_str) > 0) {
                Algebraic_Value_PlainTextEdit->appendPlainText(err_str);
            }
        }
    }

    if (out_err_str != NULL) free(out_err_str);
    if (out_str != NULL) free(out_str);
    if (err_str != NULL) free(err_str);
}

void
APCalcClass::Algebraic_focusIn() {
    Algebraic_FocusOwner = FocusParagraph;
}

void
APCalcClass::Algebraic_focusOut() {
    Algebraic_FocusOwner = FocusLine;
}

void
APCalcClass::Algebraic_textChanged() {
    static bool Suppress_textChanged = false;
    if (Suppress_textChanged) return;
    Suppress_textChanged = true;
    if (Calculator_Mode != Algebraic_Interactive_Mode) {
        if (Algebraic_FocusOwner == FocusLine)
            Algebraic_PlainTextEdit->insertTextCursorIndicator();
        Suppress_textChanged = false;
        return;
    }
    Algebraic_Evaluate(Calculator_Mode == Algebraic_Interactive_Mode);
    if (Algebraic_FocusOwner == FocusLine)
        Algebraic_PlainTextEdit->insertTextCursorIndicator();
    Suppress_textChanged = false;
}

void
APCalcClass::Algebraic_moveCursorLeft() {
    Algebraic_PlainTextEdit->removeTextCursorIndicator();
    Algebraic_PlainTextEdit->moveCursor(QTextCursor::Left);
    Algebraic_PlainTextEdit->insertTextCursorIndicator();
}

void
APCalcClass::Algebraic_moveCursorRight() {
    Algebraic_PlainTextEdit->removeTextCursorIndicator();
    Algebraic_PlainTextEdit->moveCursor(QTextCursor::Right);
    Algebraic_PlainTextEdit->insertTextCursorIndicator();
}

void
APCalcClass::Algebraic_keyPressed(int Key) {
    // These keys apply regardless of focus
    Qt::KeyboardModifiers modifiers = QApplication::keyboardModifiers();
    if ((modifiers & Qt::ControlModifier) ||
        (modifiers & Qt::AltModifier)) {
        if (Key == Qt::Key_C) {
            QString result;

            // If the algebraic expression entry widget contains selected text, get that text
            result = Algebraic_PlainTextEdit->textCursor().selectedText();
            if (result.length() == 0) {
                // Otherwise, get the content of the value display widget
                result = Algebraic_Value_PlainTextEdit->toPlainText();
                // Potentially remove digit grouping
                if (modifiers & Qt::AltModifier) result = RemoveDigitGrouping(result);
            }
            // And put on clipboard
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(result);
        }
    }
    else if (Key == Qt::Key_Escape)
        Algebraic_AdHocEvaluate();
    else if (Key == Qt::Key_PageUp) {
        Algebraic_FocusOwner = FocusParagraph;
        Algebraic_SetFocus();
    }
    else if (Key == Qt::Key_PageDown) {
        Algebraic_FocusOwner = FocusLine;
        Algebraic_SetFocus();
    }
    else if (Algebraic_FocusOwner == FocusLine) {
        // These keys only apply in the numeric value entry box
        if ((Key == Qt::Key_Space) || (Key == Qt::Key_Equal) ||
            (Key == Qt::Key_ParenLeft) || (Key == Qt::Key_ParenRight) ||
            (Key == Qt::Key_Plus) || (Key == Qt::Key_AsciiCircum) ||
            (Key == Qt::Key_Slash) || (Key == Qt::Key_Asterisk) ||
            (Key == Qt::Key_Less) || (Key == Qt::Key_Greater))
            Algebraic_PlainTextEdit->insertPlainText(QChar(Key));
    }
    else if (Algebraic_FocusOwner == FocusParagraph) {
        // These keys apply in the Algebraic entry box
        if (Key == Qt::Key_Insert) {
            Algebraic_ValueEntry_LineEdit->clear();
            Algebraic_SetFocus();
        }
    }
}

void
APCalcClass::Algebraic_ValueEntry_textChanged(QString newText) {
    LineEdit_textChanged(Algebraic_ValueEntry_LineEdit, newText);
}

void
APCalcClass::Algebraic_ValueEntry_returnPressed() {
    Algebraic_PlainTextEdit->removeTextCursorIndicator();
    Algebraic_PlainTextEdit->insertPlainText(Normalize_ValueEntry(Algebraic_ValueEntry_LineEdit->text()).toLatin1().data());
    Algebraic_PlainTextEdit->insertTextCursorIndicator();
    Algebraic_ValueEntry_LineEdit->clear();
    Algebraic_SetFocus();
}



