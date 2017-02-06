#include "LineEdit.h"

LineEdit::LineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void
LineEdit::keyPressEvent(QKeyEvent *event) {
    emit keyPressed(event->key());
    QLineEdit::keyPressEvent(event);
}

void
LineEdit::focusInEvent(QFocusEvent *event) {
    if (event->reason() == Qt::MouseFocusReason) emit gotFocus();
    QLineEdit::focusInEvent(event);
}
