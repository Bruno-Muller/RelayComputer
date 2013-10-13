/*
 *  ALU.cpp
 *  PC
 *
 *  Created by Bruno Muller on 27/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ALU.h"

ALU::ALU(Registre *registre1, Registre *registre2, Bus *outputBus) : Z(false), Cy(false), S(false), m_resultat(0), m_registre1(registre1), m_registre2(registre2), m_outputBus(outputBus) {	
	for (unsigned short int i(0); i<3; i++) {
		m_bitCode[i] = true; //false
	}
}

void ALU::compute() {
	switch (ALU::getCode()) {
		case 0: // 0b000 -> ADD 
			m_resultat =  m_registre1->getWord() + m_registre2->getWord();
			ALU::writeOnBus();
			break;
		case 1: // 0b001 -> INC
			m_resultat = m_registre1->getWord()+1;
			ALU::writeOnBus();
			break;
		case 2: // 0b010 -> AND
			m_resultat = (m_registre1->getWord() & m_registre2->getWord()) & 0x00FF;
			ALU::writeOnBus();
			break;
		case 3: // 0b011 -> OR
			m_resultat = (m_registre1->getWord() | m_registre2->getWord()) & 0x00FF;
			ALU::writeOnBus();
			break;
		case 4: // 0b100 -> XOR
			m_resultat = (m_registre1->getWord() ^ m_registre2->getWord()) & 0x00FF;
			ALU::writeOnBus();
			break;
		case 5: // 0b101 -> NOT
			m_resultat = (~m_registre1->getWord()) & 0x00FF;
			ALU::writeOnBus();
			break;
		case 6: // 0b110 -> SHL
			m_resultat = ((m_registre1->getWord()<<1) + (m_registre1->getWord()>>7)) & 0x00FF;
			ALU::writeOnBus();
			break;
		case 7: // 0b111 -> pas utilisé
			m_resultat = 0;
			break;
		default :
			m_resultat  = 0;			
	}
	
}

void ALU::writeOnBus() {
	m_outputBus->setWord(m_resultat & 0x00FF);
}


void ALU::setBitCode(unsigned short int numBit, bool valeur) {
	m_bitCode[numBit] = valeur;
	ALU::compute();
}

unsigned short int ALU::getCode() {
	unsigned short int code;
	code = (m_bitCode[2]<<2) + (m_bitCode[1]<<1) + m_bitCode[0];
	return code;
}

unsigned short int ALU::getResult() {
	ALU::compute();
	return (m_resultat & 0x00FF);
}

void ALU::loadFlags() {
	ALU::compute(); //?
	
	// On récupère Cy
	if (m_resultat & 0x0100) {
		Cy = true;
	}
	else {
		Cy = false;
	}
	
	// On récupère S	
	if (m_resultat & 0x0080) {
		S = true;
	}
	else {
		S = false;
	}
	
	// On récupère Z (ALU::getResult() pour ne pas avoir Cy)
	if ((m_resultat & 0x00FF) == 0) {
		Z = true;
	}
	else {
		Z = false;
	}
}

bool ALU::getZ() {
	return Z;
}

bool ALU::getCy() {
	return Cy;
}

bool ALU::getS() {
	return S;
}
