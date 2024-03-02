#include "POSIXAddress.hpp"

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

void POSIXAddress::unlink()
{
    // Unlink the socket file
    ::unlink(m_addr.sun_path);
}

struct sockaddr *POSIXAddress::get_address()
{
    // Return the address
    return (struct sockaddr *)&m_addr;
}

socklen_t POSIXAddress::get_size()
{
    // Return the size of the address
    return sizeof(m_addr);
}