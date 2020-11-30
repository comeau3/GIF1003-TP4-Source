#ifndef CONTROLEURDELISTEELECTORALE_H
#define CONTROLEURDELISTEELECTORALE_H

#include <QtGui>
#include "ui_controleurdelisteelectorale.h"

#include "afficheurdelisteelectorale.h"
#include "desinscrireelecteur.h"
#include "creerelecteur.h"
#include "creercandidat.h"
#include "Circonscription.h"
#include "Electeur.h"
#include "Candidat.h"

class ControleurDeListeElectorale : public QMainWindow
{
    Q_OBJECT

public:
    ControleurDeListeElectorale(QWidget *parent = 0);
    ~ControleurDeListeElectorale();

private slots:

    void nouveau();
    void sauvegarder();
    void recuperer();
    void quitter();

    void creerNouvelElecteur();
    void creerNouveauCandidat();
    void desinscrire();

private:
    //Ui::ControleurDeListeElectoraleClass ui;

    elections::Circonscription* circonscription = nullptr;

    QMenu* menuFichier;
    QMenu* menuActions;

    QAction* actionNouveau;
    QAction* actionSauvegarder;
    QAction* actionRecuperer;
    QAction* actionQuitter;

    QAction* actionCreerNouvelElecteur;
    QAction* actionCreerNouveauCandidat;
    QAction* actionDesinscrire;

    AfficheurDeListeElectorale* afficheur;
    DesinscrireElecteur* desinscripteur;
    CreerElecteur* inscripteurElecteur;
    CreerCandidat* inscripteurCandidat;



    void initialiserBarreDeMenu();
    void initialiserMenuFichier();
    void initialiserMenuActions();
    void initialiserAfficheur();
    void initialiserCirconscription();
    void initialiserFenetrePrincipale();


};

#endif // CONTROLEURDELISTEELECTORALE_H
