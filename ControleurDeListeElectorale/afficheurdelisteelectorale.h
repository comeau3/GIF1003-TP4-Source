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
    void rafraichir(const elections::Circonscription* circonscription);

private:

    QPlainTextEdit* liste;
    QPushButton* boutonNouvelElecteur;
    QPushButton* boutonNouveauCandidat;
    QPushButton* boutonDesinscrire;

    QHBoxLayout* zoneBouton;
    QVBoxLayout* zoneGlobale;

};

#endif // AFFICHEURDELISTEELECTORALE_H
