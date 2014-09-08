#include "pollster_window.h"

#include "construtcor_page.h"
#include "choice_survey_dialog.h"
#include <QMessageBox>

pollster_window::pollster_window(QString _owner, QWidget *parent) :
    QMainWindow(parent), owner (_owner)
{
    survey_list = db->get_survey_list (owner);
    ExtendedTabWidget *tab_widget = new ExtendedTabWidget (this);
    tab_widget->addPage(new construtcor_page, QIcon (), "Constructor");
    tab_widget->addPage(new QWidget, QIcon (), "Answers table");
    tab_widget->addPage(new QWidget, QIcon (), "Diagrams");
    this->setCentralWidget (tab_widget);
    choice_survey_dialog *choice = new choice_survey_dialog (&survey_list);
    QObject::connect (choice, SIGNAL (choice_done(QString)), this, SLOT (set_survey(QString)));
    choice->exec();
}

void pollster_window::set_survey(QString survey)
{
    if (survey == "...create new survey...")

    cur_survey = survey;
}
