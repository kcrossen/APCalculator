#ifndef PLAINTEXTEDIT_H
#define PLAINTEXTEDIT_H

#include <QPlainTextEdit>
#include <QKeyEvent>

class PlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit PlainTextEdit(QWidget *parent = 0);

    QString text();

    QChar TextCursorIndicator();
    void insertTextCursorIndicator();
    void removeTextCursorIndicator();

signals:
    void keyPressed(int Key);
    void focusIn();
    void focusOut();
    void PlainTextChanged();

public slots:

private slots:
    void Private_textChanged();

protected:
    void keyPressEvent(QKeyEvent *event);

    void focusInEvent (QFocusEvent *event);
    void focusOutEvent (QFocusEvent *event);

};

#endif // PLAINTEXTEDIT_H
