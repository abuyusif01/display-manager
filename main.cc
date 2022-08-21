#include "headers/ui.h"

int main(int argc, char const *argv[])
{

    Ui *ui = new Ui();
    ui->init_input();
    endwin();
    printf("%s", ui->get_name());
    // mvwprintw(ui->body_window, 1, 2, ui->get_name().c_str());
    return 0;
}
