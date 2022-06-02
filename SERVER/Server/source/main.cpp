
#include"server.h"


int main(int argc, char* argv[]) {
    log("Server __Iheb_Rachdi__ ");
    log("Your local Address: " << sf::IpAddress::getLocalAddress().toString());
    log("your public Address: " << sf::IpAddress::getPublicAddress().toString());
    unsigned short  portnbr;
    log("port number expl(53000) :");
    std::cin >> portnbr;
    ServerNetwork server_network(portnbr);
    server_network.Run();
    return 0;

}
