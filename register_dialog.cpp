#include "register_dialog.h"
#include "ui_register_dialog.h"

#include "data_base.h"
#include <QMessageBox>

register_dialog::register_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_dialog)
{
    ui->setupUi(this);
    QObject::connect (ui->register_button, SIGNAL (clicked()),
                     this, SLOT (registration()));
    QObject::connect (ui->cancel_button, SIGNAL (clicked()),
                      this, SLOT (close()));
}

register_dialog::~register_dialog()
{
    delete ui;
}

void register_dialog::registration()
{
    QString error = "";
    if ((ui->username_edit->text().length() < 6) || (ui->username_edit->text().length() > 20))
        error = "Error: username length must be 6 to 20 characters";
    if (ui->password_edit->text() != ui->password_edit_2->text())
        error = "Error: passwords must matching.";
    if ((ui->password_edit->text().length() < 7) || (ui->password_edit->text().length() > 20))
        error = "Error: password length must be 7 to 20 characters";
    if (error == "")
    {
        if (!db->add_user(ui->username_edit->text(), ui->password_edit->text()))
            error = "Error: username already taken.";
        else
        {
            QMessageBox msg (this);
            msg.setText("Registration succuessfuly done.");
            msg.setStandardButtons(QMessageBox::Ok);
            msg.exec();
            this->close();
        }
    }
    ui->error_label->setText(error);
}
