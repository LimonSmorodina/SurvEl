#ifndef NEW_QUESTION_DIALOG_H
#define NEW_QUESTION_DIALOG_H

#include <QDialog>

#include "data_base.h"
#include "constructor_frames.h"
#include "global_func.h"

#define DEFAULT_ANSWER_TEXT "Type answer..."

class true_HBoxLayout: public QHBoxLayout
{
    Q_OBJECT
public:
    true_HBoxLayout (): QHBoxLayout () {}
public slots:
    void clear_and_delete () {clearLayout(this); delete this;}
};

class text_answer_edit: public QLineEdit
{
    Q_OBJECT
public:
   text_answer_edit (): QLineEdit (DEFAULT_ANSWER_TEXT) {}
public slots:
    void if_focused () {if (this->text() == DEFAULT_ANSWER_TEXT) this->setText("");}
};

namespace Ui {
class new_question_dialog;
}

class new_question_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit new_question_dialog(int _page, int _pos, QWidget *parent = 0);
    ~new_question_dialog();

    inline abstract_question* get_result () {return result;}
private slots:
    void add_answer_variant ();
    void init_answers_layout (int);
    void construct_done ();
    void delete_answer (QHBoxLayout*);
signals:
    void question_constructed (abstract_question*);
private:
    abstract_question *result;
    Ui::new_question_dialog *ui;
    int type;
    int answers_count;
    int page, pos;
    QList<text_answer_edit*> variants;
};

#endif // NEW_QUESTION_DIALOG_H
