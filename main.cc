#include "headers/ui.h"
#include "authentication.cc"

int main(int argc, char const *argv[])
{
    Ui *ui = new Ui();
    pid_t *child_pid;
    ui->init_input();
    char *name = ui->get_name(), *pass = ui->get_pass(), *cmd = "startx";
    if (login(name, pass, cmd))
    {
        printf("Login done");
    }
    else
    {
        // printf ("%s -> %s", name, pass);
        printf("%d", sizeof(name));
        printf("nothing works");
    }
    endwin();
    return 0;
}
