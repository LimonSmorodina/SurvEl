#include "numlineedit.h"

NumLineEdit::NumLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    QRegExp rxp ("^[\+\-]?[0-9]+($|\.[0-9]+$)");
    setValidator(new QRegExpValidator(rxp, this));
}

bool NumLineEdit::isInt()
{
    QRegExp rxp (".");
    rxp.indexIn (this->text());
    return rxp.captureCount() == 0;
}

bool NumLineEdit::isReal()
{
    QRegExp rxp (".");
    rxp.indexIn (this->text());
    return rxp.captureCount() == 1;
}

bool NumLineEdit::isPositive()
{
    QRegExp rxp ("^[\+0-9]");
    rxp.indexIn (this->text());
    return rxp.captureCount() == 1;
}
