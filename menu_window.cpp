#include "menu_window.h"
#include "ui_menu_window.h"

#include "login_dialog.h"

menu_window::menu_window(QWidget *parent) :
    QDialog(parent), ui(new Ui::menu_window)
{
    ui->setupUi(this);

    QObject::connect (ui->admin_login_button, SIGNAL (clicked()),
                      this, SLOT (open_login_window()));
    QObject::connect (ui->user_login_button, SIGNAL (clicked()),
                      this, SLOT (open_login_window()));
    QObject::connect (ui->exit_button, SIGNAL (clicked()),
                      qApp, SLOT (quit()));
}

menu_window::~menu_window()
{
    delete ui;
}

void menu_window::open_login_window ()
{
    login_window *log_win = new login_window (0);
    QObject::connect (log_win, SIGNAL (login_done()),
                      this, SLOT (close()));
    log_win->show ();
}
