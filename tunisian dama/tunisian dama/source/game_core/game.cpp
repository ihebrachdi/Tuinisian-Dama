#include"game.h"


game::game(char who, imatics::Client* client) {
	Log("game is live");
	m_client = client;
	switch (who) {
	case 'B':
		Init(players::BLACK);
		break;
	case 'W':
		Init(players::WHITE);
		m_myturn = true;
		break;
		/*case 'G':
			Init(board::players::BLACK);
			m_guest = true;
			break;*/
	}
	
}

void game::run() {
	while (!window.windowclosed()) {
		m_render = true;
		while (!m_myturn) {
			if (window.m_isresize) {

				game_board.redimensionBoard(window.m_width, window.m_height);

				program_cube.use(true);
				imatics::ortho(-(window.m_width - game_board.m_portboard.x) / 2, (window.m_width - game_board.m_portboard.x) / 2, -window.m_height / 2, window.m_height / 2, 1000, -1000, m_orthocube);
				glUniformMatrix4fv(program_cube.findlocation("orth"), 1, GL_FALSE, m_orthocube.m_mat);
				program_picking.use(true);
				glUniformMatrix4fv(program_picking.findlocation("ortho"), 1, GL_FALSE, game_board.m_orthoprj.m_mat);
				program_board.use(true);
				glUniformMatrix4fv(program_board.findlocation("orth"), 1, GL_FALSE, game_board.m_orthoprj.m_mat);
				game_board.draw();


				m_render = true;
				window.m_isresize = false;
			}
			m_render = true;
			if (m_client->receivepackets()) {
				AnalysePacket();
				m_animation_state = 0;
				while (m_animation_state < 3) {
					if (m_time.Alarm(1)) {
						Logr("alarm end ");
						if (m_mode_game == 'm') {
							Log("it s a move");
							AnimateMove();
						}
						else {
							Log("it s a kill");
							AnimateKill();
						}
					}
					render();
				}

			}
			render();
		}
		while (m_myturn) {
			m_render = true;
			handelinput();
			render();
		}
		if (m_sendtoserver) {
			sf::Packet sendpacket;
			m_client->sendpacket(sendpacket);
		}

	}
}
///we creating the index every time you neeed to have a solution 
void game::render() {
	if (m_render) {
		glClear(/*GL_COLOR_BUFFER_BIT |*/ GL_DEPTH_BUFFER_BIT);
		//glClear(GL_COLOR_BUFFER_BIT);
		bg_vao.bind(true);
		glViewport(0, 0, window.m_width, window.m_height);
		program_bg.use(true);
		program_bg.draw(2);
		bg_vao.bind(false);

		cube_vao.bind(true);
		glViewport(game_board.m_portboard.x, 0, window.m_width - game_board.m_portboard.x, window.m_height );
		program_cube.use(true);
		imatics::rotation((float)glfwGetTime()* 50.0f, m_matrot);
		
		glUniformMatrix4fv(program_cube.findlocation("rotation"), 1, GL_FALSE, m_matrot.m_mat);
		program_cube.draw(12);
		cube_vao.bind(false);

		
		game_board.draw();
		program_board.use(true);
		//program_picking.use(true);
		board_vao.transferdata(game_board.m_board, 26 * sizeof(quade),52, GL_STATIC_DRAW);
		board_vao.bind(true);
		program_board.draw(52);
		//program_picking.draw(50);
		window.updatewindow(true);
		m_render = false;
	}
	else {
		window.updatewindow(false);
	}
}

