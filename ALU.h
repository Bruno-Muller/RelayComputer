/*
 *  ALU.h
 *  PC
 *
 *  Created by Bruno Muller on 27/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DEF_ALU
#define DEF_ALU

#include "Bus.h"
#include "Registre.h"

class ALU {
	
public:
	ALU(Registre *registre1, Registre *registre2, Bus *outputBus); // Constructeur
	void setBitCode(unsigned short int numBit, bool valeur);
	unsigned short int getCode();
	unsigned short int getResult();
	bool getZ();
	bool getCy();
	bool getS();
	void loadFlags();


	
private:
	Registre *m_registre1, *m_registre2;
	Bus *m_outputBus;
	bool Z, Cy, S;
        unsigned short int m_resultat;
	bool m_bitCode[3];
	
	void compute();
	void writeOnBus();
	
	
	
};

#endif
