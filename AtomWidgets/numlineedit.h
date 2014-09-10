#ifndef NUMLINEEDIT_H
#define NUMLINEEDIT_H

#include <QLineEdit>
#include <QRegExp>

class NumLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit NumLineEdit (QWidget *parent = 0);

    bool isInt ();
    bool isReal ();
    bool isPositive ();
};

#endif // NUMLINEEDIT_H
