/*
 *  EEPROM.h
 *  PC
 *
 *  Created by Bruno Muller on 28/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DEF_EEPROM
#define DEF_EEPROM

#include <string>
#include <fstream>

class EEPROM {
	
public:
	EEPROM(std::string nomFichier); // Constructeur // Rajouter fichier
	unsigned short int getWord(unsigned short int adresse);
		void setWord(unsigned short int adresse, unsigned short int data);
		
private:
	unsigned short int m_donnees[65536];
};

#endif