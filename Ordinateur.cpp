#include "Ordinateur.h"

Ordinateur::Ordinateur() :

	nbrCycles(0),

	// On crée les bus
	busDonnee(8), // Bus de 8bits
	busAdresse(16), // Bus de 16bits
	busIncr(16), // pseudo-bus de 16bits : relie l'incrémenteur 16bits à Inc

	// On crée les registres
	A(8, &busDonnee, &busDonnee), B(8, &busDonnee, &busDonnee), C(8, &busDonnee, &busDonnee), D(8, &busDonnee, &busDonnee), // A, B, C, D de 8bits
	M1(8, &busDonnee, &busDonnee), M2(8, &busDonnee, &busDonnee), // M1, M2 de 8bits
	X(8, &busDonnee, &busDonnee), Y(8, &busDonnee, &busDonnee), // X, Y de 8bits
	J1(8, &busDonnee, NULL), J2(8, &busDonnee, NULL), // J1, J2 de 8bits
	Inst(8, &busDonnee, NULL), // Inst de 8bits
	PC(16, &busAdresse, &busAdresse), // PC de 16bits
	Inc(16, &busIncr, &busAdresse), // Inc de 16bits

	// On assemble certains registres de 8 bits pour faire un registre de 16 bits
	M(&M1, &M2, NULL, &busAdresse),
	XY(&X, &Y, &busAdresse, &busAdresse),
	J(&J1, &J2, NULL, &busAdresse),

	// On crée l'ALU
	alu(&B, &C, &busDonnee),

	// On crée l'incrémenteur 16 bit
	incr16(&busAdresse, &busIncr),

	// On crée la mémoire
	memory(&busAdresse, &busDonnee),

	// On crée les EEPROM qui contiennent les microcodes
	eeprom1(std::string("EEPROM1.dat")), eeprom2(std::string("EEPROM2.dat")), eeprom3(std::string("EEPROM3.dat")), eeprom4(std::string("EEPROM4.dat")), eeprom5(std::string("EEPROM5.dat")),

	HALT(false) {
    X.setWord(64);
}

void Ordinateur::computeCycle() {
    computeEEPROM();

}

