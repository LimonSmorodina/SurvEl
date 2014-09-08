#ifndef CONSTRUTCOR_PAGE_H
#define CONSTRUTCOR_PAGE_H

#include <QWidget>
#include <QList>
#include "constructor_frames.h"

#define NEXT 0
#define PREV 1

namespace Ui {
class construtcor_page;
}

class construtcor_page : public QWidget
{
    Q_OBJECT

public:
    explicit construtcor_page(QWidget *parent = 0);
    ~construtcor_page();
public slots:
    void add_question (abstract_question* new_quest);
private slots:
    void create_new_question ();
    void create_new_page ();
    void delete_cur_page ();
    void next_page () {change_page(NEXT);}
    void prev_page () {change_page(PREV);}
    void change_page (int);
    int construct_done ();
    void on_page_change ();
private:
    Ui::construtcor_page *ui;
    QList<QList<abstract_question*>*> page_list;
    int cur_page;
};

#endif // CONSTRUTCOR_PAGE_H
