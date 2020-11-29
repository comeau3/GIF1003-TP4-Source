#ifndef CREERCANDIDAT_H
#define CREERCANDIDAT_H

#include <QtGui>
#include "Candidat.h"

//#include "ui_creerelecteur.h"

class CreerCandidat : public QDialog
{
	enum Mode {Pret, EnCours, Initial};

    Q_OBJECT

public:
    CreerCandidat(QWidget *parent = 0);
    ~CreerCandidat();

    elections::Candidat* reqCandidat(); // Cette méthode permet à l'appelant de récupérer l'objet créé

private slots:
    void clicBoutonSoumettre();
    void clicBoutonAnnuler();
    void clicBoutonReInitialiser();
    void formulaireModifie();

private:

    // Source de données

    elections::Candidat* candidat;


    Mode modeCourant;

    /* Widgets du formulaire */

    QPushButton* boutonSoumettre;
    QPushButton* boutonAnnuler;
    QPushButton* boutonReInitialiser;

    QLabel* partiBanniere;
    QLabel* nomBanniere;
    QLabel* prenomBanniere;
    QLabel* nasBanniere;
    QLabel* ddnBanniere;
    QLabel* numeroCiviqueBanniere;
    QLabel* nomRueBanniere;
    QLabel* villeBanniere;
    QLabel* codePostalBanniere;
    QLabel* provinceBanniere;

    QComboBox* partiSaisie;
    QLineEdit* nomSaisie;
    QLineEdit* prenomSaisie;
    QLineEdit* nasSaisie;
    QDateEdit* ddnSaisie;
    QLineEdit* numeroCiviqueSaisie;
    QLineEdit* nomRueSaisie;
    QLineEdit* villeSaisie;
    QLineEdit* codePostalSaisie;
    QComboBox* provinceSaisie;

    QHBoxLayout* zoneBoutons;
    QVBoxLayout* zoneSaisies;
    QVBoxLayout* zoneBannieres;

    QHBoxLayout* zoneSuperieure;
    QGridLayout* zoneGlobale;

    /* Méthode de changement de mode */

    void actualiserBoutons();
    void actualiserSaisies();
    void actualiser(Mode mode);

    /* Validation des saisies */

    bool lesSaisiesSontToutesValides();
    bool laSaisieNomEstValide();
    bool laSaisiePrenomEstValide();
    bool laSaisieNasEstValide();
    bool laSaisieDateEstValide();
    bool laSaisieAdresseEstValide();

    /* État initial */

    void initialiserBoutons();
    void initialiserBannieres();
    void initialiserZonesDeSaisie();
    void miseEnPageDuFormulaire();

};



#endif // CREERCANDIDAT_H
