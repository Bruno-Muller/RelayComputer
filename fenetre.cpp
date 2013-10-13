#include "fenetre.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent){
    setupUi(this);

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(on_pushButton_Step_clicked()));
    timer->setInterval(200);

    // On initialise sur l'ordinateur sur le premier cycle
    modeFonctionnement = STEP;
    on_pushButton_Step_clicked();

}

void Widget::on_spinBox_valueChanged() {
    float periode(0);
    periode = 1000 / spinBox->value();
    label_timer->setText("Periode : " + QString::number(periode) + "ms");
    timer->setInterval((int) periode);

}

void Widget::on_pushButton_Inst_clicked() {
    if (modeFonctionnement == INST) {
	timer->stop();
	modeFonctionnement = STEP;
	label_modeFonctionnement->setText("Mode de fonctionnement : STEP");
    }
    else {
	modeFonctionnement = INST;
	label_modeFonctionnement->setText("Mode de fonctionnement : INST");
	pushButton_Run->setChecked(false);
	timer->start();
    }
}

void Widget::on_pushButton_Run_clicked() {
    if (modeFonctionnement == RUN) {
	timer->stop();
	modeFonctionnement = STEP;
	label_modeFonctionnement->setText("Mode de fonctionnement : STEP");
    }
    else {
	modeFonctionnement = RUN;
	label_modeFonctionnement->setText("Mode de fonctionnement : RUN");
	pushButton_Inst->setChecked(false);
	timer->start();
    }
}

void Widget::on_pushButton_Step_clicked() {

    HALT = false;

    computeEEPROM();
    affiche();
    if (horloge.getClock() == 1) desassemble(Inst.getWord());

    busAdresse.pulldown();
    busDonnee.pulldown();


    if ((modeFonctionnement == INST) && (horloge.getReset())) {
	HALT = true;
    }
    if (HALT == true) {
	timer->stop();
	pushButton_Inst->setChecked(false);
	pushButton_Run->setChecked(false);
	modeFonctionnement = STEP;
	label_modeFonctionnement->setText("Mode de fonctionnement : STEP");
    }

    horloge.incClock();
    nbrCycles++;
}

void Widget::affiche() {

    this->label_nbrCycles->setText("nbrCycles:" + QString::number(nbrCycles));
    this->label_Inst->setText("Inst:0x" + QString::number(Inst.getWord(),16));    
    this->label_Clock->setText("Clock:" + QString::number(horloge.getClock() + 1));
    this->label_nbrCycles->setText("nbrCycles:" + QString::number(nbrCycles + 1));

    this->label_inc16->setText("inc16:0x" + QString::number(incr16.getWord(),16));
    this->label_Inc->setText("Inc:0x" + QString::number(Inc.getWord(),16));
    this->label_PC->setText("PC:" + QString::number(PC.getWord()));

    unsigned short int adresse(Inst.getWord()+ (horloge.getClock()<<8) + (alu.getZ()<<13) + (alu.getCy()<<14) + (alu.getS()<<15));
    this->label_AdresseEE->setText("adresseEE:0x" + QString::number(adresse, 16));
    this->label_EE1->setText("EE1:0x" + QString::number(eeprom1.getWord(adresse), 16));    
    this->label_EE2->setText("EE2:0x" + QString::number(eeprom2.getWord(adresse), 16));    
    this->label_EE3->setText("EE3:0x" + QString::number(eeprom3.getWord(adresse), 16));    
    this->label_EE4->setText("EE4:0x" + QString::number(eeprom4.getWord(adresse), 16));
    this->label_EE5->setText("EE5:0x" + QString::number(eeprom5.getWord(adresse), 16));

    this->label_codeALU->setText("codeALU:" + QString::number(alu.getCode()));
    this->label_ALU->setText("ALU:" + QString::number(alu.getResult()));
    this->label_Z->setText("Z:" + QString::number(alu.getZ()));
    this->label_Cy->setText("Cy:" + QString::number(alu.getCy()));
    this->label_S->setText("S:" + QString::number(alu.getS()));

    this->label_busDonnee->setText("busDonnee:0x" + QString::number(busDonnee.getWord(), 16));
    this->label_busAdresse->setText("busAdresse:0x" + QString::number(busAdresse.getWord(), 16));

    this->label_A->setText("A:0x" + QString::number(A.getWord(), 16));
    this->label_B->setText("B:0x" + QString::number(B.getWord(), 16));
    this->label_C->setText("C:0x" + QString::number(C.getWord(), 16));
    this->label_D->setText("D:0x" + QString::number(D.getWord(), 16));

    this->label_M1->setText("M1:0x" + QString::number(M1.getWord(), 16));
    this->label_M2->setText("M2:0x" + QString::number(M2.getWord(), 16));
    this->label_M->setText("M:0x" + QString::number(M.getWord(), 16));

    this->label_X->setText("X:0x" + QString::number(X.getWord(), 16));
    this->label_Y->setText("Y:0x" + QString::number(Y.getWord(), 16));
    this->label_XY->setText("XY:0x" + QString::number(XY.getWord(), 16));

    this->label_J1->setText("J1:0x" + QString::number(J1.getWord(), 16));
    this->label_J2->setText("J2:0x" + QString::number(J2.getWord(), 16));
    this->label_J->setText("J:0x" + QString::number(J.getWord(), 16));

    DEL(del_Inst, Inst.getWord(), 8);

    DEL(del_Clock, horloge.getClock(), 5);

    DEL(del_adresseEE, adresse, 16);
    DEL(del_EE1, eeprom1.getWord(adresse), 8);
    DEL(del_EE2, eeprom2.getWord(adresse), 8);
    DEL(del_EE3, eeprom3.getWord(adresse), 8);
    DEL(del_EE4, eeprom4.getWord(adresse), 8);
    DEL(del_EE5, eeprom5.getWord(adresse), 8);

    DEL(del_codeALU, alu.getCode(), 3);
    DEL(del_ALU, alu.getResult(), 8);
    DEL(del_Z, alu.getZ(), 1);
    DEL(del_Cy, alu.getCy(), 1);
    DEL(del_S, alu.getS(), 1);

    DEL(del_inc16, incr16.getWord(), 16);
    DEL(del_Inc, Inc.getWord(), 16);
    DEL(del_PC, PC.getWord(), 16);

    DEL(del_busAdresse, busAdresse.getWord(), 16);
    DEL(del_busDonnee, busDonnee.getWord(), 8);

    DEL(del_A, A.getWord(), 8);
    DEL(del_B, B.getWord(), 8);
    DEL(del_C, C.getWord(), 8);
    DEL(del_D, D.getWord(), 8);

    DEL(del_M1, M1.getWord(), 8);
    DEL(del_M2, M2.getWord(), 8);

    DEL(del_X, X.getWord(), 8);
    DEL(del_Y, Y.getWord(), 8);

    DEL(del_J1, J1.getWord(), 8);
    DEL(del_J2, J2.getWord(), 8);


}

