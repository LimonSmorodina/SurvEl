#ifndef POLLSTER_WINDOW_H
#define POLLSTER_WINDOW_H

#include <QMainWindow>
#include "extended_tab_widget.h"
#include <QString>

class pollster_window : public QMainWindow
{
    Q_OBJECT
public:
    explicit pollster_window (QString _owner, QWidget *parent = 0);

signals:

public slots:
    void set_survey (QString);
private:
    QString owner;
    QString cur_survey;
    QStringList survey_list;
};

#endif // POLLSTER_WINDOW_H
