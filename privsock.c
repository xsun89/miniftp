#include "privsock.h"
#include "common.h"
#include "sysutil.h"

void pri_sock_init(session_t *sess)
{
    int sockfds[2];
    if(socketpair(PF_UNIX, SOCK_STREAM, 0, sockfds) < 0)
        ERR_EXIT("socketpair");

    sess->parent_fd = sockfds[0];
    sess->child_fd = sockfds[1];
}

void priv_sock_close(session_t *sess)
{
    if(sess->parent_fd != -1)
    {
        close(sess->parent_fd);
        sess->parent_fd = -1;
    }
    if(sess->child_fd != -1)
    {
        close(sess->child_fd);
        sess->child_fd = -1;
    }
}

void priv_sock_set_parent_context(session_t *sess)
{
    if(sess->child_fd != -1)
    {
        close(sess->child_fd);
        sess->child_fd = -1;
    }
}

void priv_sock_set_child_context(session_t *sess)
{
    if(sess->parent_fd != -1)
    {
        close(sess->parent_fd);
        sess->parent_fd = -1;
    }
}