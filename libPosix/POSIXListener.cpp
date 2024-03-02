#include "POSIXListener.hpp"

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>

POSIXListener::POSIXListener()
{
    // Create a new socket
    m_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    // Check if the socket was created
    if (m_fd == -1)
    {
        std::cerr << "Error: socket" << std::endl;
        throw std::runtime_error("Error: socket");
    }
}

POSIXListener::~POSIXListener()
{
    // Close the file descriptor
    close(m_fd);
}

void POSIXListener::listen(POSIXAddress &address, int backlog)
{
    // Delete the old socket file if it exists
    address.unlink();

    // Bind the socket to the address
    if (::bind(m_fd, address.get_address(), address.get_size()) == -1)
    {
        std::cerr << "Error: bind" << std::endl;
        throw std::runtime_error("Error: bind");
    }

    // Listen for incoming connections
    if (::listen(m_fd, backlog) == -1)
    {
        std::cerr << "Error: listen" << std::endl;
        throw std::runtime_error("Error: listen");
    }
}

std::unique_ptr<POSIXSocket> POSIXListener::accept()
{
    int cfd;
    socklen_t len;
    struct sockaddr_un addr;
    std::unique_ptr<POSIXSocket> client;

    // Accept a new connection
    if ((cfd = ::accept(m_fd, (struct sockaddr *)&addr, &len)) == -1)
    {
        std::cerr << "Error: accept" << std::endl;
        throw std::runtime_error("Error: accept");
    }

    // return the new client
    client = std::make_unique<POSIXSocket>(cfd);
    return client;
}