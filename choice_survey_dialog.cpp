#include "choice_survey_dialog.h"
#include "ui_choice_survey_dialog.h"

choice_survey_dialog::choice_survey_dialog(QStringList *surveys, QWidget *parent) :
    QDialog(parent), ui(new Ui::choice_survey_dialog)
{
    this->setModal(true);
    ui->setupUi(this);
    QStringListIterator it (*surveys);
    while (it.hasNext())
        ui->survey_list->addItem(it.next());
    ui->survey_list->addItem("...create new survey...");

    QObject::connect(ui->survey_list, SIGNAL (itemDoubleClicked(QListWidgetItem*)), this, SLOT (on_choice_done (QListWidgetItem*)));
}

void choice_survey_dialog::on_choice_done(QListWidgetItem *item)
{
    emit choice_done(item->text());
    this->close();
}

choice_survey_dialog::~choice_survey_dialog()
{
    delete ui;
}
