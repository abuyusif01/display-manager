#define SERVICE_NAME "display-manager"
#include "headers/ui.h"
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <pwd.h>
#include <paths.h>

static pam_handle_t *pam_handle;

static int end(int last_result)
{
    int result = pam_end(pam_handle, last_result);
    pam_handle = 0;
    return result;
}

static bool set_env(std::string name, std::string value)
{
    std::string name_value = name + "=" + value;
    pam_putenv(pam_handle, name_value.c_str());
    return true;
}
static bool logout(void)
{
    int result = pam_close_session(pam_handle, 0);
    if (result != PAM_SUCCESS)
    {
        pam_setcred(pam_handle, PAM_DELETE_CRED);
        // qDebug() << "closession: failed";
    }

    result = pam_setcred(pam_handle, PAM_DELETE_CRED);
    if (result != PAM_SUCCESS)
    {
        // qDebug() << "pam_setcred: failed";
    }
    end(result);
    return true;
}

static void init_env(struct passwd *pw)
{
    set_env("HOME", pw->pw_dir);
    set_env("PWD", pw->pw_dir);
    set_env("SHELL", pw->pw_shell);
    set_env("USER", pw->pw_name);
    set_env("LOGNAME", pw->pw_name);
    set_env("PATH", "/usr/local/sbin:/usr/local/bin:/usr/bin");
    set_env("MAIL", _PATH_MAILDIR);
    std::string xauthority = std::to_string(*pw->pw_dir) + "/.Xauthority";
    set_env("XAUTHORITY", xauthority);
}

static int conv(int num_msg, const struct pam_message **msg, struct pam_response **resp, void *appdata_ptr)
{
    int i;
    *resp = (struct pam_response *)calloc(num_msg, sizeof(struct pam_response));
    if (*resp == NULL)
    {
        return PAM_BUF_ERR;
    }

    int result = PAM_SUCCESS;
    for (i = 0; i < num_msg; i++)
    {
        char *name, *pass;
        switch (msg[i]->msg_style)
        {
        case PAM_PROMPT_ECHO_ON:
            name = ((char **)appdata_ptr)[0];
            (*resp)[i].resp = strdup(name);
            break;
        case PAM_PROMPT_ECHO_OFF:
            pass = ((char **)appdata_ptr)[1];
            (*resp)[i].resp = strdup(pass);
            break;
        case PAM_ERROR_MSG:
            fprintf(stderr, "%s\n", msg[i]->msg);
            break;
        case PAM_TEXT_INFO:
            printf("%s\n", msg[i]->msg);
            break;
        }
        if (result != PAM_SUCCESS)
        {
            break;
        }
    }
    if (result != PAM_SUCCESS)
    {
        free(*resp);
        *resp = 0;
    }
    return result;
}

static bool login(const char *name, const char *pass, const char* cmd)
{

    //    UserAuthentication *auth;

    const char *data[2] = {name, pass};
    struct pam_conv pam_conv
    {
        conv, data
    };
    int result;
    result = pam_start(SERVICE_NAME, name, &pam_conv, &pam_handle);
    result = pam_authenticate(pam_handle, 0);
    if (result != PAM_SUCCESS)
    {
        // qDebug() << "authenticate: failed";
        return false;
    }

    result = pam_acct_mgmt(pam_handle, 0);
    if (result != PAM_SUCCESS)
    {
        // qDebug() << "pam_acc_mgmt: failed";
        return false;
    }

    result = pam_setcred(pam_handle, PAM_ESTABLISH_CRED);
    if (result != PAM_SUCCESS)
    {
        // qDebug() << "pam_setcred: failed";
        return false;
    }

    result = pam_open_session(pam_handle, 0);
    if (result != PAM_SUCCESS)
    {
        pam_setcred(pam_handle, PAM_DELETE_CRED);
        // qDebug()<<"open_session: failed";
        return false;
    }
    struct passwd *pw = getpwnam(name);
    pid_t *child_pid;
    *child_pid = fork();
    chdir(pw->pw_dir);
    //std::string cmd = "exec /bin/bash --login .xinitrc";
    execl(pw->pw_shell, pw->pw_shell, "-c", cmd, NULL);
    return true;
}
