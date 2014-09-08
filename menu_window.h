#ifndef MENU_WINDOW_H
#define MENU_WINDOW_H

#include <QDialog>

namespace Ui {
class menu_window;
}

class menu_window : public QDialog
{
    Q_OBJECT

public:
    explicit menu_window(QWidget *parent = 0);
    ~menu_window();

public slots:
    void open_login_window ();
private:
    Ui::menu_window *ui;
};

#endif // MENU_WINDOW_H
