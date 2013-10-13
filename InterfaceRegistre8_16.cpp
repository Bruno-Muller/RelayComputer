/*
 *  InterfaceRegistre8_16.cpp
 *  PC
 *
 *  Created by Bruno Muller on 28/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "InterfaceRegistre8_16.h"

InterfaceRegistre8_16::InterfaceRegistre8_16(Registre *registreH, Registre *registreL, Bus *inputBus, Bus *outputBus) : m_registreL(registreL), m_registreH(registreH), m_inputBus(inputBus), m_outputBus(outputBus) {
}

unsigned short int InterfaceRegistre8_16::getWord() const {
	return (m_registreH->getWord()<<8) + m_registreL->getWord();
}

void InterfaceRegistre8_16::select() const {
	m_outputBus->setWord((m_registreH->getWord()<<8) + m_registreL->getWord());
}

void InterfaceRegistre8_16::load() {
	m_registreH->setWord(m_inputBus->getWord()>>8);
	m_registreL->setWord(m_inputBus->getWord() & 0x00FF);
}