#include "server.h"

ServerNetwork::ServerNetwork(unsigned short port = 53000) : m_listenport(port) {

    if (listener.listen(m_listenport) != sf::Socket::Done) {
        
        log("Could not listen Try another port number: ");
    }
}

void ServerNetwork::ConnectClients(std::vector<sf::TcpSocket*>* client_array) {
    while (true) {
        sf::TcpSocket* new_client = new sf::TcpSocket();
        if (listener.accept(*new_client) == sf::Socket::Done) {
            
            new_client->setBlocking(false);
            client_array->push_back(new_client);
            log("Connect client " << new_client->getRemoteAddress() << ":" << new_client->getRemotePort());
            //////////send B AND W to the player////////////
            
            if(m_nbrplayer < 2){  
                sf::Packet packet;
                std::string playerflag;
                if (m_nbrplayer == 0) {
                    playerflag = "W";
                    packet << playerflag;
                    if (new_client->send(packet) != sf::Socket::Done) {
                        log("Could not send packet to player B");
                    }
                   
                }
                else {
                    playerflag = "B";
                    packet << playerflag;
                    if (new_client->send(packet) != sf::Socket::Done) {
                        log("Could not send packet to player W");
                    }
                    
                }
                m_nbrplayer++;
            }
            else {
                sf::Packet packet;
                char playerflag = 'G';
                packet << playerflag;
                for (int i = 0; i < 10; i++) {
                    packet << m_board[i];
                }
                if (new_client->send(packet) != sf::Socket::Done) {
                    log("Could not send packet to player G");
                }
            }
        }
        else {
            log("ERROR: restart the server");
            delete(new_client);
            break;
        }
    }
}

void ServerNetwork::DisconnectClient(sf::TcpSocket* socket_pointer, size_t position) {
    log("Client  disconnected :" << socket_pointer->getRemoteAddress());
    socket_pointer->disconnect();
    delete(socket_pointer);
    client_array.erase(client_array.begin() + position);
}

void ServerNetwork::BroadcastPacket(sf::Packet& packet, sf::IpAddress exclude_address, unsigned short port) {
    for (size_t iterator = 0; iterator < client_array.size(); iterator++) {
        sf::TcpSocket* client = client_array[iterator];
        if (client->getRemoteAddress() != exclude_address || client->getRemotePort() != port) {
            if (client->send(packet) != sf::Socket::Done) {
                log("Could not send packet on broadcast");
            }
        }
    }
}



void ServerNetwork::ReceivePacket(sf::TcpSocket* client, size_t iterator) {
    sf::Packet packet;
    if (client->receive(packet) == sf::Socket::Disconnected) {
        DisconnectClient(client, iterator);
    }
    else {
        if (packet.getDataSize() > 0) {
          
            BroadcastPacket(packet, client->getRemoteAddress(), client->getRemotePort());
            std::string received_message;
            packet >> received_message;
            log(client->getRemoteAddress().toString() << ":" << client->getRemotePort() << " - " << received_message << ";");
        }
        
    }
}

void ServerNetwork::ManagePackets() {
    while (true) {
        for (size_t it = 0; it < client_array.size(); it++) {
             ReceivePacket(client_array[it], it);
        }

        std::this_thread::sleep_for((std::chrono::milliseconds)100);
    }
}

int ServerNetwork::readflagindex(short int flag)const {
    int iflag = flag;
    return (iflag % 1000) / 10;
}

void ServerNetwork::putflagboard(short int flag) {
    m_board[readflagindex(flag)] = flag;
}

void ServerNetwork::Run() {
    std::thread connetion_thread(&ServerNetwork::ConnectClients, this, &client_array);

    ManagePackets();
}
