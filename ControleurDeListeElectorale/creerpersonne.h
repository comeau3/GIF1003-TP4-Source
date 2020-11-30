#ifndef CREERPERSONNE_H
#define CREERPERSONNE_H

#include <QtGui>
#include "Personne.h"

class CreerPersonne : public QDialog
{


    Q_OBJECT

public:
	enum Mode {Pret, EnCours, Initial};

    CreerPersonne(QWidget *parent = 0);
    virtual ~CreerPersonne();

    virtual elections::Personne* reqPersonne() = 0; // Cette méthode permet à l'appelant de récupérer l'objet créé

public slots:
    void clicBoutonSoumettre();
    void clicBoutonAnnuler();
    void clicBoutonReInitialiser();
    void formulaireModifie();

public:

    Mode modeCourant;

    std::string nomAccepte;
    std::string prenomAccepte;
    std::string nasAccepte;

    int jourAccepte;
    int moisAccepte;
    int anneeAcceptee;

    int numCivicAccepte;
    std::string nomRueAccepte;
    std::string villeAcceptee;
    std::string codePostalAccepte;
    std::string provinceAcceptee;

    /* Widgets du formulaire */

    QPushButton* boutonSoumettre;
    QPushButton* boutonAnnuler;
    QPushButton* boutonReInitialiser;

    QLabel* nomBanniere;
    QLabel* prenomBanniere;
    QLabel* nasBanniere;
    QLabel* ddnBanniere;
    QLabel* numeroCiviqueBanniere;
    QLabel* nomRueBanniere;
    QLabel* villeBanniere;
    QLabel* codePostalBanniere;
    QLabel* provinceBanniere;

    QLineEdit* nomSaisie;
    QLineEdit* prenomSaisie;
    QLineEdit* nasSaisie;
    QDateEdit* ddnSaisie;
    QLineEdit* numeroCiviqueSaisie;
    QLineEdit* nomRueSaisie;
    QLineEdit* villeSaisie;
    QLineEdit* codePostalSaisie;
    QComboBox* provinceSaisie;

    QLabel* nomValidation;
    QLabel* prenomValidation;
    QLabel* nasValidation;
    QLabel* ddnValidation;
    QLabel* numeroCiviqueValidation;
    QLabel* nomRueValidation;
    QLabel* villeValidation;
    QLabel* codePostalValidation;
    QLabel* provinceValidation;

    QHBoxLayout* zoneBoutons;
    QVBoxLayout* zoneSaisies;
    QVBoxLayout* zoneBannieres;
    QVBoxLayout* zoneValidations;

    QHBoxLayout* zoneSuperieure;
    QGridLayout* zoneGlobale;

    /* Méthode de changement de mode */

    void actualiserBoutons();
    void actualiserSaisies();
    void actualiserMessageDeValidation(QLabel*, bool);
    void actualiserValidations();
    void actualiserValeursAcceptees();
    void actualiser(Mode mode);

    /* Validation des saisies */

    bool lesSaisiesSontToutesValides();
    bool laSaisieNomEstValide();
    bool laSaisiePrenomEstValide();
    bool laSaisieNasEstValide();
    bool laSaisieDateEstValide();
    bool laSaisieAdresseEstValide();

    /* État initial */

    void initialiserLesValeursAcceptees();
    void initialiserBoutons();
    void initialiserBannieres();
    void initialiserZonesDeSaisie();
    void initialiserZonesDeValidation();
    void miseEnPageDuFormulaire();

};


#endif // CREERPERSONNE_H
