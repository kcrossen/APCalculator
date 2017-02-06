#include <QtGui>
#include <string.h>

#include "Calculator_UI.h"

extern "C" {
#include "libAPCalc.h"
#include "History.h"
}

static int RPNMemory_ButtonPendng = 0;
static int RPNMemory_OperatorPendng = 0;

static int userMark;
static char last_operand[MAXOPERAND];

void
APCalcClass::ValueStack_CellClicked(int Row, int Column) {
    if (Calculator_Mode == RPN_Mode) {
        if (Column == ValueStack_StackColumn) {
            QString cell_value = ValueStack_CellText((Row + 1), ValueStack_StackColumn);
            Qt::KeyboardModifiers keymod = QApplication::keyboardModifiers();
            if ((keymod & Qt::ControlModifier) ||
                (keymod & Qt::AltModifier)) {
                QApplication::clipboard()->setText(cell_value);
            }
            else {
                // cell_value.remove(Digit_Separator);
                ValueEntry_LineEdit->setText(RemoveDigitGrouping(cell_value));
            }
        }
        else if ((Column == ValueStack_MemoryColumn) &&
                 ((RPNMemory_ButtonPendng == btntypSTO) ||
                  (RPNMemory_ButtonPendng == btntypRCL)))
        {
            char cmdstr[MAXCMD+1+1+1];
            cmdstr[0] = '\0';

            char memreg[32];
            snprintf(memreg, 32, "%d", (ValueStack_RowCount - 1 - Row));
            /* itoa((ValueStack_RowCount - 1 - Row), memreg, 10); */

            char* operand = ValueEntry_LineEdit->text().toLatin1().data();

            if (RPNMemory_ButtonPendng == btntypSTO) {
                if (RPNMemory_OperatorPendng == 0) {
                    if (strlen(operand) > 0) {
                        strcat(cmdstr, "if(1 > 0) {delete(rpnmemory, ");
                        strcat(cmdstr, memreg);
                        strcat(cmdstr, "); insert(rpnmemory, ");
                        strcat(cmdstr, memreg);
                        strcat(cmdstr, ", ");
                        strcat(cmdstr, operand);
                        strcat(cmdstr, ");}");
                    }
                    else {
                        strcat(cmdstr, "if(size(rpnstack)>0) {delete(rpnmemory, ");
                        strcat(cmdstr, memreg);
                        strcat(cmdstr, "); insert(rpnmemory, ");
                        strcat(cmdstr, memreg);
                        strcat(cmdstr, ", rpnstack[0]);}");
                    }
                }
                else
                {
                    if (strlen(operand) > 0) {
                        strcat(cmdstr, "if(1 > 0) insert(rpnmemory, ");
                        strcat(cmdstr, memreg);
                        strcat(cmdstr, ", delete(rpnmemory, ");
                        strcat(cmdstr, memreg);
                        strcat(cmdstr, ") ");
                        if (RPNMemory_OperatorPendng == btntypAdd)
                            strcat(cmdstr, "+");
                        else if (RPNMemory_OperatorPendng == btntypSubtract)
                            strcat(cmdstr, "-");
                        else if (RPNMemory_OperatorPendng == btntypMultiply)
                            strcat(cmdstr, "*");
                        else if (RPNMemory_OperatorPendng == btntypDivide)
                            strcat(cmdstr, "/");
                        strcat(cmdstr, operand);
                        strcat(cmdstr, ");");
                    }
                    else {
                        strcat(cmdstr, "if(size(rpnstack)>0) insert(rpnmemory, ");
                        strcat(cmdstr, memreg);
                        strcat(cmdstr, ", delete(rpnmemory, ");
                        strcat(cmdstr, memreg);
                        strcat(cmdstr, ") ");
                        if (RPNMemory_OperatorPendng == btntypAdd)
                            strcat(cmdstr, "+");
                        else if (RPNMemory_OperatorPendng == btntypSubtract)
                            strcat(cmdstr, "-");
                        else if (RPNMemory_OperatorPendng == btntypMultiply)
                            strcat(cmdstr, "*");
                        else if (RPNMemory_OperatorPendng == btntypDivide)
                            strcat(cmdstr, "/");
                        strcat(cmdstr, "rpnstack[0]);");
                    }
                }
            }
            else if (RPNMemory_ButtonPendng == btntypRCL)
            {
                if (strlen(operand) > 0) {
                    // first push the contents of edit onto stack
                    strcat(cmdstr, "push(rpnstack, ");
                    strcat(cmdstr, operand);
                    strcat(cmdstr, ");");
                    ValueEntry_LineEdit->clear();
                }

                if (RPNMemory_OperatorPendng == 0) {
                    strcat(cmdstr, "push(rpnstack, rpnmemory[");
                    strcat(cmdstr, memreg);
                    strcat(cmdstr, "]);");
                }
                else {
                    strcat(cmdstr, "if(size(rpnstack)>0) push(rpnstack, (pop(rpnstack)");
                    if (RPNMemory_OperatorPendng == btntypAdd)
                        strcat(cmdstr, "+");
                    else if (RPNMemory_OperatorPendng == btntypSubtract)
                        strcat(cmdstr, "-");
                    else if (RPNMemory_OperatorPendng == btntypMultiply)
                        strcat(cmdstr, "*");
                    else if (RPNMemory_OperatorPendng == btntypDivide)
                        strcat(cmdstr, "/");
                    strcat(cmdstr, "rpnmemory[");
                    strcat(cmdstr, memreg);
                    strcat(cmdstr, "]));");
                }
            }

            if (strlen(cmdstr) > 0) ProcessRPN(cmdstr, true);
        }

        RPNMemory_ButtonPendng = 0;
        RPNMemory_OperatorPendng = 0;
        ValueStack_ColumnVisible(ValueStack_StackColumn);
    }
}