void Ordinateur::computeEEPROM() {
    unsigned short int adresse(Inst.getWord() + (horloge.getClock()<<8) + (alu.getZ()<<13) + (alu.getCy()<<14) + (alu.getS()<<15));
    unsigned short int data(0);

    // boucle nécessaire genre si le bus est lu avant qu'une valeur soit séléctionnée (on va dire que c'est à cause du temps de propagation des signaux ^^)
    for (unsigned short int boucle(0); boucle<2; boucle++) {

	// EEPROM 1
	/*
		 EEPROM 1 :
		 nBit		Adresse		donnée
		 0		Iinst0		A.load()
		 1		Iinst1		A.select()
		 2		Iinst2		B.load()
		 3		Iinst3		B.select()
		 4		Iinst4		C.load()
		 5		Iinst5		C.select()
		 6		Iinst6		D.load()
		 7		Iinst7		D.select()
		 8		Clock0		---
		 9		Clock1		---
		 10		Clock2		---
		 11		Clock3		---
		 12		Clock4		---
		 13		Z			---
		 14		Cy			---
		 15		S			---
		 */

	data = eeprom1.getWord(adresse);

	if (data & 0x01) {
	    A.load();
	}
	if (data & 0x02) {
	    A.select();
	}
	if (data & 0x04) {
	    B.load();
	}
	if (data & 0x08) {
	    B.select();
	}
	if (data & 0x10) {
	    C.load();
	}
	if (data & 0x20) {
	    C.select();
	}
	if (data & 0x40) {
	    D.load();
	}
	if (data & 0x80) {
	    D.select();
	}

	// EEPROM 2
	/*
		 EEPROM 2 :
		 nBit		Adresse		donnée
		 0		Iinst0		M1.load()
		 1		Iinst1		M1.select()
		 2		Iinst2		M2.load()
		 3		Iinst3		M2.select()
		 4		Iinst4		M.select()
		 5		Iinst5		X.load()
		 6		Iinst6		X.select()
		 7		Iinst7		Y.load()
		 8		Clock0		---
		 9		Clock1		---
		 10		Clock2		---
		 11		Clock3		---
		 12		Clock4		---
		 13		Z			---
		 14		Cy			---
		 15		S			---
		 */

	data = eeprom2.getWord(adresse);

	if (data & 0x01) {
	    M1.load();
	}
	if (data & 0x02) {
	    M1.select();
	}
	if (data & 0x04) {
	    M2.load();
	}
	if (data & 0x08) {
	    M2.select();
	}
	if (data & 0x10) {
	    M.select();
	}
	if (data & 0x20) {
	    X.load();
	}
	if (data & 0x40) {
	    X.select();
	}
	if (data & 0x80) {
	    Y.load();
	}

	// EEPROM 3
	/*
		 EEPROM 3 :
		 nBit		Adresse		donnée
		 0		Iinst0		Y.select()
		 1		Iinst1		XY.load()
		 2		Iinst2		XY.select()
		 3		Iinst3		J1.load()
		 4		Iinst4		J2.load()
		 5		Iinst5		J.select()
		 6		Iinst6		Inst.load()
		 7		Iinst7		PC.load()
		 8		Clock0		---
		 9		Clock1		---
		 10		Clock2		---
		 11		Clock3		---
		 12		Clock4		---
		 13		Z			---
		 14		Cy			---
		 15		S			---
		 */

	data = eeprom3.getWord(adresse);

	if (data & 0x01) {
	    Y.select();
	}
	if (data & 0x02) {
	    XY.load();
	}
	if (data & 0x04) {
	    XY.select();
	}
	if (data & 0x08) {
	    J1.load();
	}
	if (data & 0x10) {
	    J2.load();
	}
	if (data & 0x20) {
	    J.select();
	}
	if (data & 0x40) {
	    Inst.load();
	}
	if (data & 0x80) {
	    PC.load();
	}

	// EEPROM 4
	/*
		 EEPROM 4 :
		 nBit		Adresse		donnée
		 0		Iinst0		PC.select()
		 1		Iinst1		Inc.load()
		 2		Iinst2		Inc.select()
		 3		Iinst3		memory.read()
		 4		Iinst4		memory.write()
		 5		Iinst5		alu.loadFlags()
		 6		Iinst6		alu.setBitCode(0, #)
		 7		Iinst7		alu.setBitCode(1, #)
		 8		Clock0		---
		 9		Clock1		---
		 10		Clock2		---
		 11		Clock3		---
		 12		Clock4		---
		 13		Z			---
		 14		Cy			---
		 15		S			---
		 */

	data = eeprom4.getWord(adresse);

	if (data & 0x01) {
	    PC.select();
	}
	if (data & 0x02) {
	    Inc.load();
	}
	if (data & 0x04) {
	    Inc.select();
	}
	if (data & 0x08) {
	    memory.read();
	}
	if (data & 0x10) {
	    memory.write();
	}
	if (data & 0x20) {
	    alu.loadFlags();
	}
	if (data & 0x40) {
	    alu.setBitCode(0, true);
	}
	else {
	    alu.setBitCode(0, false);
	}
	if (data & 0x80) {
	    alu.setBitCode(1, true);
	}
	else {
	    alu.setBitCode(1, false);
	}

	// EEPROM 5
	/*
		 EEPROM 5 :
		 nBit		Adresse		donnée
		 0		Iinst0		alu.setBitCode(2, #)
		 1		Iinst1		HALT // arreter l'horloge
		 2		Iinst2		clock.resetClock() // redémarrer un nouveau cycle pour la prochaine instruction
		 3		Iinst3		LOAD_IMMEDIATE_TO_BUS
		 4		Iinst4		false
		 5		Iinst5		false
		 6		Iinst6		false
		 7		Iinst7		false
		 8		Clock0		---
		 9		Clock1		---
		 10		Clock2		---
		 11		Clock3		---
		 12		Clock4		---
		 13		Z			---
		 14		Cy			---
		 15		S			---
		 */

	data = eeprom5.getWord(adresse);

	if (data & 0x01) {
	    alu.setBitCode(2, true);
	}
	else {
	    alu.setBitCode(2, false);
	}
	if (data & 0x02) {
	    HALT = true;
	}
	if (data & 0x04) {
	    horloge.resetClock();
	}
	if (data & 0x08) {
	    unsigned short int valeur;
	    valeur = Inst.getWord() & 0x1F;
	    if (valeur & 0x10) valeur |= 0xF0;
	    busDonnee.setWord(valeur);
	}
	incr16.compute(); // techniquement il faudrait executer ça à chaque SELECT d'un registre de 16bits sur le BUS, mais une fois par cycle c'est ok
    }
}
