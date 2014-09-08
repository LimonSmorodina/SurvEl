#include <QApplication>

#include "menu_window.h"
#include "data_base.h"
#include "pollster_window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    db->connect("root","localhost","9xhjm2zm");

    pollster_window win ("tester");
    win.show();

    //menu_window main_menu;
    //main_menu.show();
    return a.exec();
}
