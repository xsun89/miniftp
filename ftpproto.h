#ifndef _FTP_PROTO_H_
#define _FTP_PROTO_H_

#include "session.h"

void handle_child(session_t *sess);
void ftp_reply(session_t *sess, int status, const char *text);
void ftp_lreply(session_t *sess, int status, const char *text);
int list_common(session_t *sess, int detail);
int get_transfer_fd(session_t *sess);
int port_active(session_t *sess);
int pasv_active(session_t *sess);
int get_port_fd(session_t *sess);
int get_pasv_fd(session_t *sess);
int get_transfer_fd(session_t *sess);
void upload_common(session_t *sess, int is_append);
void limit_rate(session_t *sess, int bytes_transfered, int is_upload);

void handle_alarm_timeout(int sig);
void handle_data_connection_sigalarm(int sig);
void start_cmdio_alarm(void);
void start_data_alarm(void);
void handle_sigurg(int sig);
void check_abor(session_t *sess);

#endif