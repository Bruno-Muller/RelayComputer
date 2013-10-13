/*
 *  Incr16bit.h
 *  PC
 *
 *  Created by Bruno Muller on 28/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DEF_INCR_16_BITS
#define DEF_INCR_16_BITS

#include "Bus.h"

class Incr16bit {
	
public:
	Incr16bit(Bus *inputBus, Bus *outputBus); // Constructeur
	unsigned short int getWord() const;
	void compute() const;
	
private:
	Bus *m_inputBus, *m_outputBus;	
};

#endif