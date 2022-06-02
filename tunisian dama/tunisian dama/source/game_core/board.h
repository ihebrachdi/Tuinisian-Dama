#pragma once

#include<glew.h>
#include"../maths/quads.h"
#include"../maths/mat4.h"
#include"../game_states.h"
#define ratio 70
#define moving_quade 25


class board {
public:	
	

	quade m_board[26];//one for the moving quade
	players m_player = NOPL;
	players m_enemy = NOPL;
	imatics::mat4 m_orthoprj;
	float m_vecteurw;
	imatics::vec2 m_portboard;
	imatics::vec3 m_lastmousspos;
	bool m_valispicking = false; //need it to check to enter mouss prssing 
	size_t m_nbrkill = 0;
private:
	imatics::vec3 m_vecteurpushx, m_vecteurpushy, m_startpoint;

public:
	board() = default;
	void createboard(size_t windoww, size_t windowh ,players player);
	
	//void movingquade(int xmouse, int ymouse);
	void redimensionBoard(size_t windoww, size_t windowh);
	bool checkmove(int newindex, int lastindex, unsigned short& destholder, unsigned short& targholder, char& modeofmove);
	bool pick(int pickindex, int& pickholder);
	void draw();
	void move_quade(double xpos, double ypos, float zpos);
private:
	void constraint(size_t windoww, size_t windowh);
	void swap(int newindex);




};