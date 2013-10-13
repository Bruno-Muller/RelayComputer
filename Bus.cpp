/*
 *  Bus.cpp
 *  PC
 *
 *  Created by Bruno Muller on 28/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Bus.h"

Bus::Bus(unsigned short int nbrBit) : m_mot(0), m_masque(0){
	unsigned short int masque;
	for (unsigned short int i(0); i<nbrBit; i++) {
		masque = (masque<<1) + 1;
	}
	m_masque = masque;
}

void Bus::setWord(unsigned short int mot) {
	m_mot =  (mot & m_masque);
}

unsigned short int Bus::getWord() const {
	return m_mot;
}

unsigned short int Bus::getMasque() const {
	return m_masque;
}

void Bus::pulldown() {
	m_mot = 0;
}