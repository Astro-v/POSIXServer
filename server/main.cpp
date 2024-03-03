#include "Server.hpp"
#include "DummyData.hpp"
#include <iostream>
#include <string>
#include <memory>

#include "POSIXSocket.hpp"
#include "POSIXListener.hpp"
#include "POSIXAddress.hpp"

int main()
{
    std::cout << "Starting server" << std::endl;
    /*POSIXAddress address("/tmp/POSIXSocketTest");
    POSIXListener listener;

    listener.listen(address);*/

    Server server(std::make_unique<DummyData>(), "/tmp/POSIXSocketTest");
    //  server.start();

    std::cout << "Closing server" << std::endl;
    return 0;
}