void
APCalcClass::ValueStack_PushValue(char* ValueToPush) {
    char* operand = Normalize_ValueEntry(ValueEntry_LineEdit->text()).toLatin1().data();
    char cmdstr[MAXCMD+1+1+1];
    cmdstr[0] = '\0';

    // first, save current stack for possible undo
    strcpy(last_operand, operand);
    strcpy(cmdstr, "free(lastrpnstack);lastrpnstack=rpnstack;");
    if (strlen(operand) > 0) {
        // push the contents of edit onto stack
        strcat(cmdstr, "push(rpnstack, ");
        strcat(cmdstr, operand);
        strcat(cmdstr, ");");
        ValueEntry_LineEdit->clear();
    }

    strcat(cmdstr, "push(rpnstack, ");
    strcat(cmdstr, ValueToPush);
    strcat(cmdstr, ");");

    if (strlen(cmdstr) > 0) ProcessRPN(cmdstr, true);
}

void
APCalcClass::RPNButton_Execute(ButtonDefinition *Execute_Button) {
    int hist_idx = 0;
    char* operand = Normalize_ValueEntry(ValueEntry_LineEdit->text()).toLatin1().data();
    // RemoveDigitGroup(operand);
    char cmdstr[MAXCMD+1+1+1];
    cmdstr[0] = '\0';
    bool save_history_enabled = true;

    Qt::KeyboardModifiers keymod = QApplication::keyboardModifiers();

    switch (Execute_Button->ButtonType)
    {
    case btntypNone: break;

    case btntypChar:
    case btntypBase:
        if (strlen(operand) == 0) {
            if ((keymod & Qt::AltModifier) != 0) {
                if (Execute_Button->ButtonType == btntypBase)
                    ValueEntry_LineEdit->insert("0b");
            }
            else if (strcmp(Execute_Button->Program, "E") == 0)
                ValueEntry_LineEdit->insert("1E");
            else if (strcmp(Execute_Button->Program, "i") == 0)
                ValueEntry_LineEdit->insert("1i");
            else ValueEntry_LineEdit->insert(Execute_Button->Program);
        }
        else ValueEntry_LineEdit->insert(Execute_Button->Program);
        break;
    case btntypRadixMark:
        ValueEntry_LineEdit->insert(Radix_Mark);
        break;
    case btntypDelete:
        if (ValueEntry_LineEdit->selectedText().length() == 0)
            ValueEntry_LineEdit->cursorBackward(true, 1);
        ValueEntry_LineEdit->del();
        break;

    case btntypPush:
        // first, save current stack for possible undo
        strcpy(last_operand, operand);
        strcpy(cmdstr, "free(lastrpnstack);lastrpnstack=rpnstack;");
        if (strlen(operand) > 0) {
            // push the contents of edit onto stack
            strcat(cmdstr, "push(rpnstack, ");
            strcat(cmdstr, operand);
            strcat(cmdstr, ");");
            ValueEntry_LineEdit->clear();
        }
        else strcat(cmdstr, "push(rpnstack, rpnstack[0])");
        break;
    case btntypPop:
        // first, save current stack for possible undo
        strcpy(last_operand, operand);
        strcpy(cmdstr, "free(lastrpnstack);lastrpnstack=rpnstack;");
         // then drop the stack
        strcat(cmdstr, "pop(rpnstack)");
        break;

    case btntypUndo:
        // Old code emulates HP-42s/HP-48
        // ValueEntry_LineEdit->setText(last_operand);
        // strcat(cmdstr,Execute_Button->Program);
        hist_idx = History_Index;
        if (hist_idx > saved_history_count()) hist_idx = hist_idx - 1;

        if (hist_idx == 1) {
            // Restore RPN mode initial state, not recorded in history
            History_Index = 0;
            RPN_RestoreState(cmdstr, NULL);
            save_history_enabled = false;
            break;
        }

        while (hist_idx > 1) {
            // Back up to previous RPN mode state
            hist_idx = hist_idx - 1;
            if (recall_history_mode(hist_idx) == RPN_Mode) {
                History_Index = hist_idx;
                RPN_RestoreState(cmdstr, recall_stack_memory(History_Index));
                save_history_enabled = false;
                break;
            }
        }
        break;

    case btntypRedo:
        // Old code emulates HP-42s/HP-48
        // ValueEntry_LineEdit->setText(last_operand);
        // strcat(cmdstr,Execute_Button->Program);
        hist_idx = History_Index;
        // Forward to next RPN mode state
        while (hist_idx < saved_history_count()) {
            hist_idx = hist_idx + 1;
            if (recall_history_mode(hist_idx) == RPN_Mode) {
                History_Index = hist_idx;
                RPN_RestoreState(cmdstr, recall_stack_memory(History_Index));
                save_history_enabled = false;
                break;
            }
        }
        break;

    // case btntypInvSign:
    case btntypSwap:
        // first, save current stack for possible undo
        strcpy(last_operand, operand);
        strcpy(cmdstr, "free(lastrpnstack);lastrpnstack=rpnstack;");
        if (strlen(operand) > 0) {
            // first push the contents of edit onto stack
            strcat(cmdstr, "push(rpnstack, ");
            strcat(cmdstr, operand);
            strcat(cmdstr, ");");
            ValueEntry_LineEdit->clear();
        }
        strcat(cmdstr, Execute_Button->Program);
        break;

    case btntypProgram:
    case btntypAdd:
    case btntypSubtract:
    case btntypMultiply:
    case btntypDivide:
    case btntypChangeSign:
        if ((RPNMemory_ButtonPendng == 0) ||
            (Execute_Button->ButtonType == btntypProgram))
        {
            // first, save current stack for possible undo
            strcpy(last_operand, operand);
            strcpy(cmdstr, "free(lastrpnstack);lastrpnstack=rpnstack;");
            if (strlen(operand) > 0) {
                // first push the contents of edit onto stack
                strcat(cmdstr, "push(rpnstack, ");
                strcat(cmdstr, operand);
                strcat(cmdstr, ");");
                ValueEntry_LineEdit->clear();
            }
            strcat(cmdstr, Execute_Button->Program);
        }
        else
            RPNMemory_OperatorPendng = Execute_Button->ButtonType;
        break;

    case btntypShift:
        Buttons_Index = (Buttons_Index + 1) % RPN_ButtonSets;
        CalculatorButtons_SetText(Calculator_Mode, Buttons_Index);
        break;
    case btntypSTO:
        if (RPNMemory_ButtonPendng == btntypSTO) {
            RPNMemory_ButtonPendng = 0;
            RPNMemory_OperatorPendng = 0;
            ValueStack_ColumnVisible(ValueStack_StackColumn);
        }
        else {
            RPNMemory_ButtonPendng = btntypSTO;
            ValueStack_ColumnVisible(ValueStack_MemoryColumn);
        }
        break;
    case btntypRCL:
        if (RPNMemory_ButtonPendng == btntypRCL) {
            RPNMemory_ButtonPendng = 0;
            RPNMemory_OperatorPendng = 0;
            ValueStack_ColumnVisible(ValueStack_StackColumn);
        }
        else {
            RPNMemory_ButtonPendng = btntypRCL;
            ValueStack_ColumnVisible(ValueStack_MemoryColumn);
        }
        break;

    default: break;
    }

    if (((Execute_Button->ButtonType == btntypProgram) || (Execute_Button->ButtonType == btntypNone)) &&
        (Buttons_Index > 0)) {
        Buttons_Index = 0;
        CalculatorButtons_SetText(Calculator_Mode, Buttons_Index);
    }

    if (strlen(cmdstr) > 0) ProcessRPN(cmdstr, save_history_enabled);
}

