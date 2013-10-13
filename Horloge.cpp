/*
 *  Horloge.cpp
 *  PC
 *
 *  Created by Bruno Muller on 28/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Horloge.h"

Horloge::Horloge() : m_clock(0), m_resetNextTime(false) {
}

void Horloge::resetClock() {
	m_resetNextTime = true;
}

unsigned short int Horloge::getClock() {
	return m_clock;
}

void Horloge::incClock() {
	if (m_resetNextTime) {
		m_clock=0;
		m_resetNextTime = false;
	}
	else {
		m_clock++;
	}

}

bool Horloge::getReset() {
    return m_resetNextTime;
}
