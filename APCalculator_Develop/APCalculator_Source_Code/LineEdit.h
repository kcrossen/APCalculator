#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEdit(QWidget *parent = 0);

signals:
void keyPressed(int Key);
void gotFocus();

public slots:

protected:
void keyPressEvent(QKeyEvent *event);
void focusInEvent (QFocusEvent *event);

};

#endif // LINEEDIT_H
