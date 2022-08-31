#include "headers/ui.h"

int main(int argc, char const *argv[])
{
    Ui *ui = new Ui();
    ui->init_scr();
    endwin();
    delete ui;
    return 0;
}
