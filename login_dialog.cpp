#include "login_dialog.h"
#include "ui_login_dialog.h"

#include "data_base.h"
#include "register_dialog.h"
#include "pollster_window.h"

login_window::login_window (QWidget *parent):
    QDialog(parent), ui(new Ui::login_window)
{
    ui->setupUi(this);
    QObject::connect (ui->login_button, SIGNAL (clicked()), this, SLOT (login()));
    QObject::connect (ui->register_button, SIGNAL (clicked()), this, SLOT (register_user()));
    QObject::connect (ui->exit_button, SIGNAL (clicked()), this, SLOT (close()));
}

login_window::~login_window()
{
    delete ui;
}

void login_window::login()
{
    QString error = "";
    if ((ui->username_edit->text().length() < 6) || (ui->username_edit->text().length() > 20))
        error = "Error: username length must be 6 to 20 characters";
    if ((ui->password_edit->text().length() < 7) || (ui->password_edit->text().length() > 20))
        error = "Error: password length must be 7 to 20 characters";
    if (error == "")
    {
        if (db->login (ui->username_edit->text(), ui->password_edit->text()))
            error = "Error: wrong username or password.";
        else
        {
            pollster_window *win = new pollster_window (ui->username_edit->text());
            win->show();
            emit login_done();
            this->close();
        }
    }
    ui->error_label->setText(error);
}

void login_window::register_user()
{
    register_dialog *reg_dial = new register_dialog (0);
    reg_dial->show ();
}
