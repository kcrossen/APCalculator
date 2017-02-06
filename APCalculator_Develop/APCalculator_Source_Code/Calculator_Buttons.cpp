#include "Calculator_UI.h"
#include "ButtonDefinitions.h"

void
APCalcClass::RPN_ValueEntry_returnPressed() {
    RPN_AdHocExecute(btntypPush);
}

void
APCalcClass::RPN_AdHocExecute(APCalc_ButtonType Execute_ButtonType) {
    ButtonDefinition *btndef = NULL;
    for (int b = 0;
         ((RPNButtons_A[b].Row >= 0) && (RPNButtons_A[b].Column >= 0));
         b++) {
        if (RPNButtons_A[b].ButtonType == Execute_ButtonType) {
            btndef = (ButtonDefinition*) &RPNButtons_A[b];
            RPNButton_Execute(btndef);
            return;
        }
    }
    for (int b = 0;
         ((RPNButtons_B[b].Row >= 0) && (RPNButtons_B[b].Column >= 0));
         b++) {
        if (RPNButtons_B[b].ButtonType == Execute_ButtonType) {
            btndef = (ButtonDefinition*) &RPNButtons_B[b];
            RPNButton_Execute(btndef);
            return;
        }
    }
}

void
APCalcClass::Algebraic_AdHocEvaluate() {
    Algebraic_AdHocExecute(btntypEval);
}

void
APCalcClass::Algebraic_AdHocExecute(APCalc_ButtonType Execute_ButtonType) {
    ButtonDefinition *btndef = NULL;
    for (int b = 0;
         ((AlgebraicButtons_A[b].Row >= 0) && (AlgebraicButtons_A[b].Column >= 0));
         b++) {
        if (AlgebraicButtons_A[b].ButtonType == Execute_ButtonType) {
            btndef = (ButtonDefinition*) &AlgebraicButtons_A[b];
            Algebraic_ButtonExecute(btndef);
            return;
        }
    }
}

void
APCalcClass::Program_AdHocEvaluate() {
    Program_AdHocExecute(btntypEval);
}

void
APCalcClass::Program_AdHocExecute(APCalc_ButtonType Execute_ButtonType) {
    ButtonDefinition *btndef = NULL;
    for (int b = 0;
         ((ProgramButtons_A[b].Row >= 0) && (ProgramButtons_A[b].Column >= 0));
         b++) {
        if (ProgramButtons_A[b].ButtonType == Execute_ButtonType) {
            btndef = (ButtonDefinition*) &ProgramButtons_A[b];
            Program_ButtonExecute(btndef);
            break;
        }
    }
}

void
APCalcClass::Button_Execute(APCalc_Calculator_Mode Mode, int Buttons_Index, int Row, int Column) {
    ButtonDefinition *btndef = NULL;
    switch (Mode) {
    case RPN_Mode:
        switch (Buttons_Index) {
        case 0:
            for (int b = 0;
                 ((RPNButtons_A[b].Row >= 0) && (RPNButtons_A[b].Column >= 0));
                 b++)
                if ((RPNButtons_A[b].Row == Row) && (RPNButtons_A[b].Column == Column)) {
                    btndef = (ButtonDefinition*) &RPNButtons_A[b];
                    break;
                }
            break;
        case 1:
            for (int b = 0;
                 ((RPNButtons_B[b].Row >= 0) && (RPNButtons_B[b].Column >= 0));
                 b++)
                if ((RPNButtons_B[b].Row == Row) && (RPNButtons_B[b].Column == Column)) {
                    btndef = (ButtonDefinition*) &RPNButtons_B[b];
                    break;
                }
            break;
        }
        RPNButton_Execute(btndef);
        break;

    case Algebraic_Mode:
    case Algebraic_Interactive_Mode:
        switch (Buttons_Index) {
        case 0:
            for (int b = 0;
                 ((AlgebraicButtons_A[b].Row >= 0) && (AlgebraicButtons_A[b].Column >= 0));
                 b++)
                if ((AlgebraicButtons_A[b].Row == Row) && (AlgebraicButtons_A[b].Column == Column)) {
                    btndef = (ButtonDefinition*) &AlgebraicButtons_A[b];
                    break;
                }
            break;
        case 1:
            for (int b = 0;
                 ((AlgebraicButtons_B[b].Row >= 0) && (AlgebraicButtons_B[b].Column >= 0));
                 b++)
                if ((AlgebraicButtons_B[b].Row == Row) && (AlgebraicButtons_B[b].Column == Column)) {
                    btndef = (ButtonDefinition*) &AlgebraicButtons_B[b];
                    break;
                }
            break;
        case 2:
            for (int b = 0;
                 ((AlgebraicButtons_C[b].Row >= 0) && (AlgebraicButtons_C[b].Column >= 0));
                 b++)
                if ((AlgebraicButtons_C[b].Row == Row) && (AlgebraicButtons_C[b].Column == Column)) {
                    btndef = (ButtonDefinition*) &AlgebraicButtons_C[b];
                    break;
                }
            break;
        }
        Algebraic_ButtonExecute(btndef);
        break;

    case Program_Mode:
        switch (Buttons_Index) {
        case 0:
            for (int b = 0;
                 ((ProgramButtons_A[b].Row >= 0) && (ProgramButtons_A[b].Column >= 0));
                 b++)
                if ((ProgramButtons_A[b].Row == Row) && (ProgramButtons_A[b].Column == Column)) {
                    btndef = (ButtonDefinition*) &ProgramButtons_A[b];
                    break;
                }
            break;
        case 1:
            for (int b = 0;
                 ((ProgramButtons_B[b].Row >= 0) && (ProgramButtons_B[b].Column >= 0));
                 b++)
                if ((ProgramButtons_B[b].Row == Row) && (ProgramButtons_B[b].Column == Column)) {
                    btndef = (ButtonDefinition*) &ProgramButtons_B[b];
                    break;
                }
            break;
        case 2:
            for (int b = 0;
                 ((ProgramButtons_C[b].Row >= 0) && (ProgramButtons_C[b].Column >= 0));
                 b++)
                if ((ProgramButtons_C[b].Row == Row) && (ProgramButtons_C[b].Column == Column)) {
                    btndef = (ButtonDefinition*) &ProgramButtons_C[b];
                    break;
                }
            break;
        }
        Program_ButtonExecute(btndef);
        break;
    }
}

