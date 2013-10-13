/*
 *  Bus.h
 *  PC
 *
 *  Created by Bruno Muller on 28/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef DEF_BUS
#define DEF_BUS

class Bus {
	
public:
	Bus(unsigned short int nbrBit); // Constructeur
	void setWord(unsigned short int mot);
	unsigned short int getWord() const;
	unsigned short int getMasque() const;
	void pulldown();
	
private:
	unsigned short int m_mot, m_masque;
	
};

#endif