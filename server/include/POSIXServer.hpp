#ifndef POSIX_SERVER_HPP
#define POSIX_SERVER_HPP

#include <string>
#include <memory>
#include "POSIXListener.hpp"
#include "POSIXAddress.hpp"

class Server;

class POSIXServer
{
    POSIXListener m_listener;
    Server &m_server;

public:
    POSIXServer() = delete;
    POSIXServer(POSIXAddress address, Server &server);
    ~POSIXServer();
    POSIXServer(const POSIXServer &) = delete;
    POSIXServer &operator=(const POSIXServer &) = delete;
    void start();
    void stop();
};

#endif // POSIX_SERVER_HPP