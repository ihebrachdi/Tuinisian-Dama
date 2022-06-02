#pragma once
#include <SFML/Network.hpp>

namespace imatics {
	class Client {
	public:
		sf::TcpSocket m_socket;
		sf::Packet m_packet;
		bool m_isConnected = false;
	public:
		Client();
		void connecttoserver(const char* address, unsigned short port);
		bool receivepackets();
		void sendpacket(sf::Packet& packet);
	
	};
}