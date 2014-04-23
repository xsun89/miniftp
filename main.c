#include "common.h"
#include "sysutil.h"
#include "session.h"

int main(void)
{
    if(getuid() != 0)
    {
        fprintf(stderr, "miniftpd: must be started as root\n");
        exit(EXIT_FAILURE);
    }

    session_t sess = {
        -1, "", "", "",
        -1, -1
    };

    int listenfd = tcp_server(NULL, 5188);
    int conn;
    
}