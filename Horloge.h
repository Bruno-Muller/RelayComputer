/*
 *  Horloge.h
 *  PC
 *
 *  Created by Bruno Muller on 28/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DEF_HORLOGE
#define DEF_HORLOGE

class Horloge {
	
public:
	Horloge(); // Constructeur
	unsigned short int getClock();
	void resetClock();
	void incClock();
	bool getReset();
	
	
private:
	unsigned short int m_clock, m_nbrCyclesMax;
	bool m_resetNextTime;
};
#endif
