#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <string.h>
#include <SFML/Network.hpp>


#define log(x) std::cout <<  x << std::endl

class ServerNetwork {
    sf::TcpListener listener;
    std::vector<sf::TcpSocket*> client_array;
    unsigned short m_listenport;
    bool rawMode = false;
private:
    size_t m_nbrplayer = 0;
    unsigned int m_board[10];
public:
    ServerNetwork(unsigned short);
    void ConnectClients(std::vector<sf::TcpSocket*>*);
    void DisconnectClient(sf::TcpSocket*, size_t);

    void ReceivePacket(sf::TcpSocket*, size_t);

    void BroadcastPacket(sf::Packet&, sf::IpAddress, unsigned short);

    void ManagePackets();
    void Run();
private:
    int readflagindex(short int flag)const;
    void putflagboard(short int flag);
    
};
