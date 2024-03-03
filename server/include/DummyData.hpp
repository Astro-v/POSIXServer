#ifndef DUMMY_DATA_HPP
#define DUMMY_DATA_HPP

#include <string>
#include <iostream>
#include "Query.hpp"
#include "DataInterface.hpp"
#include "Server.hpp"
#include "POSIXClient.hpp"

class DummyData : public DataInterface
{
public:
    DummyData() = default;
    ~DummyData() = default;

    void subscribe(Server &server) override
    {
        m_conn = server.m_queries.connect([this](Query &q, POSIXClient &client)
                                          {
                if (q.type == Query::Type::RECEIVE)
                {
                    // Send the message to the client
                    std::cout << "RECEIVE : " << q.message << std::endl;
                } });
    }
};

#endif // DUMMY_DATA_HPP