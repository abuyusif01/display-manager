#ifndef UI_H
#define UI_H

#include <form.h>
#include <ctype.h>
#include <ncurses.h>
#include <assert.h>
#include <string.h>
#include <iostream>

class Ui : FORM, WINDOW
{

public:
    char *name, *pass;

public:
    FORM *form;
    WINDOW *body_window, *form_window;

public:
    FIELD *fields[4];

public:
    Ui();
    void driver(int ch);
    void set_field(int index, std::string value);
    char *trim_whitespaces(char *str);
    char *get_field(int index);
    void ui_refresh(WINDOW *window);
    void init_input();
    char *get_name();
    char *get_pass();
};
#endif