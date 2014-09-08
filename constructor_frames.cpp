#include "constructor_frames.h"

abstract_question::abstract_question (QString _wording, int _page, int _pos, bool _is_enable)
{
    this->setLayout(&result_layout);
    wording.setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Minimum);
    result_layout.addWidget(&wording);
    wording.setText(_wording);
    page = _page;
    pos = _pos;
    is_enable = _is_enable;
}

text_question::text_question (QString _wording, int _page, int _pos, bool _is_enable):
    abstract_question (_wording, _page, _pos, _is_enable)
{
    answer.setEnabled(is_enable);
    result_layout.addWidget(&answer);
}

int text_question::send_to_database (int survey_id, int page_num)
{
    return db->add_question (survey_id, this->get_wording(), TEXT_QUESTION, page_num);
}

abstract_choice_question::abstract_choice_question (QString _wording, int _page, int _pos, bool _is_enable):
    abstract_question (_wording, _page, _pos, _is_enable)
{
    variants.setLayout(&variants_layout);
    result_layout.addWidget(&variants);
}

set_question::set_question (QString _wording, int _page, int _pos, QStringList &_variant_list, bool _is_enable):
    abstract_choice_question (_wording, _page, _pos, _is_enable)
{
    QStringListIterator it (_variant_list);
    while (it.hasNext())
        add_variant(it.next());
}

void set_question::add_variant (QString var)
{
    QRadioButton *new_var = new QRadioButton (var);
    new_var->setEnabled(is_enable);
    variants_layout.addWidget(new_var);
    variant_list << var;
}

int set_question::send_to_database (int survey_id, int page_num)
{
    return db->add_question (survey_id, this->get_wording(), SET_QUESTION, page_num, this->get_variants());
}

enum_question::enum_question (QString _wording, int _page, int _pos, QStringList &_variant_list, bool _is_enable):
    abstract_choice_question (_wording, _page, _pos, _is_enable)
{
    QStringListIterator it (_variant_list);
    while (it.hasNext())
        add_variant(it.next());
}

void enum_question::add_variant (QString var)
{
    QCheckBox *new_var = new QCheckBox (var);
    new_var->setEnabled(is_enable);
    variants_layout.addWidget(new_var);
    variant_list << var;
}

int enum_question::send_to_database (int survey_id, int page_num)
{
    return db->add_question (survey_id, this->get_wording(), ENUM_QUESTION, page_num, this->get_variants());
}
