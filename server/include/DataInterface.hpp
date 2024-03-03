#ifndef DATA_INTERFACE_HPP
#define DATA_INTERFACE_HPP

#include <memory>
#include <boost/signals2.hpp>
class Server;

class DataInterface
{
protected:
    boost::signals2::connection m_conn;

public:
    DataInterface() = default;
    virtual ~DataInterface() = default;
    virtual void subscribe(Server &server) = 0;
};

#endif // DATA_INTERFACE_HPP