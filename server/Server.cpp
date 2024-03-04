#include "Server.hpp"

#include <iostream>

Server::Server(std::unique_ptr<DataInterface> data_interface, std::string address)
    : m_data_interface(std::move(data_interface)), m_address(address), m_server(m_address, *this)
{

    std::cout << "Initializing server" << std::endl;
    m_data_interface->subscribe(*this);
}

Server::~Server()
{
    stop();
}

void Server::start()
{

    std::cout << "Starting server" << std::endl;
    m_server.start();
}

void Server::stop()
{
    m_server.stop();
}

void Server::add_client(std::unique_ptr<POSIXClient> client)
{
    m_clients.push_back(std::move(client));
}

void Server::remove_client(POSIXClient *client)
{
    auto it = std::find_if(m_clients.begin(), m_clients.end(),
                           [client](const std::unique_ptr<POSIXClient> &c)
                           {
                               return c.get() == client;
                           });
    if (it != m_clients.end())
    {
        m_clients.erase(it);
    }
}
