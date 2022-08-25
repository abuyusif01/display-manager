#include "headers/ui.h"
#include "authentication.cc"

int main(int argc, char const *argv[])
{
    Ui *ui = new Ui();
    ui->init_scr();
    endwin();
    delete ui;
    return 0;
}
