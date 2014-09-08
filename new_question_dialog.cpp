#include "new_question_dialog.h"
#include "ui_new_question_dialog.h"

#include <QLineEdit>

new_question_dialog::new_question_dialog(int _page, int _pos, QWidget *parent) :
    QDialog(parent), ui(new Ui::new_question_dialog)
{
    answers_count = 0;
    result = 0;
    page = _page;
    pos = _pos;

    ui->setupUi(this);
    ui->qustion_type_box->addItem ("Numerical answer");
    ui->qustion_type_box->addItem ("Text answer");
    ui->qustion_type_box->addItem ("Choose from set (one answer)");
    ui->qustion_type_box->addItem ("Choose from set (many answers)");

    ui->done_button->setEnabled(false);

    QObject::connect (ui->qustion_type_box, SIGNAL (activated(int)), this, SLOT (init_answers_layout(int)));
    QObject::connect (ui->done_button, SIGNAL (clicked()), this, SLOT (construct_done()));

    QObject::connect (ui->done_button, SIGNAL (clicked()), this, SLOT (close()));
    QObject::connect (ui->cancel_button, SIGNAL (clicked()), this, SLOT (close()));
}

new_question_dialog::~new_question_dialog()
{
    delete ui;
}

void new_question_dialog::init_answers_layout(int type)
{
    clearLayout (ui->answers_layout);

    ui->done_button->setEnabled(true);
    this->type = type;

    if ((type == SET_QUESTION) || (type == ENUM_QUESTION))
    {
        add_answer_variant ();
        QPushButton *add_var_button = new QPushButton ("Add answer");
        QObject::connect (add_var_button, SIGNAL (clicked()), this, SLOT (add_answer_variant()));
        ui->answers_layout->addWidget (add_var_button);
    }
}

void new_question_dialog::add_answer_variant ()
{
    answers_count++;
    true_HBoxLayout *answer_layout = new true_HBoxLayout;
    QPushButton *delete_button = new QPushButton ("Delete");
    text_answer_edit *variant = new text_answer_edit ();

    QObject::connect (delete_button, SIGNAL (clicked()), answer_layout, SLOT (clear_and_delete()));
    QObject::connect (variant, SIGNAL (cursorPositionChanged (int, int)), variant, SLOT (if_focused()));

    variants << variant;
    answer_layout->addWidget (delete_button);
    answer_layout->addWidget (variant);
    ui->answers_layout->insertLayout (ui->answers_layout->count()-1, answer_layout);
}

void new_question_dialog::delete_answer(QHBoxLayout *lay)
{
    clearLayout (lay);
    delete lay;
}

void new_question_dialog::construct_done ()
{
    switch (type)
    {
    case TEXT_QUESTION:
        result = new text_question (ui->wording_edit->toPlainText(), page, pos, false);
        break;
    case SET_QUESTION:
    {
        set_question *temp = new set_question (ui->wording_edit->toPlainText(), page, pos, false);
        QListIterator<text_answer_edit*> it (variants);
        while (it.hasNext())
            temp->add_variant (it.next()->text());
        result = temp;
        break;}
    case ENUM_QUESTION:
    {
        enum_question *temp = new enum_question (ui->wording_edit->toPlainText(), page, pos, false);
        QListIterator<text_answer_edit*> it (variants);
        while (it.hasNext())
            temp->add_variant (it.next()->text());
        result = temp;
        result = temp;
        break;}
    }
    emit question_constructed(result);
}