void
APCalcClass::ProcessRPN(char* RPNCommands, bool SaveHistoryEnabled) {
    int err;

    // set_run_state(RUN_TOP_LEVEL);

    if (RPNCommands != NULL) {
        if (strlen(RPNCommands) > 0) {
            userMark = user_mark();

            user_clear();

            (void) openstring(RPNCommands, strlen(RPNCommands));
            err = execute_commands(true);
            closeinput();

            user_flush();
        }
    }

    char ch_stack_memory[MAXCMD+1+1+1];
    ch_stack_memory[0] = '\0';

    RPN_DisplayStackMemory(ch_stack_memory);

    if (SaveHistoryEnabled) {
        save_history_rpn((char *) "", ch_stack_memory);
        History_Index = saved_history_count() + 1;
    }
}

void
APCalcClass::RPN_DisplayStackMemory(char* StackMemory_History) {
    int err;
    int r;
    char* use_str;

    char* cp_stack_memory = StackMemory_History;

    // Process RPN Stack
    userMark = user_mark();

    char PrintRPNStack[] = "forall(rpnstack, \"PrintRPN\")";

    user_clear();

    (void) openstring(PrintRPNStack, strlen(PrintRPNStack));
    err = execute_commands(true);
    closeinput();

    user_flush();

    // Value Stack Values
    for (r = 1; r <= ValueStack_RowCount; r++)
        ValueStack_setCellText(r, ValueStack_StackColumn, (char*) "");

    if (cp_stack_memory != NULL)
        strcat(cp_stack_memory, "free(rpnstack);rpnstack=list();\n");

    if (user_count(std_out, userMark) > 0) {
        if (cp_stack_memory != NULL) {
            for (r = user_count(std_out, userMark); r > ValueStack_RowCount; r--) {
                use_str = user_return_line(std_out, userMark, (r - 1));
                use_str = str_trim(use_str);
                use_str = str_skipchar(use_str, '~');
                use_str = str_skipspace(use_str);

                strcat(cp_stack_memory, "push(rpnstack, ");
                strcat(cp_stack_memory, use_str);
                strcat(cp_stack_memory, ");\n");

                free(use_str);
            }
        }

        for (r = ValueStack_RowCount; r >= 1; r--) {
            if (r <= user_count(std_out, userMark)) {
                use_str = user_return_line(std_out, userMark, (r - 1));
                use_str = str_trim(use_str);
                use_str = str_skipchar(use_str, '~');
                use_str = str_skipspace(use_str);

                QString display_operand = DisplayValue(use_str);
                display_operand = display_operand.trimmed();
                ValueStack_setCellText
                  ((ValueStack_RowCount - r + 1), ValueStack_StackColumn,
                   display_operand); // display_operand.toLatin1().data()

                if (cp_stack_memory != NULL) {
                    strcat(cp_stack_memory, "push(rpnstack, ");
                    strcat(cp_stack_memory, use_str);
                    strcat(cp_stack_memory, ");\n");
                }

                free(use_str);
            }
        }
    }

    // Process RPN Memory
    userMark = user_mark();

    char PrintRPNMemory[] = "forall(rpnmemory, \"PrintRPN\")";

    user_clear();

    (void) openstring(PrintRPNMemory, strlen(PrintRPNMemory));
    err = execute_commands(true);
    closeinput();

    user_flush();

    // Memory Register Values
    for (r = 1; r <= ValueStack_RowCount; r++)
        ValueStack_setCellText(r, ValueStack_MemoryColumn, (char*) "");

    if (cp_stack_memory != NULL) {
        strcat(cp_stack_memory, "\n");
        strcat(cp_stack_memory, "free(rpnmemory);rpnmemory = list(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);\n");
    }

    int mem_reg = 0;
    char str_memreg[32];

    if (user_count(std_out, userMark) > 0) {
        for (r = ValueStack_RowCount; r >= 1; r--) {
            if (r <= user_count(std_out, userMark)) {
                use_str = user_return_line(std_out, userMark, (r - 1));
                use_str = str_trim(use_str);
                use_str = str_skipchar(use_str, '~');
                use_str = str_skipspace(use_str);
                QString display_operand = DisplayValue(use_str);
                display_operand = display_operand.trimmed();
                ValueStack_setCellText
                  ((ValueStack_RowCount - r + 1), ValueStack_MemoryColumn,
                   display_operand); // display_operand.toLatin1().data()

                if (cp_stack_memory != NULL) {
                    snprintf(str_memreg, 32, "%d", (ValueStack_RowCount - 1 - mem_reg));
                    /* itoa((ValueStack_RowCount - 1 - mem_reg), str_memreg, 10); */
                    strcat(cp_stack_memory, "{delete(rpnmemory, ");
                    strcat(cp_stack_memory, str_memreg);
                    strcat(cp_stack_memory, "); insert(rpnmemory, ");
                    strcat(cp_stack_memory, str_memreg);
                    strcat(cp_stack_memory, ", ");
                    strcat(cp_stack_memory, use_str);
                    strcat(cp_stack_memory, ");};\n");
                    mem_reg = mem_reg + 1;
                }

                free(use_str);
            }
        }
    }
}

