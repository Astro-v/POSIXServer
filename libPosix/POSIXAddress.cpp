#include "POSIXAddress.hpp"
#include <iostream>
#include <stdexcept>

POSIXAddress::POSIXAddress(const std::string &path)
{
    POSIXAddress(path.c_str());
}

POSIXAddress::POSIXAddress(const char *path)
{
    // Set the address family to POSIX (AF_UNIX)
    m_addr.sun_family = AF_UNIX;

    // Copy the path to the address
    strncpy(m_addr.sun_path, path, sizeof(m_addr.sun_path) - 1);
}

POSIXAddress::POSIXAddress(const POSIXAddress &other)
{
    // Copy the address

    m_addr.sun_family = AF_UNIX;
    strncpy(m_addr.sun_path, other.m_addr.sun_path, sizeof(m_addr.sun_path) - 1);
}

/**
 * @brief Unlink the socket file
 * @return void
 */
void POSIXAddress::unlink()
{
    // Unlink the socket file
    int output = ::unlink(m_addr.sun_path);
    if (output == -1)
    {
        if (errno == EACCES)
        {
            std::cerr << "Error: EACCES" << std::endl;
            throw std::runtime_error("Error: EACCES");
        }
        else if (errno == EBUSY)
        {
            std::cerr << "Error: EBUSY" << std::endl;
            throw std::runtime_error("Error: EBUSY");
        }
        else if (errno == ENOENT)
        {
            std::cerr << "Error: ENOENT" << std::endl;
            throw std::runtime_error("Error: ENOENT");
        }
        else if (errno == EPERM)
        {
            std::cerr << "Error: EPERM" << std::endl;
            throw std::runtime_error("Error: EPERM");
        }
        else if (errno == EROFS)
        {
            std::cerr << "Error: EROFS" << std::endl;
            throw std::runtime_error("Error: EROFS");
        }
    }
}

/**
 * @brief Get the address
 * @return The address
 */
struct sockaddr *POSIXAddress::get_address()
{
    // Return the address
    return (struct sockaddr *)&m_addr;
}

/**
 * @brief Get the size of the address
 * @return The size of the address
 */
socklen_t POSIXAddress::get_size()
{
    // Return the size of the address
    return sizeof(m_addr);
}