void
APCalcClass::CalculatorButtons_SetText(APCalc_Calculator_Mode Mode, int Buttons_Index) {
    switch (Mode) {
    case RPN_Mode:
        switch (Buttons_Index) {
        case 0:
            for (int b = 0;
                 ((RPNButtons_A[b].Row >= 0) && (RPNButtons_A[b].Column >= 0));
                 b++)
                Button_SetText(RPNButtons_A[b].Row,
                               RPNButtons_A[b].Column,
                               RPNButtons_A[b].ButtonType,
                               RPNButtons_A[b].Text,
                               RPNButtons_A[b].ToolTip);
            break;

        case 1:
            for (int b = 0;
                 ((RPNButtons_B[b].Row >= 0) && (RPNButtons_B[b].Column >= 0));
                 b++)
                Button_SetText(RPNButtons_B[b].Row,
                               RPNButtons_B[b].Column,
                               RPNButtons_B[b].ButtonType,
                               RPNButtons_B[b].Text,
                               RPNButtons_B[b].ToolTip);
            break;
        }
        break;

    case Algebraic_Mode:
    case Algebraic_Interactive_Mode:
        switch (Buttons_Index) {
        case 0:
            for (int b = 0;
                 ((AlgebraicButtons_A[b].Row >= 0) && (AlgebraicButtons_A[b].Column >= 0));
                 b++)
                Button_SetText(AlgebraicButtons_A[b].Row,
                               AlgebraicButtons_A[b].Column,
                               AlgebraicButtons_A[b].ButtonType,
                               AlgebraicButtons_A[b].Text,
                               AlgebraicButtons_A[b].ToolTip);
            break;

        case 1:
            for (int b = 0;
                 ((AlgebraicButtons_B[b].Row >= 0) && (AlgebraicButtons_B[b].Column >= 0));
                 b++)
                Button_SetText(AlgebraicButtons_B[b].Row,
                               AlgebraicButtons_B[b].Column,
                               AlgebraicButtons_B[b].ButtonType,
                               AlgebraicButtons_B[b].Text,
                               AlgebraicButtons_B[b].ToolTip);
            for (int r = 1; r <= Algebraic_ButtonRows; r++)
                Button_SetText(r, 7, btntypNone, (char*) "", (char*) "");
            break;

        case 2:
            for (int b = 0;
                 ((AlgebraicButtons_C[b].Row >= 0) && (AlgebraicButtons_C[b].Column >= 0));
                 b++)
                Button_SetText(AlgebraicButtons_C[b].Row,
                               AlgebraicButtons_C[b].Column,
                               AlgebraicButtons_C[b].ButtonType,
                               AlgebraicButtons_C[b].Text,
                               AlgebraicButtons_C[b].ToolTip);
            for (int r = 1; r <= Algebraic_ButtonRows; r++)
                Button_SetText(r, 7, btntypNone, (char*) "", (char*) "");
            break;
        }
        break;

    case Program_Mode:
        switch (Buttons_Index) {
        case 0:
            for (int b = 0;
                 ((ProgramButtons_A[b].Row >= 0) && (ProgramButtons_A[b].Column >= 0));
                 b++)
                Button_SetText(ProgramButtons_A[b].Row,
                               ProgramButtons_A[b].Column,
                               ProgramButtons_A[b].ButtonType,
                               ProgramButtons_A[b].Text,
                               ProgramButtons_A[b].ToolTip);
            break;

        case 1:
            for (int b = 0;
                 ((ProgramButtons_B[b].Row >= 0) && (ProgramButtons_B[b].Column >= 0));
                 b++)
                Button_SetText(ProgramButtons_B[b].Row,
                               ProgramButtons_B[b].Column,
                               ProgramButtons_B[b].ButtonType,
                               ProgramButtons_B[b].Text,
                               ProgramButtons_B[b].ToolTip);
            break;

        case 2:
            for (int b = 0;
                 ((ProgramButtons_C[b].Row >= 0) && (ProgramButtons_C[b].Column >= 0));
                 b++)
                Button_SetText(ProgramButtons_C[b].Row,
                               ProgramButtons_C[b].Column,
                               ProgramButtons_C[b].ButtonType,
                               ProgramButtons_C[b].Text,
                               ProgramButtons_C[b].ToolTip);
            break;
        }
        break;
    }

}

