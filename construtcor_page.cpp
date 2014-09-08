#include "construtcor_page.h"
#include "ui_construtcor_page.h"

#include "new_question_dialog.h"
#include "global_func.h"
#include <QMessageBox>

construtcor_page::construtcor_page(QWidget *parent) :
    QWidget(parent), ui(new Ui::construtcor_page)
{
    ui->setupUi(this);

    page_list << new QList<abstract_question*>;
    cur_page = 0;
    on_page_change();

    QObject::connect (ui->add_question_button, SIGNAL (clicked()), this, SLOT (create_new_question()));
    QObject::connect (ui->next_page_button, SIGNAL (clicked()), this, SLOT (next_page()));
    QObject::connect (ui->prev_page_button, SIGNAL (clicked()), this, SLOT (prev_page()));
    QObject::connect (ui->add_page_button, SIGNAL (clicked()), this, SLOT (create_new_page()));
    QObject::connect (ui->delete_page_button, SIGNAL (clicked()), this, SLOT (delete_cur_page()));
}

construtcor_page::~construtcor_page()
{
    delete ui;
}

void construtcor_page::change_page (int direction)
{
    clearLayout (ui->questions_layout);

    if (direction == NEXT)
        cur_page++;
    else
        cur_page--;

    QListIterator<abstract_question*> it (*page_list[cur_page]);
    while (it.hasNext())
        ui->questions_layout->addWidget(it.next()->get_copy());

    on_page_change();
}

int construtcor_page::construct_done ()
{
    return 0;
}

void construtcor_page::on_page_change ()
{
    ui->num_question_label->setText("Page " + QString::number(cur_page+1) + " of " + QString::number(page_list.count()));
    ui->next_page_button->setEnabled(cur_page-(page_list.count()-1));
    ui->prev_page_button->setEnabled(cur_page > 0);
}

void construtcor_page::create_new_page ()
{
    clearLayout (ui->questions_layout);
    ui->delete_page_button->setEnabled(true);

    page_list.insert(++cur_page, new QList<abstract_question*>);

    on_page_change();
}

void construtcor_page::delete_cur_page ()
{
    if (cur_page == 0)
    {
        change_page (NEXT);
        page_list.removeAt(--cur_page);
    }
    else
    {
        change_page (PREV);
        page_list.removeAt(cur_page+1);
    }

    ui->delete_page_button->setEnabled (page_list.count() > 1);
    on_page_change();
}

void construtcor_page::create_new_question ()
{
    new_question_dialog *dialog = new new_question_dialog (cur_page, page_list[cur_page]->count());
    QObject::connect (dialog, SIGNAL (question_constructed(abstract_question*)), this, SLOT (add_question(abstract_question*)));
    dialog->show();
}

void construtcor_page::add_question(abstract_question *new_quest)
{
    page_list[cur_page]->push_back (new_quest);
    ui->questions_layout->addWidget (new_quest->get_copy());
}
