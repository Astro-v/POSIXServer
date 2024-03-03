#include "POSIXServer.hpp"
#include "Server.hpp"
#include <iostream>

POSIXServer::POSIXServer(POSIXAddress address, Server &server)
    : m_server(server)
{
    POSIXAddress t_address("/tmp/POSIXSocketTest");
    m_listener.listen(t_address);
}

POSIXServer::~POSIXServer()
{
    stop();
}

void POSIXServer::start()
{
    while (true)
    {
        auto client = m_listener.accept();
        if (client)
        {
            m_server.add_client(std::make_unique<POSIXClient>(std::move(client), m_server));
            std::cout << "Client connected" << std::endl;
        }
    }
}

void POSIXServer::stop()
{
    std::cout << "Server stopped" << std::endl;
}