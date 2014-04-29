#include "privparent.h"

void handle_parent(session_t *sess)
{
    struct passwd *pw = getpwnam("nobody");
    if(pw == NULL)
        return;

    if(setegid(pw->pw_gid < 0))
        ERR_EXIT("setegid");

    if(seteuid(pw->pw_uid))
        ERR_EXIT("seteuid");

    char cmd;
    while(1)
    {
        read(sess->parent_fd, &cmd, 1);
    }
}