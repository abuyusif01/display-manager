#include <iostream>
#include <pwd.h>
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <string>
#define SERVICE_NAME "ADY"
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

bool login(const std::string UserName, const std::string PassWord, )
{
    //    UserAuthentication *auth;
    pam_handle_t* pam_handle;
    const char* data[2] = { UserName.c_str(), PassWord.c_str() };
    struct pam_conv pam_conv {
        conv, data
    };
    struct passwd* pass = getpwnam(UserName.c_str());
    std::cout << UserName;
    int result;
    result = pam_start(SERVICE_NAME, pass->pw_name, &pam_conv, &pam_handle);

    return result;
}

int main(int argc, char* argv[])
{
    login("username", "password");
    return 0;
}
