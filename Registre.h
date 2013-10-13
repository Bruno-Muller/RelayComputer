/*
 *  Registre.h
 *  PC
 *
 *  Created by Bruno Muller on 28/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DEF_REGISTRE
#define DEF_REGISTRE

#include "Bus.h"

class Registre {
	
public:
	Registre(unsigned short int nbrBit, Bus *inputBus, Bus *outputBus); // Constructeur
	void setWord(unsigned short int mot);
	unsigned short int getWord() const;
	unsigned short int getMasque() const;
	void select() const;
	void load();
	
private:
	unsigned short int m_mot, m_masque;
	Bus *m_inputBus, *m_outputBus;
	
};

#endif