void
APCalcClass::RPN_RestoreState(char* Command_String, char* Restore_Stack_Memory) {
    char* cmdstr = Command_String;

    if (Restore_Stack_Memory == NULL) {
        strcat(cmdstr, "free(rpnstack);rpnstack=list();");
        strcat(cmdstr, "free(rpnmemory);rpnmemory = list(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);");

    }
    else strcat(cmdstr, Restore_Stack_Memory);

    return;
}

//# ⇧ Shift
//# ⌃	Control (modifiers & Qt::MetaModifier)
//# ⌥	Option (Alt, Alternative) (modifiers & Qt::AltModifier)
//# ⌘	Command (modifiers & Qt::ControlModifier)
//# ⏎ ↩ Return
//# ⏏	Eject

void
APCalcClass::RPN_keyPressed(int Key) {
    Qt::KeyboardModifiers keymod = QApplication::keyboardModifiers();
    if ((keymod & Qt::ControlModifier) ||
        (keymod & Qt::AltModifier)) {
        if (Key == Qt::Key_C) {
            QString result;

            // If ValueEntry has selected text, get that text
            result = ValueEntry_LineEdit->selectedText();
            if (result.length() == 0) {
                // Otherwise, get the content of the bottom stack entry
                result = ValueStack_CellText
                             (ValueStack_RowCount, ValueStack_StackColumn);
            }

            if (keymod & Qt::AltModifier) result = RemoveDigitGrouping(result);

            // And put on clipboard
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(result);
        }
        else if (Key == Qt::Key_V) {
            QClipboard *clipboard = QApplication::clipboard();
            // Clean up clipboard text, eliminate "illegal" characters
            clipboard->setText(RemoveDigitGrouping(clipboard->text().trimmed()));
        }
    }
    else if (Key == Qt::Key_Plus)
        RPN_AdHocExecute(btntypAdd);
    else if (Key == Qt::Key_Underscore)
        // Tricky because minus can start a decimal number or a negative exponent
        RPN_AdHocExecute(btntypSubtract);
    else if (Key == Qt::Key_Asterisk)
        RPN_AdHocExecute(btntypMultiply);
    else if (Key == Qt::Key_Slash)
        RPN_AdHocExecute(btntypDivide);
    else if (Key == Qt::Key_Equal)
        RPN_AdHocExecute(btntypChangeSign);
    else if (Key == Qt::Key_Return) {
        /* if (ValueEntry_LineEdit->text().length() <= 0) ??? Why ??? */
            RPN_AdHocExecute(btntypPush);
    }
}