void Widget::DEL(QLabel *label, unsigned short int word, unsigned short int nbrBits) {
    QPixmap ledOn(3+22*nbrBits+3,26);
    unsigned short int masque(1);
    masque<<=(nbrBits-1);


    QPainter p(&ledOn);

    p.setPen(QPen(Qt::black, 1)) ;
    p.setBrush(QBrush(Qt::gray)) ;
    p.drawRect(0,0,ledOn.width()-1,ledOn.height()-1) ;

    for (unsigned short int i(0); i< nbrBits; i++) {
	p.setPen(QPen(Qt::black, 1)) ;
	if (word & masque) p.setBrush(QBrush(Qt::red));
	else p.setBrush(QBrush(Qt::NoBrush));
	masque>>=1;

	p.drawEllipse(3+22*i,3,20,20);
    }

    label->setPixmap(ledOn);

}

void Widget::desassemble(unsigned short int instruction) {
    QString code;
	// MOV
	if ((instruction & 0xC0) == 0) {
		code = "MOV ";
		unsigned short int source(0), destination(0);
		destination = (instruction & 0x38)>>3;
		switch (destination) {
			case 0:
				code +="A";
				break;
			case 1:
				code += "B";
				break;
			case 2:
				code += "C";
				break;
			case 3:
				code += "D";
				break;
			case 4:
				code += "M1";
				break;
			case 5:
				code += "M2";
				break;
			case 6:
				code += "X";
				break;
			case 7:
				code += "Y";
				break;
			default:
				break;
		}
		code += ", ";
		source = instruction & 0x07;
		switch (source) {
			case 0:
				code += "A";
				break;
			case 1:
				code += "B";
				break;
			case 2:
				code += "C";
				break;
			case 3:
				code += "D";
				break;
			case 4:
				code += "M1";
				break;
			case 5:
				code += "M2";
				break;
			case 6:
				code += "X";
				break;
			case 7:
				code += "Y";
				break;
			default:
				break;
		}
	}
	// ALU
	else if ((instruction & 0xF0) == 0x80) {
		unsigned short int fonction(0);
		fonction = instruction & 0x07;
		switch (fonction) {
			case 0:
				code = "ADD";
				break;
			case 1:
				code = "INC";
				break;
			case 2:
				code = "AND";
				break;
			case 3:
				code = "OR";
				break;
			case 4:
				code = "XOR";
				break;
			case 5:
				code = "NOT";
				break;
			case 6:
				code = "SHL";
				break;
			case 7:
				code = "ALU <not used>";
				break;
			default:
				break;
		}
		code += " ";
		if (instruction & 0x08) code += "D";
		else code += "A";

	}
	//SETAB
	else if ((instruction & 0xC0) == 0x40) {
		code = "MOV ";
		if (instruction & 0x20) code += "B";
		else code += "A";
		code += ", ";
		short int valeur;
		valeur = Inst.getWord() & 0x1F;
		if (valeur & 0x10) valeur |= 0xFFF0;
		code += QString::number(valeur);
	}
	// INCXY
	else if (instruction == 0xB0) code = "INC XY";
	// LOAD
	else if ((instruction & 0xFC) == 0x90) {
		unsigned short int destination(instruction & 0x03);
		code = "MOV ";
		switch (destination) {
			case 0:
				code += "A";
				break;
			case 1:
				code += "B";
				break;
			case 2:
				code += "C";
				break;
			case 3:
				code += "D";
				break;
			default:
				break;
		}
		code += ", [M]";
	}
	// STORE
	else if ((instruction & 0xFC) == 0x98) {
		unsigned short int destination(instruction & 0x03);
		code = "MOV [M], ";
		switch (destination) {
			case 0:
				code += "A";
				break;
			case 1:
				code += "B";
				break;
			case 2:
				code += "C";
				break;
			case 3:
				code += "D";
				break;
			default:
				break;
		}
	}
	// MOV16
	// - HALT
	else if (instruction == 0xAE) code = "HALT";
	// - RET / BRANCH INDIRECT
	else if (instruction == 0xAA) code = "RET";
	// - MOV
	else if ((instruction & 0xF1) == 0xA0) {
		unsigned short int destination;
		destination = (instruction & 0x08)>>2;
		code = "MOV ";
		switch (destination) {
			case 0:
				code += "XY";
				break;
			case 1:
				code += "PC";
				break;
			default:
				break;
		}
		code += ", ";
		unsigned short int source;
		source = (instruction & 0x06)>>1;
		switch (source) {
			case 0:
				code += "M";
				break;
			case 1:
				code += "XY";
				break;
			case 2:
				code += "J";
				break;
			case 3:
				code += "break";
				break;

			default:
				break;
		}
	}
	// GOTO
	// - MOV
	else if (instruction == 0xC0) {
		code = "MOV M, ";
		unsigned short int valeur;
		valeur = memory.getWord(PC.getWord()+1);
		valeur <<=8;
		valeur += memory.getWord(PC.getWord()+2);
		code += QString::number(valeur);
	}
	// - GOTO/JUMP
	else if (instruction == 0xE6) {
		code = "JUMP ";
		unsigned short int valeur;
		valeur = memory.getWord(PC.getWord()+1);
		valeur <<=8;
		valeur += memory.getWord(PC.getWord()+2);
		code += QString::number(valeur);
	}
	// - CALL
	else if (instruction == 0xE7) {
		code = "CALL ";
		unsigned short int valeur;
		valeur = memory.getWord(PC.getWord()+1);
		valeur <<=8;
		valeur += memory.getWord(PC.getWord()+2);
		code += QString::number(valeur);
	}
	// - BNEG
	else if (instruction == 0xF0) {
		code = "BNEG ";
		unsigned short int valeur;
		valeur = memory.getWord(PC.getWord()+1);
		valeur <<=8;
		valeur += memory.getWord(PC.getWord()+2);
		code += QString::number(valeur);
	}
	// - BNC
	else if (instruction == 0xE8) {
		code = "BNC ";
		unsigned short int valeur;
		valeur = memory.getWord(PC.getWord()+1);
		valeur <<=8;
		valeur += memory.getWord(PC.getWord()+2);
		code += QString::number(valeur);
	}
	// - BZ/BE
	else if (instruction == 0xE4) {
		code = "BZ ";
		unsigned short int valeur;
		valeur = memory.getWord(PC.getWord()+1);
		valeur <<=8;
		valeur += memory.getWord(PC.getWord()+2);
		code += QString::number(valeur);
	}
	// - BNZ/BZE
	else if (instruction == 0xE2) {
		code = "BNZ ";
		unsigned short int valeur;
		valeur = memory.getWord(PC.getWord()+1);
		valeur <<=8;
		valeur += memory.getWord(PC.getWord()+2);
		code += QString::number(valeur);
	}
	// Instruction inconnue
	else {
		code = "Instruction inconnue.";
	}
	lineEdit_ASM->setText(code);
}

