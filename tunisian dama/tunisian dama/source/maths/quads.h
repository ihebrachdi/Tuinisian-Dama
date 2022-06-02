#pragma once
#include<ostream>
#include<stdint.h>
#include"vec2.h"
#include"vec3.h"



struct vertex {
	imatics::vec3 position;
	int flag = 0;
	imatics::vec2 textcoor;
};
struct quade {
	vertex q_vertex[4];
	quade()
	{
		q_vertex[1].position = { 1.0f,0.0f,0.0f };
		q_vertex[2].position = { 1.0f,1.0f,0.0f };
		q_vertex[3].position = { 0.0f,1.0f,0.0f };

		/******texture coordinate ******/
		q_vertex[0].textcoor = { 0.0f,0.0f };
		q_vertex[1].textcoor = { 1.0f,0.0f };
		q_vertex[2].textcoor = { 1.0f,1.0f };
		q_vertex[3].textcoor = { 0.0f,1.0f };
	}
};

quade& operator+=(quade& lquade, const imatics::vec3 rvec3);
quade& operator*=(quade& lquade, const float rnbr);

quade operator+(quade lquade, const imatics::vec3 rvec3);

std::ostream& operator<<(std::ostream& lstream, const quade& rquade);

void operator<=(quade& lquade, const quade& rquade);//just copying the position 
void operator<(quade& lquade, const int& rflag);//just copying the flag 

unsigned int* createindexquade(unsigned int quadenbr);