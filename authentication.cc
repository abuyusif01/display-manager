#include "headers/authentication.h"
#include "headers/logger.h"
#include "headers/ui.h"

static pam_handle_t *pam_handle;

void Authentication::init_env(struct passwd *pw, const char* tty_id)
{
    extern char **environ;
    char *term = getenv("TERM");
    char *lang = getenv("LANG");
    char user[15];

    // setting xdg env
    snprintf(user, 15, "/run/user/%d", getuid());
    set_env("XDG_SESSION_TYPE", "x11");
    setenv("XDG_RUNTIME_DIR", user, 0);
    setenv("XDG_SESSION_CLASS", "user", 0);
    setenv("XDG_SESSION_ID", "1", 0);
    setenv("XDG_SEAT", "seat0", 0);
    setenv("XDG_VTNR", tty_id, 0);
    // clean env
    environ[0] = NULL;

    setenv("TERM", term ? term : "linux", 1);
    setenv("HOME", pw->pw_dir, 1);
    setenv("PWD", pw->pw_dir, 1);
    setenv("SHELL", pw->pw_shell, 1);
    setenv("USER", pw->pw_name, 1);
    setenv("LOGNAME", pw->pw_name, 1);
    setenv("LANG", lang ? lang : "C++", 1);
}

int Authentication::get_free_display(int size)
{
    char xlock[size];
    uint8_t i; // we declare this here so could access it outside the loop
    for (i = 0; i < 200; i++)
    {
        snprintf(xlock, sizeof(xlock), "/tmp/.X%d-lock", i);
        if (access(xlock, F_OK) == -1)
        {
            break;
        }
    }
    return i;
}

void Authentication::reset_terminal(struct passwd *pw)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        execl(pw->pw_shell, pw->pw_shell, "-c"
                                          "reset",
              NULL);
        exit(EXIT_SUCCESS);
    }
    int status;
    waitpid(pid, &status, 0);
}

int Authentication::end(int last_result)
{
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

    // this loop assign the actual name and pass to the pam_response
    for (i = 0; i < num_msg; i++)
    {
        char *name, *pass;
        switch (msg[i]->msg_style)
        {
        case PAM_PROMPT_ECHO_ON:
        {
            name = ((char **)appdata_ptr)[0];
            (*resp)[i].resp = strdup(name);
            break;
        }
        case PAM_PROMPT_ECHO_OFF:
        {
            pass = ((char **)appdata_ptr)[1];
            (*resp)[i].resp = strdup(pass);
            break;
        }
        case PAM_ERROR_MSG:
        {
            Logger(1, msg[i]->msg);
            break;
        }
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
