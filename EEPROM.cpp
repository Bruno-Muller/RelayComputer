/*
 *  EEPROM.cpp
 *  PC
 *
 *  Created by Bruno Muller on 28/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include <iostream>
#include "EEPROM.h"

EEPROM::EEPROM(std::string nomFichier) {
	std::ifstream fichier(nomFichier.c_str(), std::ios::in | std::ios::binary);
	
	if (fichier) {
		for (unsigned int adresse(0); adresse<65536; adresse++){
			char code;
			fichier.get(code);
			m_donnees[adresse] = ((unsigned short int) code) & 0x00FF;
			//if (m_donnees[adresse]!=0) std::cout<< nomFichier << ":" << adresse << "->" << m_donnees[adresse] << std::endl;
		}
		fichier.close();
	}
}

unsigned short int EEPROM::getWord(unsigned short int adresse) {
	return m_donnees[adresse];
}

void EEPROM::setWord(unsigned short int adresse, unsigned short int data) {
	m_donnees[adresse] = (data & 0x00FF);
}
