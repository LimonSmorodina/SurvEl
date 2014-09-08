#ifndef CHOICE_SURVEY_DIALOG_H
#define CHOICE_SURVEY_DIALOG_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class choice_survey_dialog;
}

class choice_survey_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit choice_survey_dialog(QStringList *surveys, QWidget *parent = 0);
    ~choice_survey_dialog();
signals:
    void choice_done (QString);
private slots:
    void on_choice_done (QListWidgetItem*);
private:
    Ui::choice_survey_dialog *ui;
};

#endif // CHOICE_SURVEY_DIALOG_H
