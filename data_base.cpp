#include "data_base.h"

#include <openssl/sha.h>
#include <QVariant>
#include <QString>
#include <QMessageBox>

data_base *db = new data_base ();

data_base::data_base ()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("SurveyDB");
}

int data_base::connect (QString user_name, QString host_name, QString password)
{
    db.setUserName (user_name);
    db.setHostName (host_name);
    db.setPassword (password);
    if (!db.open ()) QMessageBox::critical (0, "error", db.lastError().text(),QMessageBox::Cancel);
    query = new QSqlQuery (db);
    return 0;
}

int data_base::add_user (QString name, QString password)
{
    query->prepare ("INSERT INTO Owners (name, password)\
                     VALUES (:name, :password);");
    query->bindValue (":name", name);
    query->bindValue (":password", hash_password(password));
    return query->exec ();
}

int data_base::add_survey (QString name, QString description, QString owner)
{
    query->prepare ("INSERT INTO Surveys (name, description, Owners_name)\
                     VALUES (:name, :description, :owner);");
    query->bindValue (":name", name);
    query->bindValue (":description", description);
    query->bindValue (":owner", owner);
    return query->exec ();
}

int data_base::add_question(int survey_index, QString wording, int q_type, int page_num)
{
    query->prepare ("INSERT INTO Questions (wording, type, page, Surveys_idSurveys)\
                     VALUES (:wording, :type, :page_num, :id_survey);");
    query->bindValue (":wording", wording);
    query->bindValue (":type", q_type);
    query->bindValue (":page", page_num);
    query->bindValue (":id_survey", survey_index);
    return query->exec();
}

int data_base::add_question (int survey_index, QString wording, int q_type, int page_num, QStringList variants)
{
    int result = 0;
    query->prepare ("INSERT INTO Questions (wording, type, page, Surveys_idSurveys)\
                     VALUES (:wording, :type, :page_num, :id_survey);");
    query->bindValue (":wording", wording);
    query->bindValue (":type", q_type);
    query->bindValue (":page", page_num);
    query->bindValue (":id_survey", survey_index);
    result = query->exec();
    if (result == 1)
    {
        int last_id;
        if (query->exec("SELECT LAST_INSERT_ID()"))
        {
            query->next();
            last_id = query->value(0).toInt();

            QStringListIterator it (variants);

            switch (q_type)
            {
                case SET_QUESTION:
                {
                    query->prepare("INSERT INTO Sets (variants, Questions_idQuestions)\
                                    VALUES (:variant, :id_quest)");
                    while (it.hasNext() && result)
                    {
                        query->bindValue(":variant", it.next());
                        query->bindValue(":id_quest", last_id);
                        result = query->exec();
                    }
                }
                case ENUM_QUESTION:
                {
                    query->prepare("INSERT INTO Enums (variants, Questions_idQuestions)\
                                    VALUES (:variant, :id_quest)");
                    while (it.hasNext() && result)
                    {
                        query->bindValue(":variant", it.next());
                        query->bindValue(":id_quest", last_id);
                        result = query->exec();
                    }
                }
            }
        }
    }
    return result;
}

char* data_base::hash_password (QString password)
{
    char* pass_hash = new char[PASSWORD_HASH_SIZE+1];
    SHA1 ((unsigned char*) password.toUtf8().data(), password.length()* sizeof (char), (unsigned char*)pass_hash);
    pass_hash[PASSWORD_HASH_SIZE] = '\0';
    return pass_hash;
}

int data_base::login (QString name, QString password)
{
    int result = 1;
    query->exec ("SELECT name FROM Owners;");
    bool name_found = false;
    while (((!name_found)) && (query->next()))
        if (query->value(0).toString() == name) name_found = true;
    if (name_found)
    {
        query->prepare("SELECT password FROM Owners WHERE name = :name;");
        query->bindValue(":name", name);
        query->exec ();
        if (query->first())
            if (hash_password(password) == query->value(0).toString()) result = 0;
    }
    return result;
}

QStringList data_base::get_survey_list (QString owner)
{
    QStringList result;
    query->exec ("SELECT name FROM Surveys WHERE Owners_name = "+owner+";");
    while (query->next())
        result.append(query->value("name").toString());
    return result;
}
