#include "afficheurdelisteelectorale.h"

const QString TXT_BOUTON_ELECTEUR = QString::fromUtf8("Nouvel électeur");
const QString TXT_BOUTON_CANDIDAT = QString::fromUtf8("Nouveau candidat");
const QString TXT_BOUTON_DESINSCRIRE = QString::fromUtf8("Désinscription");

QString AfficheurDeListeElectorale::convertirTexte(std::string texte)
{
	std::vector<char> texteBrut(texte.begin(), texte.end());
	texteBrut.push_back('\0');
	return QString::fromUtf8(&texteBrut[0]);
}

AfficheurDeListeElectorale::AfficheurDeListeElectorale(elections::Circonscription* circ, QWidget *parent)
    : QWidget(parent)
{

	elections::Circonscription* circonscription = circ;

	liste = new QPlainTextEdit(convertirTexte(circonscription->reqCirconscriptionFormate()));
	liste->setReadOnly(true);
	boutonNouvelElecteur = new QPushButton(TXT_BOUTON_ELECTEUR);
	boutonNouveauCandidat = new QPushButton(TXT_BOUTON_CANDIDAT);
	boutonDesinscrire = new QPushButton(TXT_BOUTON_DESINSCRIRE);

	zoneBouton = new QHBoxLayout;
	zoneBouton->addWidget(boutonNouvelElecteur);
	zoneBouton->addWidget(boutonNouveauCandidat);
	zoneBouton->addWidget(boutonDesinscrire);

	zoneGlobale = new QVBoxLayout;
	zoneGlobale->addWidget(liste);
	zoneGlobale->addLayout(zoneBouton);

	setLayout(zoneGlobale);
}

QPushButton* AfficheurDeListeElectorale::reqBoutonDesinscrire()
{
	return boutonDesinscrire;
}

QPushButton* AfficheurDeListeElectorale::reqBoutonCreerNouvelElecteur()
{
	return boutonNouvelElecteur;
}

QPushButton* AfficheurDeListeElectorale::reqBoutonCreerNouveauCandidat()
{
	return boutonNouveauCandidat;
}

void AfficheurDeListeElectorale::rafraichir(const elections::Circonscription* circonscription)
{
    liste->clear();
    liste->setPlainText(convertirTexte(circonscription->reqCirconscriptionFormate()));
}

AfficheurDeListeElectorale::~AfficheurDeListeElectorale()
{

}
