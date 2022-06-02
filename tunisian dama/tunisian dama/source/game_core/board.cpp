#include"board.h"
#include"../Log.h"

#include<glfw3.h>





void board::createboard(size_t windoww, size_t windowh , players player){
	m_player = player;
	m_enemy = player == players::WHITE ? players::BLACK : players::WHITE;
	constraint(windoww, windowh);
	players cell;
	cell = m_player;
	quade simplequad;
	simplequad *= m_vecteurw;

	int i = 0;
	for (int l = 0; l < 5; l++) {	
		for (int c = 0; c < 5; c++) {
			m_board[i]<=((simplequad + m_startpoint) + (c* (m_vecteurpushx)));
			
			if (i == 12)
				cell = NOPL;
			else if (i == 13) {
				if (m_player == WHITE)
					cell = BLACK;
				else
					cell = WHITE;
			}
			//Log(cell);
			m_board[i] < cell+i*10; 
			Log(i<<"  the player: "<<cell << "  with flag: "<< m_board[i].q_vertex->flag);
			/*Log(m_vecteurpushy);
			Log(m_startpoint);
			Log(i);*/
		//	Log(m_board[i]);


			i++;
		}
		m_startpoint.y += m_vecteurpushy.y;
	}
	m_board[25] = m_board[24];
	m_board[25] += imatics::vec3(0.0f, 0.0f, -20.0f);
	
	
	
}
void board::redimensionBoard(size_t windoww, size_t windowh) {
	constraint(windoww, windowh);
	quade simplequad;
	simplequad *= m_vecteurw;

	for (int i = 0, l = 0; l < 5; l++) {
		for (int c = 0; c < 5; c++) {
			m_board[i] <= ((simplequad + m_startpoint) + (c * (m_vecteurpushx)));
			i++;
		}
		m_startpoint.y += m_vecteurpushy.y;
		
	}
	m_board[25] = m_board[24];
	m_board[25] += imatics::vec3(0.0f, 0.0f, -20.0f);

}
void board::constraint(size_t windoww, size_t windowh) {
	float aspectratio ;
	m_portboard.x = windoww * 0.7f;
	m_portboard.y = windowh;
	if(m_portboard.y < m_portboard.x) //make in considration the aspect ratio
		aspectratio = m_portboard.y / m_portboard.x;
	else
		aspectratio = m_portboard.x / m_portboard.y;
	//aspectratio = 1;
	m_vecteurw = ((m_portboard.x * 0.7f) / 5) * aspectratio;
	m_vecteurpushx.x = m_vecteurw + ((m_portboard.x * 0.07f) * aspectratio / 5);//{->,0,0}
	float boardlength = (m_vecteurpushx.x * 5) - ((m_portboard.x * 0.07f) * aspectratio / 5);
	m_vecteurpushy.y = m_vecteurpushx.x;//{0,^,0}
	m_startpoint.x = -2.5f * m_vecteurpushx.x;
	m_startpoint.y = -(boardlength/2);//will not change only the y direction will increase by the vecteurpush
	//Log("start point:  " << m_startpoint.y);
	imatics::ortho(-m_portboard.x/2,m_portboard.x/2, -m_portboard.y/2, m_portboard.y/2, 10, -10, m_orthoprj);
	Log("calculating board  : "<<windoww << "\t" <<windowh);
	/*Log(m_portboard);
	Log(m_vecteurw);
	Log(m_vecteurpushx);
	Log(m_vecteurpushy);*/

}
bool board::checkmove(int newindex, int lastindex, unsigned short& destholder, unsigned short& targholder,char& modeofmove) {
	//check the move and swap the quade accordenly 
	//true only if there's a valide move and need to send data
	//you need to call this function only if the moving quade is active
	if (lastindex > 25)
		return false;

	int floor = lastindex / 5;
	int move = newindex - lastindex;
	
	switch (move) {
		case  1:
		case -1:
		case  5:
		case -5:
			if (floor == newindex / 5 || ((0 <= lastindex + move <= 24) && (move != 1 && move != -1))) {
				if (m_board[newindex].q_vertex[0].flag % 10 == NOPL) {
					destholder = m_board[newindex].q_vertex[0].flag;
					swap(newindex);
					modeofmove = 'm';
					return true;
				}
				else {
					swap(lastindex);
					return false;
				}
			}
			break;
		case   2:
		case  -2:
		case  10:
		case -10:
			

			if (floor == newindex / 5 || ((0 <= lastindex + move <= 24) && (move != 2 && move != -2))) {
				int targetindex = lastindex + (move / 2);
				
				if (m_board[targetindex].q_vertex[0].flag % 10 == m_enemy) {
					destholder = m_board[newindex].q_vertex[0].flag;
					targholder = m_board[targetindex].q_vertex[0].flag;
					swap(newindex);
					m_board[targetindex] < (m_board[targetindex].q_vertex[0].flag / 10)*10 + NOPL ;//to make it empty 
					modeofmove = 'k';
					m_nbrkill++;
					return true;
				}
				else {
					swap(lastindex);
					return false;
				}
			}
			break;
		default:
			Log("you didn't make any valid move")
			swap(lastindex);
			return false;
		}

}
void board::swap(int newindex) {
	//changing the newindex flag with myplayer flag
	//discard moving quade
	
	m_board[newindex] < ((m_board[newindex].q_vertex[0].flag / 10) * 10 ) + m_player ;
	m_board[moving_quade] += imatics::vec3(0.0f, 0.0f, -20.0f);
	
}

///work on that plz
bool board::pick(int pickindex,int& pickholder) {
	if (pickindex < 25) {
		Log("whos player your picking  : "<<m_board[pickindex].q_vertex[0].flag % 10);
		if (m_board[pickindex].q_vertex[0].flag % 10 == m_player) {
			m_board[moving_quade] = m_board[pickindex];
			m_board[moving_quade] < m_board[moving_quade].q_vertex->flag % 1000 + DISCARD; 
			pickholder = m_board[pickindex].q_vertex[0].flag;
			m_board[pickindex] < (((m_board[pickindex].q_vertex[0].flag / 10) * 10) + players::NOPL);
			Log("the new flag og the board that picked :  " << m_board[pickindex].q_vertex[0].flag);
			m_board[moving_quade] += imatics::vec3(0.0f, 0.0f, 0.5f);
			m_valispicking = true;
			return true;

		}
	}
	return false;
}

void board::move_quade(double xpos, double ypos ,float zpos) {
	imatics::vec3 vpush(float(xpos) -(float)m_portboard.x / 2,(float)m_portboard.y / 2 - float(ypos), 0.0f);
	vpush -= m_lastmousspos;
	m_board[moving_quade] += vpush;
	m_lastmousspos = imatics::vec3(float(xpos) - (float)m_portboard.x / 2, (float)m_portboard.y / 2 - float(ypos), 0.0f);

}
////
////to fix the viewport brfore drawing///
////
void board::draw() {
	glViewport(0, 0, (size_t)m_portboard.x, (size_t)m_portboard.y);
	//Log("the port board  : "<< (size_t)m_portboard.x <<"  "<< (size_t)m_portboard.y <<"in float "<< m_portboard.x <<"  "<< m_portboard.y)
}

