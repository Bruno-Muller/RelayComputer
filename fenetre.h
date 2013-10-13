#ifndef FENETRE_H
#define FENETRE_H

#include "ui_fenetre.h"

#include "QString"
#include "QTimer"
#include "QPixmap"
#include "QPainter"

#include "Ordinateur.h"

enum ModeFonctionnement {STEP, INST, RUN};

class Widget : public QWidget, Ordinateur, private Ui::Widget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

private slots:
    void on_pushButton_Run_clicked();
    void on_pushButton_Inst_clicked();
    void on_pushButton_Step_clicked();
    void on_spinBox_valueChanged();

private:
    QTimer *timer;
    ModeFonctionnement modeFonctionnement;

    void affiche();
    void DEL(QLabel *label, unsigned short int word, unsigned short int nbrBits);
    void desassemble(unsigned short int instruction);

};

#endif // FENETRE_H
