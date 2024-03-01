#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/socket.h>
#include <sys/un.h>

struct Client
{
    int client_fd;
    struct sockaddr_un client_addr;
    socklen_t client_len;
};

#endif // CLIENT_HPP
