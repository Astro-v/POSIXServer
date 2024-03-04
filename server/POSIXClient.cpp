#include "POSIXClient.hpp"
#include "Server.hpp"
#include <iostream>

POSIXClient::POSIXClient(std::unique_ptr<POSIXSocket> socket, Server &server)
    : m_socket(std::move(socket)), m_server(server)
{

    std::cout << "Starting client" << std::endl;
    m_conn = m_server.m_queries.connect([this](Query &q, POSIXClient &c)
                                        {
                        if (q.type == Query::Type::SEND)
                        {
                            // Send the message to the client
                            m_mutex.lock();
                            std::cout << "Sending" << q.message << std::endl;
                            m_socket->send(q.message);
                            m_mutex.unlock();
                        } });
}

POSIXClient::~POSIXClient()
{
    std::cout << "Stopping client destructor" << std::endl;
}

void POSIXClient::start()
{

    int output = 0;
    std::string message;
    while (output == 0)
    {
        std::cout << "Waiting for message" << std::endl;
        m_mutex.lock();
        output = m_socket->receive(message);
        m_mutex.unlock();
        if (output == 0)
        {
            Query q{message, Query::Type::RECEIVE};
            m_server.m_queries(q, *this);
        }
    }
    stop();
}

void POSIXClient::stop()
{
    m_conn.disconnect();
    m_server.remove_client(this);

    std::cout << "Stopping client stop" << std::endl;
}