#ifndef POSIX_LISTENER_HPP
#define POSIX_LISTENER_HPP

#include "POSIXSocket.hpp"
#include "POSIXAddress.hpp"
#include <memory>

class POSIXListener
{
private:
    int m_fd;

public:
    POSIXListener();
    ~POSIXListener();

    void listen(POSIXAddress &address, int backlog = 5);
    std::unique_ptr<POSIXSocket> accept();
};

#endif // POSIX_LISTENER_HPP