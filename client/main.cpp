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
    std::string message("Hello, World!");
    client.send(message);

    std::string message2("Goodbye, World!");
    client.send(message2);

    sleep(10);
    return 0;
}