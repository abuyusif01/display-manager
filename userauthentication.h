#include <iostream>
#include <pwd.h>
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <string>
#include <QCoreApplication>
#include <QDebug>

#define SERVICE_NAME "system-login"
static int conv(int num_msg, const struct pam_message** msg, struct pam_response** resp, void* appdata_ptr)
{
    int i;
    *resp = (struct pam_response*)calloc(num_msg, sizeof(struct pam_response));
    if (*resp == NULL) {
        return PAM_BUF_ERR;
    }

    int result = PAM_SUCCESS;
    for (i = 0; i < num_msg; i++) {
        std::string UserName, PassWord;
        switch (msg[i]->msg_style) {
        case PAM_PROMPT_ECHO_ON:
            UserName = ((char**)appdata_ptr)[0];
            (*resp)[i].resp = strdup(UserName.c_str());
            break;
        case PAM_PROMPT_ECHO_OFF:
            PassWord = ((char**)appdata_ptr)[1];
            (*resp)[i].resp = strdup(PassWord.c_str());
            break;
        case PAM_ERROR_MSG:
            fprintf(stderr, "%s\n", msg[i]->msg);
            break;
        case PAM_TEXT_INFO:
            printf("%s\n", msg[i]->msg);
            break;
        }
        if (result != PAM_SUCCESS) {
            break;
        }
    }
    if (result != PAM_SUCCESS) {
        free(*resp);
        *resp = 0;
    }
    return result;
}

bool login(const std::string UserName, const std::string PassWord, pid_t *child_pid)
{
    //    UserAuthentication *auth;
    pam_handle_t* pam_handle;
    const char* data[2] = { UserName.c_str(), PassWord.c_str() };
    struct pam_conv pam_conv {
        conv, data
    };
    int result;
    result = pam_start(SERVICE_NAME, UserName.c_str(), &pam_conv, &pam_handle);
    result = pam_authenticate(pam_handle, 0);
    if (result != PAM_SUCCESS)
    {   qDebug()<<"authenticate: failed";
        return false;
    }

    result = pam_acct_mgmt(pam_handle, 0);
    if (result != PAM_SUCCESS)
    {   qDebug()<<"pam_acc_mgmt: failed";
        return false;
    }

    result = pam_setcred(pam_handle, PAM_ESTABLISH_CRED);
    if (result != PAM_SUCCESS)
    {   qDebug()<<"pam_setcred: failed";
        return false;
    }

    result = pam_open_session(pam_handle, 0);
    if (result != PAM_SUCCESS)
    {
        pam_setcred(pam_handle, PAM_DELETE_CRED);
        qDebug()<<"open_session: failed";
        return false;
    }
    struct passwd *pw = getpwnam(UserName.c_str());
    *child_pid = fork();
    chdir(pw->pw_dir);
    std::string cmd = "/bin/zsh --login";
    execl(pw->pw_shell, pw->pw_shell, "-c",cmd.c_str(),NULL);
    return true;
}





