void
APCalcClass::RPN_ValueEntry_textChanged(QString newText) {
    LineEdit_textChanged(ValueEntry_LineEdit, newText);
}

void
APCalcClass::LineEdit_textChanged(QLineEdit *LineEdit, QString newText) {
    static BOOL in_process = false;

    if (in_process) return;
    if (Suppress_DigitGrouping) return;

    in_process = true;

    QString val = newText;
    QChar pos_chr = '\0';
    int pos = LineEdit->cursorPosition();
    if (pos < val.length()) {
        pos_chr = val[pos];
        while ((pos < val.length()) &&
               IsDigitGroupingCharacter(pos_chr)) {
            /* ensure that selection position is not on a digit separator */
            pos = pos + 1;
            pos_chr = val[pos];
        }
        /* For digit grouping selection placeholder, digits ... */
        /* ... and radix marks (or E, etc.) treated differently. */
        /* All such non-digits terminate digit grouping, which ... */
        /* only applies to the integral portion of the decimal value. */
        if (((pos_chr >= ('0')) && (pos_chr <= ('9'))) ||
            ((val.startsWith("0x") || val.startsWith("0X")) &&
             (((pos_chr >= ('a')) && (pos_chr <= ('f'))) ||
              ((pos_chr >= ('A')) && (pos_chr <= ('F')))))) {
            val[pos] = '|';
            pos_chr = pos_chr.toUpper();
        }
        else
            val[pos] = '^';
    }

    val = DigitGroup(RemoveDigitGrouping(val));

    if (pos_chr != '\0') {
        pos = 0;
        while (val[pos] != '\0') {
            if ((val[pos] == '|') || (val[pos] == '^')) {
                val[pos] = pos_chr;
                break;
            }
            pos = pos + 1;
        }
        LineEdit->setText(val);
        LineEdit->setCursorPosition(pos);
    }
    else LineEdit->setText(val);

    in_process = false;

    return;
}
