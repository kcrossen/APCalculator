#include "PlainTextEdit.h"

PlainTextEdit::PlainTextEdit(QWidget *parent) :
    QPlainTextEdit(parent)
{
    connect(this, SIGNAL(textChanged()), this, SLOT(Private_textChanged()));
}

#define QChar_TextCursorIndicator QChar(0x25b2)

QString
PlainTextEdit::text() {
    return QPlainTextEdit::toPlainText().remove(QChar_TextCursorIndicator);
}

static bool Suppress_PlainTextChanged = false;
void
PlainTextEdit::Private_textChanged() {
    if (Suppress_PlainTextChanged) return;
    emit PlainTextChanged();
}

void
PlainTextEdit::keyPressEvent(QKeyEvent *event) {
    emit keyPressed(event->key());
    QPlainTextEdit::keyPressEvent(event);
}

void
PlainTextEdit::focusInEvent(QFocusEvent *event) {
    if (event->reason() == Qt::MouseFocusReason) emit focusIn();
    QPlainTextEdit::focusInEvent(event);
    removeTextCursorIndicator();
}

void
PlainTextEdit::focusOutEvent(QFocusEvent *event) {
    if (event->reason() == Qt::MouseFocusReason) emit focusOut();
    QPlainTextEdit::focusOutEvent(event);
    insertTextCursorIndicator();
}

QChar
PlainTextEdit::TextCursorIndicator() {
    return QChar_TextCursorIndicator;
}

void
PlainTextEdit::insertTextCursorIndicator() {
    Suppress_PlainTextChanged = true;
    if (QPlainTextEdit::toPlainText().length() > 0) {
        QPlainTextEdit::insertPlainText(QChar_TextCursorIndicator);
        QPlainTextEdit::moveCursor(QTextCursor::Left, QTextCursor::KeepAnchor);
    }
    Suppress_PlainTextChanged = false;
}

void
PlainTextEdit::removeTextCursorIndicator() {
    Suppress_PlainTextChanged = true;
    QTextCursor txtcur = QPlainTextEdit::textCursor();
    QPlainTextEdit::moveCursor(QTextCursor::End);
    if (QPlainTextEdit::find(QChar_TextCursorIndicator, QTextDocument::FindBackward))
        QPlainTextEdit::insertPlainText("");
    else QPlainTextEdit::setTextCursor(txtcur);
    Suppress_PlainTextChanged = false;
}
