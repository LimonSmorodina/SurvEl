#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <QtSql>
#include <QString>

#define LOGIN_MAX_LENGTH    20
#define LOGIN_MIN_NEGTH     5
#define PASSWORD_MAX_LENGTH 30
#define PASSWORD_MIN_LENGTH 7
#define PASSWORD_HASH_SIZE  20

// QUESTOINS TYPES DEFINE BY INT
#define TEXT_QUESTION       1
#define SET_QUESTION        2
#define ENUM_QUESTION       3

class data_base
{
public:
    // base
    data_base ();
    int connect (QString user_name, QString host_name, QString password);

    // errors
    QString last_error () {return db.lastError().text();}
    QString last_query_error () {return query->lastError().text();}

    // insert methods
    int add_user (QString name, QString password);
    int add_survey (QString name, QString description, QString owner);
    int add_question (int survey_index, QString wording, int q_type, int page_num);
    int add_question (int survey_index, QString wording, int q_type, int page_num, QStringList variants);

    // get methods
    QStringList get_survey_list (QString);

    // secutity
    char* hash_password (QString password);

    // other
    int login (QString name, QString password);

private:
    QSqlDatabase db;
    QSqlQuery *query;
    QString error;
};

extern data_base *db;

#endif // DATA_BASE_H
