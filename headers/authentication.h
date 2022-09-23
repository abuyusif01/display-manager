
#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#define SERVICE_NAME "display-manager"

#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pwd.h>
#include <paths.h>
#include <string>

class Authentication
{

private:
    static int last_result;
    static std::string nam;
    static std::string value;
    static struct passwd *pw;
    static int num_msg;
    static const struct pam_message **msg;
    static struct pam_response **resp;
    static void *appdata_ptr;
    static const char *name;
    static const char *pass;
    static const char *cmd;

public:
    static void init_env(struct passwd *pw, const char *tty_id = "2");
    int get_free_display(int size);
    static void reset_terminal(struct passwd *pw);
    static int end(int last_result);
    static bool set_env(std::string nam, std::string value);
    static bool logout(void);
    static int conv(int num_msg, const struct pam_message **msg, struct pam_response **resp, void *appdata_ptr);
    static bool login(const char *name, const char *pass, const char *cmd);
};
#endif
