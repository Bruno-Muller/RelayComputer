/*
 *  InterfaceRegistre8_16.h
 *  PC
 *
 *  Created by Bruno Muller on 28/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DEF_INTERFACE_REGISTRE8_16
#define DEF_INTERFACE_REGISTRE8_16

#include "Registre.h"
#include "Bus.h"

class InterfaceRegistre8_16 {
	
public:
	InterfaceRegistre8_16(Registre *registreH, Registre *registreL, Bus *inputBus, Bus *outputBus); // Constructeur
//	void setWord(unsigned short int mot);
	unsigned short int getWord() const;
	void select() const;
	void load();
	
private:
	Registre *m_registreL, *m_registreH;
	Bus *m_inputBus, *m_outputBus;
	
};

#endif