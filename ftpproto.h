#ifndef _FTP_PROTO_H_
#define _FTP_PROTO_H_

#include "session.h"

void handle_child(session_t *sess);
void ftp_reply(session_t *sess, int status, const char *text);
void ftp_lreply(session_t *sess, int status, const char *text);
int list_common(session_t *sess);
int get_transfer_fd(session_t *sess);

#endif