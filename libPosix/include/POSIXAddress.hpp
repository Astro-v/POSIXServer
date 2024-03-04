#ifndef POSIX_ADDRESS_HPP
#define POSIX_ADDRESS_HPP

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string>

class POSIXAddress
{
private:
    struct sockaddr_un m_addr;

public:
    POSIXAddress() = delete;
    POSIXAddress(const std::string &path);
    POSIXAddress(const char *path);
    ~POSIXAddress() = default;
    POSIXAddress(const POSIXAddress &);

    void unlink();

    struct sockaddr *get_address();
    socklen_t get_size();
};

#endif // POSIX_ADDRESS_HPP