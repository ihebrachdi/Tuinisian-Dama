#include"Log.h"
#include<glew.h>
#include<glfw3.h>
#include"display/Window.h"
#include"files/program.h"
#include"maths/quads.h"
#include"game_core/board.h"
#include"render/basicbuffer.h"
#include"maths/mat4.h"
#include"render/Texture.h"
#include"render/pickingsystem.h"
#include"game_core/game.h"
#include"Network/clientnet.h"


int main(int argc,char* argv[]) {
#if 1
	imatics::Client client;
	std::string serverip;
	unsigned short port;
	std::string whoami; 
	
	while (!client.m_isConnected) {
		Logr("Enter ServerIp : ");
		std::cin >> serverip;
		Logr("Enter a Port Number : ");
		std::cin >> port;
		client.connecttoserver(serverip.c_str(), port);
	}
	if (client.m_socket.receive(client.m_packet) == sf::Socket::Done) {
		client.m_packet >> whoami;
		Logr("whoami : " << whoami[0]);
		client.m_packet.clear();
		client.m_socket.setBlocking(false);
	}
	else {
		Logr("Failed to obtain response");
		whoami = "B";
		client.m_socket.setBlocking(false);
	}
	game dama(whoami[0], &client);
	
	dama.run();
	return 0;
#endif
#if 0
	game dama;
	dama.run();
	return 0;
#endif
	
}


