#ifndef DESINSCRIREELECTEUR_H
#define DESINSCRIREELECTEUR_H

#include <QtGui>
//#include "ui_desinscrireelecteur.h"

class DesinscrireElecteur : public QDialog
{
    Q_OBJECT

public:
    DesinscrireElecteur(QWidget *parent = 0);
    ~DesinscrireElecteur();
    QString reqNasADesinscrire();

private slots:
    void clicBoutonAnnuler();
    void clicBoutonDesinscrire();
    void saisieModifiee();

private:


    enum Mode {INITIAL, EDITION, PRET};

    Mode mode;
    QString nasSaisi;

    QLabel* nasBanniere;
    QLineEdit* nasRecherche;
    QPushButton* boutonAnnuler;
    QPushButton* boutonDesinscrire;

    QHBoxLayout* zoneBoutons;
    QHBoxLayout* zoneSaisie;
    QVBoxLayout* zoneGlobale;

    void initialiserLesComposantes();
    void mettreEnPageLeDialogue();
    void connecterLesSignaux();
    void rafraichir(Mode);

    //Ui::DesinscrireElecteurClass ui;
};

#endif // DESINSCRIREELECTEUR_H
