#ifndef ORDINATEUR_H
#define ORDINATEUR_H

#include "Bus.h"
#include "InterfaceRegistre8_16.h"
#include "Registre.h"
#include "ALU.h"
#include "Incr16bit.h"
#include "Memory.h"
#include "EEPROM.h"
#include "Horloge.h"

class Ordinateur
{

public:
    Ordinateur();

protected:

    unsigned short int nbrCycles;

    // On crée les bus
    Bus busDonnee;  // Bus de 8bits
    Bus busAdresse; // Bus de 16bits
    Bus busIncr;    // pseudo-bus de 16bits : relie l'incrémenteur 16bits à Inc

    // On crée les registres
    Registre A, B, C, D; // A, B, C, D de 8bits
    Registre M1, M2; // M1, M2 de 8bits
    Registre X, Y; // X, Y de 8bits
    Registre J1, J2; // J1, J2 de 8bits
    Registre Inst; // Inst de 8bits
    Registre PC; // PC de 16bits
    Registre Inc; // Inc de 16bits

    // On assemble certains registres de 8 bits pour faire un registre de 16 bits
    InterfaceRegistre8_16 M;
    InterfaceRegistre8_16 XY;
    InterfaceRegistre8_16 J;

    // On crée l'ALU
    ALU alu;

    // On crée l'incrémenteur 16 bit
    Incr16bit incr16;

    // On crée la mémoire
    Memory memory;

    // On crée les EEPROM qui contiennent les microcodes
    EEPROM eeprom1, eeprom2, eeprom3, eeprom4, eeprom5;

    // On crée l'horloge
    Horloge horloge;

    // Signal de mise en veille
    bool HALT;

    void computeCycle();
    void computeEEPROM();

private:


};

#endif // ORDINATEUR_H
