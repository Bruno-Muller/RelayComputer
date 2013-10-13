/*
 *  Memory.h
 *  PC
 *
 *  Created by Bruno Muller on 28/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DEF_MEMORY
#define DEF_MEMORY

#include "Bus.h"

class Memory {
	
public:
	Memory(Bus *adresseBus, Bus *dataBus); // Constructeur // Rajouter fichier
	unsigned short int getWord(unsigned short int adresse);
	void setWord(unsigned short int adresse, unsigned short int data);
	void read();
	void write();
	
	
private:
	Bus *m_adresseBus, *m_dataBus;	
	unsigned short int m_donnees[32768];
};

#endif