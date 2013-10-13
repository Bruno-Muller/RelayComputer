/*
 *  Registre.cpp
 *  PC
 *
 *  Created by Bruno Muller on 28/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Registre.h"

Registre::Registre(unsigned short int nbrBit, Bus *inputBus, Bus *outputBus) : m_mot(0), m_masque(0), m_inputBus(inputBus), m_outputBus(outputBus) {	
	unsigned short int masque;
	for (unsigned short int i(0); i<nbrBit; i++) {
		masque = (masque<<1) + 1;
	}
	m_masque = masque;
}

void Registre::setWord(unsigned short int mot) {
	m_mot = (mot & m_masque);
}

unsigned short int Registre::getWord() const {
	return m_mot;
}

unsigned short int Registre::getMasque() const {
	return m_masque;
}

void Registre::select() const {
	m_outputBus->setWord(Registre::getWord());
}

void Registre::load() {
	Registre::setWord(m_inputBus->getWord());
}
