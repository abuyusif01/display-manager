#ifndef AUTEHNTICAION_H
#define AUTEHNTICAION_H

#define SERVICE_NAME "display-manager"
#include "ui.h"
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <pwd.h>

class Auth : Ui
{

private:
    static int conv(int num_msg, const struct pam_message **msg, struct pam_response **resp, void *appdata_ptr);
    bool login(const char *name, const char *pass, pid_t *child_pid);
    bool logout();
    void init_env(struct passwd *pw);
    int end(int last_result);
    void set_env(std::string name, std::string value);
};

#endif // AUTEHNTICAION_H
