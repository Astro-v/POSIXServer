#include "POSIXSocket.hpp"

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>

POSIXSocket::POSIXSocket() : POSIXSocket(socket(AF_UNIX, SOCK_STREAM, 0))
{
}

POSIXSocket::POSIXSocket(int fd) : m_fd(fd)
{
    // Check if the socket was created
    if (m_fd == -1)
    {
        std::cerr << "Error: socket" << std::endl;
        throw std::runtime_error("Error: socket");
    }
}

POSIXSocket::~POSIXSocket()
{
    // Close the file descriptor
    close(m_fd);
}

int POSIXSocket::connect(POSIXAddress &address)
{
    if (::connect(m_fd, address.get_address(), address.get_size()) == -1)
    {
        // Error
        return 1;
    }
    // Everything works fine
    return 0;
}

int POSIXSocket::send(std::string message)
{
    ssize_t bytes_sent;

    // Send the message
    bytes_sent = ::send(m_fd, message.c_str(), message.size(), MSG_NOSIGNAL);

    if (bytes_sent <= 0)
    {
        // Error or end of the connection
        return 1;
    }

    // Everything works fine
    return 0;
}

int POSIXSocket::receive(std::string &message)
{
    ssize_t n = 0;
    char buf[100];

    // Wait to receive the message (Blocking call)
    n = ::recv(m_fd, &buf, sizeof(buf), 0);

    if (n == -1)
    {
        // Error or end of the connection
        return 1;
    }

    // Store the received message
    message = std::string(buf, n);

    // Everything works fine
    return 0;
}
