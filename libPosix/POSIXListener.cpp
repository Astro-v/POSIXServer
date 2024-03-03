#include "POSIXListener.hpp"

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>

POSIXListener::POSIXListener()
{
    // Create a new socket
    m_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    std::cout << "Socket created" << std::endl;

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

/**
 * @brief Listen for incoming connections
 * @param address The address to bind the socket to
 * @param backlog The maximum length of the queue of pending connections
 * @return void
 */
void POSIXListener::listen(POSIXAddress &address, int backlog)
{
    // Bind the socket to the address
    if (::bind(m_fd, address.get_address(), address.get_size()) == -1)
    {
        handle_bind_error(errno);
    }

    // Listen for incoming connections
    if (::listen(m_fd, backlog) == -1)
    {
        std::cerr << "Error: listen" << std::endl;
        throw std::runtime_error("Error: listen");
    }
}

/**
 * @brief Accept a new connection
 * @return A new client
 */
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

void POSIXListener::handle_bind_error(int error)
{
    if (error == EBADF)
    {
        std::cerr << "Error (EBADF) : " << strerror(errno) << std::endl;
        throw std::runtime_error("Error: EBADF");
    }
    else if (error == ENOTSOCK)
    {
        std::cerr << "Error (ENOTSOCK) : " << strerror(errno) << std::endl;
        throw std::runtime_error("Error: ENOTSOCK");
    }
    else if (error == EOPNOTSUPP)
    {
        std::cerr << "Error (EOPNOTSUPP) : " << strerror(errno) << std::endl;
        ;
        throw std::runtime_error("Error: EOPNOTSUPP");
    }
    else if (error == EINVAL)
    {
        std::cerr << "Error (EINVAL) : " << strerror(errno) << std::endl;
        if (::close(m_fd) == -1)
        {
            handle_close_error(errno);
        }
        else
        {
            std::cout << "Socket closed" << std::endl;
        }
        throw std::runtime_error("Error: EINVAL");
    }
    else if (error == EADDRINUSE)
    {
        std::cerr << "Error (EADDRINUSE) : " << strerror(errno) << std::endl;
        throw std::runtime_error("Error: EADDRINUSE");
    }
    else
    {
        std::cerr << "Error: bind" << std::endl;
        throw std::runtime_error("Error: bind");
    }
}

void POSIXListener::handle_close_error(int error)
{
    if (error == EBADF)
    {
        std::cerr << "Error (EBADF) : " << strerror(errno) << std::endl;
        throw std::runtime_error("Error: EBADF");
    }
    else if (error == EINTR)
    {
        std::cerr << "Error (EINTR) : " << strerror(errno) << std::endl;
        throw std::runtime_error("Error: EINTR");
    }
    else if (error == EIO)
    {
        std::cerr << "Error (EIO) : " << strerror(errno) << std::endl;
        throw std::runtime_error("Error: EIO");
    }
    else
    {
        std::cerr << "Error: close" << std::endl;
        throw std::runtime_error("Error: close");
    }
}
