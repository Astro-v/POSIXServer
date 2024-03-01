#ifndef POSIX_SERVER_HPP
#define POSIX_SERVER_HPP

#include <string>
#include <vector>
#include <memory>
#include "IPOSIXServer.hpp"

class POSIXServer : public IPOSIXServer
{
    int server_fd;
    char buf[100];

public:
    POSIXServer();
    ~POSIXServer() override;
    void start() override;
    void run() override;
    void stop() override;
};

#endif // POSIX_SERVER_HPP