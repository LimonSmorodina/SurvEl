#ifndef CONSTRUCTOR_FRAMES_H
#define CONSTRUCTOR_FRAMES_H

#include <QWidget>
#include <QVector>
#include <QBoxLayout>
#include <QTextBrowser>
#include <QLineEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QRadioButton>

#include "data_base.h"

// ABSTRACT CLASSES
class abstract_question: public QWidget
{
    Q_OBJECT
public:
    abstract_question (QString _wording, int _page, int _pos, bool _is_enable = true);

    virtual int send_to_database () {return 0;}
    virtual abstract_question *get_copy () {return 0;}
    inline QString get_wording () {return wording.toPlainText();}
protected:
    QTextBrowser wording;
    int page;
    int pos;
    QVBoxLayout result_layout;
    bool is_enable;
};

class abstract_choice_question: public abstract_question
{
    Q_OBJECT
public:
    abstract_choice_question (QString _wording, int _page, int _pos, bool _is_enable = true);

    virtual void add_variant () {}
    inline QStringList get_variants () {return variant_list;}
protected:
    QGroupBox variants;
    QStringList variant_list;
    QVBoxLayout variants_layout;
};

// WIDGET CLASSES
class text_question: public abstract_question
{
    Q_OBJECT
public:
    text_question (QString _wording, int _page, int _pos, bool _is_enable = true);

    virtual int send_to_database (int survey_id, int page_num);
    virtual abstract_question *get_copy () {return new text_question (get_wording(), page, pos, is_enable);}
private:
    QLineEdit answer;
};

class enum_question: public abstract_choice_question
{
    Q_OBJECT
public:
    enum_question (QString _wording, int _page, int _pos, bool _is_enable = true):
        abstract_choice_question (_wording, _page, _pos, _is_enable) {}

    enum_question (QString _wording, int _page, int _pos, QStringList &_variant_list, bool _is_enable);

    virtual int send_to_database (int survey_id, int page_num);
    virtual void add_variant (QString var);
    virtual abstract_question *get_copy () {return new enum_question (get_wording(), page, pos, variant_list, is_enable);}
private:
    int answer;
};

class set_question: public abstract_choice_question
{
    Q_OBJECT
public:
    set_question (QString _wording, int _page, int _pos, bool _is_enable = true):
        abstract_choice_question (_wording, _page, _pos, _is_enable) {}

    set_question (QString _wording, int _page, int _pos,  QStringList &_variant_list, bool _is_enable = true);

    virtual int send_to_database (int survey_id, int page_num);
    virtual void add_variant (QString var);
    virtual abstract_question *get_copy () {return new set_question (get_wording(), page, pos, variant_list, is_enable);}
private:
    QVector<int> answers;
};
#endif // CONSTRUCTOR_FRAMES_H