bool game::handelinput() {
	double xpos, ypos;
	if (window.m_isresize) {
		
		game_board.redimensionBoard(window.m_width, window.m_height);

		program_cube.use(true);
		imatics::ortho(-(window.m_width - game_board.m_portboard.x) / 2, (window.m_width - game_board.m_portboard.x) / 2, -window.m_height / 2, window.m_height / 2, 1000, -1000, m_orthocube);
		glUniformMatrix4fv(program_cube.findlocation("orth"), 1, GL_FALSE, m_orthocube.m_mat);
		program_picking.use(true);
		glUniformMatrix4fv(program_picking.findlocation("ortho"), 1, GL_FALSE, game_board.m_orthoprj.m_mat);
		program_board.use(true);
		glUniformMatrix4fv(program_board.findlocation("orth"), 1, GL_FALSE, game_board.m_orthoprj.m_mat);
		game_board.draw();


		m_render = true;
		window.m_isresize = false;
	}
	
	if (window.m_mouse_pressed) {
		
		if (game_board.pick(getpickindex(),m_pickholder)){
	
			glfwGetCursorPos(window.m_window, &xpos, &ypos);
			game_board.m_lastmousspos = imatics::vec3(float(xpos) - (float)game_board.m_portboard.x / 2, (float)game_board.m_portboard.y / 2 - float(ypos), 0.0f);
			window.m_mouse_pressed = false;

			m_render = true;
			//hold the flag to send later
			m_source_quade = m_pickholder;

		}
		else {
			window.m_mouse_pressing = false;
		}
		
		return false;
	}
	else if (window.m_mouse_pressing) {

			glfwGetCursorPos(window.m_window, &xpos, &ypos);
			game_board.move_quade(xpos, ypos,0.5f);
			m_render = true;
	}
	else if (window.m_mouse_release && game_board.m_valispicking) {
			Log("you realese the mouss");
			int lastindex = fbo_picking.m_lastpickedindex;
			glfwGetCursorPos(window.m_window, &xpos, &ypos);
			if (game_board.checkmove(getpickindex(), lastindex , m_dest_quade,m_target_quade,m_mode_game)) {
				//send the data he make a valid move
				m_sendtoserver = true;
				if (m_nbrofkill != 12) {
					m_packetstring.clear();
					m_packetstring += 'c';
					m_packetstring += m_mode_game; //'cm' or 'ck'
					m_client->m_packet.clear();
					if (m_mode_game == 'm') {
						m_client->m_packet << m_packetstring << m_source_quade << m_dest_quade ;
					}
					else {
						m_client->m_packet << m_packetstring << m_source_quade << m_dest_quade << m_target_quade;
						Log("you' sending : " << m_packetstring << " " << m_source_quade << " " << m_dest_quade << " " << m_target_quade);
					}
				}
				else {
					m_packetstring.clear();
					m_packetstring += 'ek';
					m_client->m_packet.clear();
					m_client->m_packet << m_packetstring << m_source_quade << m_dest_quade << m_target_quade;
				}
				m_myturn = false;
			}
			m_render = true;
			window.m_mouse_release = false;
			game_board.m_valispicking = false;
		}
	return true;
}

int game::getpickindex() {
	imatics::vec3 indexv;
	double xpos, ypos;
	program_picking.use(true);
	fbo_picking.bind(imatics::vec3(0.0f, 0.55f, 0.33f));
	//drawfunction goes here
	program_board.draw(50);//don't draw the moving_quade
	//
	glfwGetCursorPos(window.m_window, &xpos, &ypos);
	indexv = fbo_picking.readpixel(xpos, ypos,window.m_height);
	fbo_picking.unbind(imatics::vec3(0.0f, 1.0f, 0.0f));

	program_board.use(true);
	Log((int)(indexv.y * 100.0f));
	return (int)(indexv.y * 100.0f);
}

void game::Init(players myplayer) {

	#include"cube.h"

	game_board.createboard(1080, 720, myplayer);
	//window.configport(&game_board);
	
	program_bg.use(true);
	
	float bgquade[] = {
						-1.0f,-1.0f,0.0f,0.0f,
						 1.0f,-1.0f,1.0f,0.0f,
						 1.0f, 1.0f,1.0f,1.0f,
						-1.0f, 1.0f,0.0f,1.0f
	};

	bg_vao.transferdata(bgquade, sizeof(bgquade), 2, GL_STATIC_DRAW);
	bg_vao.bind(true);
	bg_images.addtexture("source/images/bg.jpg",2);
	bg_vao.bind(false);

	program_cube.use(true);
	imatics::ortho(-(window.m_width - game_board.m_portboard.x) / 2, (window.m_width - game_board.m_portboard.x) / 2, -window.m_height / 2, window.m_height / 2, 1000, -1000, m_orthocube);
	
	imatics::rotation(100.0f, m_matrot);
	imatics::scale((window.m_width - game_board.m_portboard.x) / 4, m_matscalecube);

	glUniformMatrix4fv(program_cube.findlocation("rotation"), 1, GL_FALSE, m_matrot.m_mat);
	glUniformMatrix4fv(program_cube.findlocation("scale"), 1, GL_FALSE, m_matscalecube.m_mat);
	glUniformMatrix4fv(program_cube.findlocation("orth"), 1, GL_FALSE, m_orthocube.m_mat);
	glUniform1i(program_cube.findlocation("index"), (int)game_board.m_player);

	cube_vao.transferdata(cube, sizeof(cube), 12, GL_STATIC_DRAW);
	cube_vao.bind(true);
	cube_images.addtexture("source/images/lgb.png", 3);
	cube_images.addtexture("source/images/lgw.png", 4);
	cube_vao.bind(false);
	
	program_picking.use(true);
	glUniformMatrix4fv(program_picking.findlocation("ortho"), 1, GL_FALSE, game_board.m_orthoprj.m_mat);
	
	program_board.use(true);
	glUniformMatrix4fv(program_board.findlocation("orth"), 1, GL_FALSE, game_board.m_orthoprj.m_mat);
	
	
	
	
	float quadecolor[] = {
		1.0f,1.0f,1.0f,
		0.0f,1.0f,0.0f,
		1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,
		0.5f,0.0f,0.0f
	};
	glUniform3fv(program_board.findlocation("quadecolor"), 5, quadecolor);


	board_vao.transferdata(game_board.m_board, 26 * sizeof(quade), 52, GL_STATIC_DRAW);
	board_vao.bind(true);
	images.addtexture("source/images/black.png", 0);
	images.addtexture("source/images/white.png", 1);
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	game_board.draw();
	m_render = true;

	glEnable(GL_DEPTH_TEST);

}

