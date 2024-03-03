#ifndef SERVER_HPP
#define SERVER_HPP

#include <memory>
#include <vector>
#include <boost/signals2.hpp>
#include "POSIXServer.hpp"
#include "POSIXClient.hpp"
#include "POSIXAddress.hpp"
#include "DataInterface.hpp"
#include "Query.hpp"

class Server
{
    POSIXServer m_server;
    std::vector<std::unique_ptr<POSIXClient>> m_clients;
    std::unique_ptr<DataInterface> m_data_interface;
    POSIXAddress m_address;

public:
    boost::signals2::signal<void(Query &, POSIXClient &)> m_queries;

    Server() = delete;
    Server(std::unique_ptr<DataInterface> data_interface, std::string address);
    ~Server();
    void start();
    void stop();
    void add_client(std::unique_ptr<POSIXClient> client);
    void remove_client(POSIXClient *client);
};

#endif // SERVER_HPP