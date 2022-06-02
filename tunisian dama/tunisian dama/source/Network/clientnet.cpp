#include"clientnet.h"
#include"../Log.h"

namespace imatics {
	Client::Client() {
		Log("client started");
	}
	void Client::connecttoserver(const char* address, unsigned short port) {
		if (m_socket.connect(address, port) != sf::Socket::Done) {
			Logr("Could not connect to server try again \n");
		}
		else {
			m_isConnected = true;
			Logr("Connected to  __Iheb_Rachdi_ server\n");

		}
	}
	

	bool Client::receivepackets() {
		if (m_socket.receive(m_packet) == sf::Socket::Done) {
			return true;
		}
		else {
			return false;
		}

	}

	void Client::sendpacket(sf::Packet& packet) {
		if (m_packet.getDataSize() > 0 && m_socket.send(m_packet) != sf::Socket::Done) {
			Logr("ERROR: Could not send packet");
		}
		std::string teststr;
		short int testsource, testdest;
		m_packet >> teststr >> testsource >> testdest;
		Logr(teststr << "----- " << testsource << "---- " << testdest);
		m_packet.clear();
	}
}