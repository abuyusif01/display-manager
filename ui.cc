#include "headers/ui.h"

#include "authentication.cc"
#include <ncurses.h>

// constructor
void Ui::init_scr()
{
    int ch;

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    this->body_window = newwin(24, 80, 0, 0);
    assert(body_window != NULL);
    box(body_window, 0, 0);
    this->form_window = derwin(body_window, 20, 78, 3, 1);
    assert(form_window != NULL);
    box(form_window, 0, 0);
    mvwprintw(body_window, 1, 2, "Press F1 to quit and F2 to print this->fields content");

    this->fields[0] = new_field(1, 10, 0, 0, 0, 0);
    this->fields[1] = new_field(1, 40, 0, 15, 0, 0);
    this->fields[2] = new_field(1, 10, 2, 0, 0, 0);
    this->fields[3] = new_field(1, 40, 2, 15, 0, 0);
    this->fields[4] = NULL;
    assert(this->fields[0] != NULL && this->fields[1] != NULL && this->fields[2] != NULL && this->fields[3] != NULL);

    set_field_buffer(this->fields[0], 0, "Username");
    set_field_buffer(this->fields[1], 0, "");
    set_field_buffer(this->fields[2], 0, "Password");
    set_field_buffer(this->fields[3], 0, "");

    set_field_opts(this->fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(this->fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(this->fields[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(this->fields[3], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    set_field_back(this->fields[1], A_UNDERLINE);
    set_field_back(this->fields[3], A_UNDERLINE);

    this->form = new_form(this->fields);
    assert(this->form != NULL);
    set_form_win(this->form, form_window);
    set_form_sub(this->form, derwin(form_window, 18, 76, 1, 1));
    post_form(this->form);

    refresh();
    wrefresh(body_window);
    wrefresh(form_window);

    while ((ch = getch()) != KEY_F(1))
        this->driver(ch);

    unpost_form(this->form);
    // this->init_input();
}

char *Ui::get_name()
{
    return this->trim_whitespaces(this->name);
}

char *Ui::get_pass()
{
    return this->trim_whitespaces(this->pass);
}

void Ui::init_input()
{
    this->name = field_buffer(this->fields[1], 0);
    this->pass = field_buffer(this->fields[3], 0);
}

void Ui::set_cmd(char *cmd)
{
    this->cmd = cmd;
}
void Ui::driver(int ch)
{

    switch (ch)
    {
    case 10:
    {
        form_driver(this->form, REQ_NEXT_FIELD);
        form_driver(this->form, REQ_PREV_FIELD);
        pos_form_cursor(this->form);
        this->init_input();
        
        if (login(this->get_name(), this->get_pass(), this->cmd.c_str()))
        {
            
            free_form(this->form);
            free_field(this->fields[0]);
            free_field(this->fields[1]);
            free_field(this->fields[2]);
            free_field(this->fields[3]);
            delwin(form_window);
            delwin(body_window);
            clear();
            printw("Login sucessfully");
        }
        else
        {
            clear();
            printw("something went wrong!!");
            // refresh();
        }
    }
    break;

    case KEY_DOWN:
        form_driver(this->form, REQ_NEXT_FIELD);
        form_driver(this->form, REQ_END_LINE);
        break;

    case KEY_UP:
        form_driver(this->form, REQ_PREV_FIELD);
        form_driver(this->form, REQ_END_LINE);
        break;

    case KEY_LEFT:
        form_driver(this->form, REQ_PREV_CHAR);
        break;

    case KEY_RIGHT:
        form_driver(this->form, REQ_NEXT_CHAR);
        break;

    // Delete the char before cursor
    case KEY_BACKSPACE:
    case 127:
        form_driver(this->form, REQ_DEL_PREV);
        break;

    // Delete the char under the cursor
    case KEY_DC:
        form_driver(this->form, REQ_DEL_CHAR);
        break;

    default:
        form_driver(this->form, ch);
        break;
    }

    wrefresh(this->form_window);
}

char *Ui::trim_whitespaces(char *str) // some majic functions
{
    char *end;
    while (isspace(*str))
        str++;
    if (*str == 0) // all spaces?
        return str;
    end = str + strnlen(str, 128) - 1;
    while (end > str && isspace(*end))
        end--;
    *(end + 1) = '\0';
    return str;
}