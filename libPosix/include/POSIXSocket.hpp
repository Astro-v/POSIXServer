#ifndef POSIX_SOCKET_HPP
#define POSIX_SOCKET_HPP

#include "POSIXAddress.hpp"

class POSIXSocket
{
private:
    int m_fd;

public:
    POSIXSocket();
    POSIXSocket(int fd);
    ~POSIXSocket();

    int connect(POSIXAddress &address);
    int send(std::string message);
    int receive(std::string &message);
};

#endif // POSIX_SOCKET_HPP