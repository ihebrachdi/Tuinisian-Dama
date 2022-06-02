#include"quads.h"



quade& operator+=(quade& lquade, const imatics::vec3 rvec3) {
	for (int i = 0; i < 4; i++) {
		lquade.q_vertex[i].position += rvec3;
	}
	return lquade;
}
quade& operator*=(quade& lquade, const float rnbr) {
	for (int i = 0; i < 4; i++) {
		lquade.q_vertex[i].position *= rnbr;
	}
	return lquade;
}

quade operator+(quade lquade, const imatics::vec3 rvec3) {
	for (int i = 0; i < 4; i++) {
		lquade.q_vertex[i].position += rvec3;
	}
	return lquade;
}

std::ostream& operator<<(std::ostream& lstream, const quade& rquade) {
	return lstream << "| "<< rquade.q_vertex[0].position.x <<"  "<< rquade.q_vertex[0].position.y << "  " << rquade.q_vertex[0].position.z << " |\n" <<
		"| " << rquade.q_vertex[1].position.x << "  " << rquade.q_vertex[1].position.y << "  " << rquade.q_vertex[1].position.z << " |\n" <<
		"| " << rquade.q_vertex[2].position.x << "  " << rquade.q_vertex[2].position.y << "  " << rquade.q_vertex[2].position.z << " |\n" <<
		"| " << rquade.q_vertex[3].position.x << "  " << rquade.q_vertex[3].position.y << "  " << rquade.q_vertex[3].position.z << " |\n";
}

unsigned int* createindexquade(unsigned int quadenbr) {
	unsigned int* t = new unsigned int[quadenbr * 6];
	int push = 0;
	for (unsigned int i = 0; i < quadenbr * 6; i += 6) {

		t[0 + i] = 0 + push * 4;
		t[1 + i] = 1 + push * 4;
		t[2 + i] = 2 + push * 4;
		t[3 + i] = 2 + push * 4;
		t[4 + i] = 3 + push * 4;
		t[5 + i] = 0 + push * 4;

		push++;
	}
	return t;
}

//to copy just position
void operator<=(quade& lquade, const quade& rquade) {
	for (int i = 0; i < 4; i++) {
		lquade.q_vertex[i].position = rquade.q_vertex[i].position;
	}
}

void operator<(quade& lquade, const int& rflag) {
	for (int i = 0; i < 4; i++) {
		lquade.q_vertex[i].flag = rflag;
	}
}