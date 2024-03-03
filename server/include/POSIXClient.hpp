#ifndef POSIX_CLIENT_HPP
#define POSIX_CLIENT_HPP

#include <memory>
#include <thread>
#include <mutex>
#include <boost/signals2.hpp>
#include "POSIXSocket.hpp"

class Server;

class POSIXClient
{
    std::unique_ptr<POSIXSocket> m_socket;
    Server &m_server;
    std::thread m_thread;
    std::mutex m_mutex;
    boost::signals2::connection m_conn;

public:
    POSIXClient() = delete;
    POSIXClient(std::unique_ptr<POSIXSocket> socket, Server &server);
    POSIXClient(const POSIXClient &) = delete;
    POSIXClient &operator=(const POSIXClient &) = delete;
    ~POSIXClient();
    void start();
    void stop();
};

#endif // POSIX_CLIENT_HPP