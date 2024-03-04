#include "POSIXSocket.hpp"
#include "POSIXListener.hpp"
#include "POSIXAddress.hpp"
#include <iostream>
#include <string>

int main()
{
    std::cout << "Starting client" << std::endl;
    POSIXAddress address("/tmp/POSIXSocketTest");
    POSIXSocket client;
    client.connect(address);
    sleep(10);
    std::string message("Hello, World!");
    client.send(message);

    return 0;
}