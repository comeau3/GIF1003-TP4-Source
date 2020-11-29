#ifndef AFFICHEURDELISTEELECTORALE_H
#define AFFICHEURDELISTEELECTORALE_H

#include <QtGui>
#include "desinscrireelecteur.h"
#include "Circonscription.h"


class AfficheurDeListeElectorale : public QWidget
{
    Q_OBJECT

public:
	static QString convertirTexte(std::string texte);

    AfficheurDeListeElectorale(elections::Circonscription*, QWidget *parent = 0);
    ~AfficheurDeListeElectorale();
    QPushButton* reqBoutonDesinscrire();
    QPushButton* reqBoutonCreerNouvelElecteur();
    QPushButton* reqBoutonCreerNouveauCandidat();

public slots:
    void rafraichir(const elections::Circonscription*);

private:

    QPlainTextEdit* liste;
    QPushButton* boutonNouvelElecteur;
    QPushButton* boutonNouveauCandidat;
    QPushButton* boutonDesinscrire;

    QHBoxLayout* zoneBouton;
    QVBoxLayout* zoneGlobale;


    //QLineEdit*   ligneRecherche;
    //QPushButton* boutonRecherche;

    //Ui::afficheurDeListeElectoraleClass ui;
};

#endif // AFFICHEURDELISTEELECTORALE_H
