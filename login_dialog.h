#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QDialog>

namespace Ui {
class login_window;
}

class login_window : public QDialog
{
    Q_OBJECT

public:
    explicit login_window(QWidget *parent = 0);
    ~login_window();
public slots:
    void login ();
    void register_user ();
signals:
    void login_done ();
private:
    Ui::login_window *ui;
};

#endif // LOGIN_WINDOW_H