//just change the index of flag and color of bg and *** let the player flag 
int flipindex(int flag , int color) {
	
	return (24 - ((flag % 1000) / 10)) * 10 + flag % 10 + color;
}

void game::AnimateKill() {
	int index, source, empty, dest, target;

	switch (m_animation_state) {
	case 0:
		source = flipindex( m_source_quade,GREEN);
		index = 24-((m_source_quade % 1000) / 10);
		game_board.m_board[index] < source;
		m_render = true;
		m_animation_state++;
		Log("m_animate state = 0");
		break;
	case 1:
		dest = flipindex(m_dest_quade, BLUE);
		index = 24-((m_dest_quade % 1000) / 10);
		game_board.m_board[index] < dest;
		Log("m_animate state = 1");

		target = flipindex(m_target_quade, RED);
		index = 24-((m_target_quade % 1000) / 10);
		game_board.m_board[index] < target;

		m_render = true;
		m_animation_state++;
		break;

	case 2://change the board
		empty = flipindex(m_source_quade, NONE) / 10;
		empty = (empty * 10) + NOPL;
		index = 24-((m_source_quade % 1000) / 10);
		game_board.m_board[index] < empty;

		empty = flipindex(m_target_quade, NONE) / 10;
		Log(m_target_quade);
		empty = (empty * 10) + NOPL;
		index = 24-((m_target_quade % 1000) / 10);
		game_board.m_board[index] < empty;

		
		dest = flipindex(m_dest_quade, NONE) / 10;
		dest = (dest * 10) + game_board.m_enemy;
		index = 24-((m_dest_quade % 1000) / 10);
		game_board.m_board[index] < dest;
		Log("m_animate state = 2");

		m_myturn = true;
		m_animation_state++;
		m_render = true;
		break;
	}

}
void game::AnimateMove() {
	int index, source, empty, dest;

	switch (m_animation_state) {

	case 0:
		source = flipindex(m_source_quade, GREEN);
		index = 24 - ((m_source_quade % 1000) / 10);
		Log("source "<<source);
		game_board.m_board[index] < source;
		m_render = true;
		m_animation_state++;
		break;
	case 1:
		dest = flipindex(m_dest_quade, BLUE);
		index = 24 - ((m_dest_quade % 1000) / 10);
		Log("dest " << dest);
		game_board.m_board[index] < dest;
		m_animation_state++;
		m_render = true;
		break;

	case 2://change the board
		empty = flipindex(m_source_quade, NONE) / 10;
		empty = (empty * 10) + NOPL;
		index = 24 - ((m_source_quade % 1000) / 10);
		Log("empty " << empty);
		game_board.m_board[index] < empty;

		empty = flipindex(m_dest_quade, NONE) / 10;
		empty = (empty * 10) + game_board.m_enemy;
		index = 24 - ((m_dest_quade % 1000) / 10);
		game_board.m_board[index] < empty;

		m_myturn = true;
		m_animation_state++;
		m_render = true;

		break;
	}
}

void game::AnalysePacket() {
	std::string recievedstring;
	m_client->m_packet >> recievedstring >> m_source_quade >> m_dest_quade >> m_target_quade;
	Logr("recived packet :" << recievedstring <<" -- " <<   m_source_quade << " -- " << m_dest_quade << " -- " << m_target_quade)
	if (recievedstring[0] == 'e') {
		m_end_game = true;
	}
	switch (recievedstring[1]) {
	case 'm':
		m_mode_game = 'm';
		Log(m_mode_game);
		break;
	case 'k':
		m_mode_game = 'k';
		Log(m_mode_game);
		break;
	default:
		Logr("the received message doesn't match any move");
	}

}