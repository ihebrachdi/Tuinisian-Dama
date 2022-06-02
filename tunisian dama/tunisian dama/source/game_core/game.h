#pragma once
#include"../includes.h"
#include"../Network/clientnet.h"
#include"../System/time.h"





class game {
public:
	unsigned int cube_elem[36] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3,
	};
	imatics::mat4 m_orthocube;
	imatics::mat4 m_matscalecube;
public:
	imatics::Window window = imatics::Window("A Good Place As Any", 1080, 720);

	imatics::program program_board = imatics::program("source/files/shaders/vertex.shader", "source/files/shaders/fragment.shader");
	imatics::program program_picking = imatics::program("source/files/shaders/vertex_picking.shader", "source/files/shaders/fragment_picking.shader");
	imatics::program program_bg = imatics::program("source/files/shaders/vertexbg.shader", "source/files/shaders/fragmentbg.shader");
	imatics::program program_cube = imatics::program("source/files/shaders/vertexcube.shader", "source/files/shaders/fragmentcube.shader");

	imatics::texture images = imatics::texture(program_board.findlocation("textureunits"), 2);
	imatics::texture bg_images = imatics::texture(program_bg.findlocation("textureunit"), 1);
	imatics::texture cube_images = imatics::texture(program_cube.findlocation("textureunit"), 2);

	imatics::basicbuffer board_vao = imatics::basicbuffer("3f1f2f", createindexquade(26));
	imatics::basicbuffer bg_vao = imatics::basicbuffer("2f2f", createindexquade(1));
	imatics::basicbuffer cube_vao = imatics::basicbuffer("3f2f", cube_elem);

	imatics::picking fbo_picking = imatics::picking(imatics::vec2(float(window.m_width),float(window.m_height)));
	imatics::Client* m_client;
	board game_board;
	bool m_guest = false;
	bool m_myturn = false;
	bool m_render = false;
	bool m_sendtoserver = false;
	std::string m_packetstring;
	char m_end_game;
	char m_mode_game;
	unsigned short m_source_quade;
	unsigned short m_dest_quade;
	unsigned short m_target_quade;
	imatics::Time m_time;
	size_t m_nbrofkill = 0;
	unsigned int m_animation_state = 0;
	int m_pickholder;
	imatics::mat4 m_matrot;

public:
	game(char who, imatics::Client* client);
	void run();
	bool handelinput();
	int getpickindex();
	void render();
	
private:
	void Init(players myplayer);
	void AnimateKill();
	void AnimateMove();
	void AnalysePacket();

};