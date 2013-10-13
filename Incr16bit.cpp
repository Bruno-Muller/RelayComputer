/*
 *  Incr16bit.cpp
 *  PC
 *
 *  Created by Bruno Muller on 28/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Incr16bit.h"

Incr16bit::Incr16bit(Bus *inputBus, Bus *outputBus) : m_inputBus(inputBus), m_outputBus(outputBus) {	
}

unsigned short int Incr16bit::getWord() const {
	return (m_inputBus->getWord() + 1);
}


void Incr16bit::compute() const {
	m_outputBus->setWord(Incr16bit::getWord());
}
