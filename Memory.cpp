/*
 *  Memory.cpp
 *  PC
 *
 *  Created by Bruno Muller on 28/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Memory.h"

Memory::Memory(Bus *adresseBus, Bus *dataBus) : m_adresseBus(adresseBus), m_dataBus(dataBus) {	
	unsigned short int adresse(0);
	/*
	for (unsigned short int destination(0); destination < 8; destination++) {
		for (unsigned short int source(0); source <8; source++) {
			m_donnees[adresse] = source + (destination<<3);
			adresse++;
		}
	}
	for (unsigned short int destination(0); destination <2; destination++) {
		for (unsigned short int fonction(0); fonction < 7; fonction++) {
			m_donnees[adresse] = 0x80 + (destination<<3) + fonction;
			adresse++;
		}
	}
	for (unsigned short int destination(0); destination <2; destination++) {
		for (unsigned short int valeur(0); valeur < 0x20; valeur++) {
			m_donnees[adresse] = 0x40 + (destination<<5) + valeur;
			adresse++;
		}
	}
	m_donnees[adresse] = 0xB0;
	adresse++;
	for (unsigned short int destination(0); destination<4; destination++) {
		m_donnees[adresse] = 0x90 + destination;
		adresse++;
	}
	for (unsigned short int destination(0); destination<4; destination++) {
		m_donnees[adresse] = 0x98 + destination;
		adresse++;
	}
	
	
	// Intestable
	for (unsigned short int destination(0); destination < 2; destination++) {
		for (unsigned short int source(0); source <4; source++) {
			m_donnees[adresse] = 0xA0 + (source<<1) + (destination<<3);
			adresse++;
		}
	}
	m_donnees[adresse] = 0xAA;
	adresse++;

	m_donnees[adresse] = 0xC0;
	adresse++;
	m_donnees[adresse] = 0x00;
	adresse++;
	m_donnees[adresse] = 0xFF;
	adresse++;
	*/


	m_donnees[adresse] = 0x6F; // MOV B, 15
	adresse++;
	m_donnees[adresse] = 0x85; // NOT A
	adresse++;
	m_donnees[adresse] = 0x08; // MOV B, A
	adresse++;
	m_donnees[adresse] = 0x81; // INC A
	adresse++;
	m_donnees[adresse] = 0x08; // MOV B, A
	adresse++;
	m_donnees[adresse] = 0x4F; // MOV A, 15
	adresse++;
	m_donnees[adresse] = 0x10; // MOV C, A
	adresse++;
	m_donnees[adresse] = 0x80; // ADD A
	adresse++;
	m_donnees[adresse] = 0xE6; // GOTO 0 // 0xAE = HALT
	adresse++;
	m_donnees[adresse] = 0x00; // GOTO 0
	adresse++;
	m_donnees[adresse] = 0x00; // GOTO 0
	adresse++;

}

unsigned short int Memory::getWord(unsigned short int adresse) {
	return m_donnees[adresse];
}

void Memory::setWord(unsigned short int adresse, unsigned short int data) {
	m_donnees[adresse] = (data & 0x00FF);
}

void Memory::read() { // On lit la donnée de la mémoire pour la mettre sur le bus
	m_dataBus->setWord(Memory::getWord(m_adresseBus->getWord()));
}

void Memory::write() { // On lit la donnée du bus pour la mettre dans la mémoire
	Memory::setWord(m_adresseBus->getWord(), m_dataBus->getWord());
}
