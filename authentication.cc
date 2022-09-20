#include "headers/authentication.h"
#include "headers/logger.h"
#include  "headers/ui.h"

static pam_handle_t *pam_handle;
int Authentication::end(int last_result){
int result = pam_end(pam_handle, last_result);
    pam_handle = 0;
    return result;
}
int Authentication::conv(int num_msg, const struct pam_message **msg, struct pam_response **resp, void *appdata_ptr)
{
    int i;
    *resp = (struct pam_response *)calloc(num_msg, sizeof(struct pam_response));
    if (*resp == NULL)
    {
        Logger(1, "pam buffer error");
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
            Logger(1, msg[i]->msg);
            break;
        case PAM_TEXT_INFO:
        {
            // Todo:  fix logger constructor to accept args like this
            // std::string content = "pam_conv: " + std::to_string(1);
            Logger(1, msg[i]->msg);

            break;
        }
        }
        if (result != PAM_SUCCESS)
        {
            Logger(1, "pam_conv: failed");
            break;
        }
    }
    if (result != PAM_SUCCESS)
    {
        free(*resp);
        *resp = 0;
        Logger(1, "pam_conv: failed resp set to nullptr");
    }
    return result;
}
bool Authentication::set_env(std::string nam, std::string value)
{
    std::string name_value = nam + "=" + value;
    std::string content = "pam_putenv: success " + name_value;
    switch (pam_putenv(pam_handle, name_value.c_str()))
    {
    case PAM_PERM_DENIED:
        Logger(1, "pam_putenv: pam_perm_denied");
        break;
    case PAM_BAD_ITEM:
        Logger(1, "pam_putenv: pam_bad_item");
        break;
    case PAM_ABORT:
        Logger(1, "pam_putenv: pam_abort");
        break;
    case PAM_BUF_ERR:
        Logger(1, "pam_putenv: pam_buf_err");
        break;
    case PAM_SUCCESS:
        Logger(3, content);
        break;

    default:
        Logger(-1, "pam_putenv: invlalid error code");
    }
    return true;
}

bool Authentication::logout(void)
{

    /*
    1 -> ERROR
    2 -> WARNING
    3 -> INFO
    */

    int result = pam_close_session(pam_handle, 0);
    if (result != PAM_SUCCESS)
    {
        pam_setcred(pam_handle, PAM_DELETE_CRED);
        Logger(1, "pam_closession: failed");
    }

    result = pam_setcred(pam_handle, PAM_DELETE_CRED);
    if (result != PAM_SUCCESS)
    {
        Logger(1, "pam_setcred: failed");
    }
    end(result);
    return true;
}
 bool Authentication::login(const char *name, const char *pass, const char *cmd)
{
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
        Logger(1, "pam_login: Login failed");
        return false;
    }

    result = pam_acct_mgmt(pam_handle, 0);
    if (result != PAM_SUCCESS)
    {
        Logger(1, "pam_acc_mgmt: failed");
        return false;
    }

    result = pam_setcred(pam_handle, PAM_ESTABLISH_CRED);
    if (result != PAM_SUCCESS)
    {
        Logger(1, "pam_setcred: failed");
        return false;
    }

    result = pam_open_session(pam_handle, 0);
    if (result != PAM_SUCCESS)
    {
        pam_setcred(pam_handle, PAM_DELETE_CRED);
        Logger(1, "open_session: failed");
        return false;
    }
    struct passwd *pw = getpwnam(name);

    Ui *ui = new Ui();

    /*
        incase something went wrong, we need to make sure that we delete the ui object
        before we exit the program
    */

    wclear(ui->body_window);
    wclear(ui->form_window);
    endwin();

    chdir(pw->pw_dir);

    // might need a thread here need to get the exit code from the child process
    if (execl(pw->pw_shell, pw->pw_shell, "-c", cmd, NULL) == -1)
    {
        Logger(1, "X: command can mot be executed");
        delete (ui);
    }
    else
    {
        Logger(3, "startx: Command run succesfully");
        delete (ui);
    }
    return true;
}