QToolButton* APCalc_Button[ButtonRows][ButtonColumns];

void APCalcClass::CreateButtons() {
    for (int r = 1; r <= ButtonRows; r++) {
        for (int c = 1; c <= ButtonColumns; c++) {
            APCalc_Button[r - 1][c - 1] = createToolButton(r, c);
        }
    }

}

QToolButton* APCalcClass::createToolButton(const int Row, const int Column) {
    QToolButton *button = new QToolButton(this);
    QString text;
    text.setNum((10 * Row) + Column);
    button->setText(text);
    button->setMinimumWidth(45);
    button->setMinimumHeight(APCalculator_ButtonHeight);
    button->setMaximumHeight(APCalculator_ButtonHeight);
    button->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    button->setObjectName(text);
    connect(button, SIGNAL(clicked()), this,  SLOT(Clicked_Button()));
    return button;
}

void APCalcClass::Clicked_Button () {
    QToolButton *button = (QToolButton*) sender();
    int btn_idx = button->objectName().toInt();
    Button_Execute(Calculator_Mode, Buttons_Index, (btn_idx / 10) , (btn_idx % 10));
}

QGridLayout *APCalcClass::RPNButtons_GridLayout() {
    QGridLayout *buttons_GridLayout = new QGridLayout();
    buttons_GridLayout->setContentsMargins(0, 0, 0, 0);
    buttons_GridLayout->setSpacing(1);

    for (int r = 1; r <= RPN_ButtonRows; r++) {
        for (int c = 1; c <= RPN_ButtonColumns; c++) {
            buttons_GridLayout->addWidget(APCalc_Button[r - 1][c - 1], (r - 1), (c - 1));
        }
    }

    return buttons_GridLayout;
}

QGridLayout *APCalcClass::AlgebraicButtons_GridLayout() {
    QGridLayout *buttons_GridLayout = new QGridLayout();
    buttons_GridLayout->setContentsMargins(0, 0, 0, 0);
    buttons_GridLayout->setSpacing(1);

    for (int r = 1; r <= Algebraic_ButtonRows; r++) {
        for (int c = 1; c <= Algebraic_ButtonColumns; c++) {
            buttons_GridLayout->addWidget(APCalc_Button[r - 1][c - 1], (r - 1), (c - 1));
        }
    }

    return buttons_GridLayout;
}

QGridLayout *APCalcClass::ProgramButtons_GridLayout() {
    QGridLayout *buttons_GridLayout = new QGridLayout();
    buttons_GridLayout->setContentsMargins(0, 0, 0, 0);
    buttons_GridLayout->setSpacing(1);

    for (int r = 1; r <= Program_ButtonRows; r++) {
        for (int c = 1; c <= Program_ButtonColumns; c++) {
            buttons_GridLayout->addWidget(APCalc_Button[r - 1][c - 1], (r - 1), (c - 1));
        }
    }

    return buttons_GridLayout;
}

void APCalcClass::Button_SetText(int Row, int Column, int Type, QString Text, char* ToolTip) {
    QToolButton *tbtn = APCalc_Button[Row - 1][Column - 1];

    if (tbtn != NULL) {
        if (Type == btntypRadixMark) tbtn->setText(Radix_Mark);
        else tbtn->setText(Text);
        QFont fnt = tbtn->font();
#ifdef Q_OS_MAC
        fnt.setPointSize(Button_FontSize);
        fnt.setBold(not ((Type == btntypChar) ||
                         /* (Type == btntypRadixMark) || */
                         (Type == btntypDelete)));
#endif
        fnt.setItalic((Type == btntypProgram) || (Type == btntypFunction));
        tbtn->setFont(fnt);
        tbtn->setVisible(Text.length() > 0);
        tbtn->setToolTip(ToolTip);
    }
}
