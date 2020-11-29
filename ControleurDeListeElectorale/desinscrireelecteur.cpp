#include "desinscrireelecteur.h"
#include "validationFormat.h"
#include <iostream>

const QString TXT_NAS_BANNIERE = QString::fromUtf8("Numéro d'assurance sociale: ");
const QString TXT_NAS_PHOLDER = QString::fromUtf8("888 888 888");
const QString TXT_ANNULER_BOUTON = QString::fromUtf8("Annuler");
const QString TXT_DESINSCRIRE_BOUTON = QString::fromUtf8("Désinscrire");

DesinscrireElecteur::DesinscrireElecteur(QWidget *parent)
    : QDialog(parent)
{
	initialiserLesComposantes();
	mettreEnPageLeDialogue();
	connecterLesSignaux();

	rafraichir(INITIAL);
	nasSaisi = "";

	//ui.setupUi(this);
}

void DesinscrireElecteur::initialiserLesComposantes()
{
	nasBanniere = new QLabel(TXT_NAS_BANNIERE);
	nasRecherche = new QLineEdit;
	nasRecherche->setPlaceholderText(TXT_NAS_PHOLDER);
	boutonAnnuler = new QPushButton(TXT_ANNULER_BOUTON);
	boutonDesinscrire = new QPushButton(TXT_DESINSCRIRE_BOUTON);
}

void DesinscrireElecteur::mettreEnPageLeDialogue()
{
	zoneBoutons = new QHBoxLayout;
	zoneBoutons->addWidget(boutonAnnuler);
	zoneBoutons->addWidget(boutonDesinscrire);

	zoneSaisie = new QHBoxLayout;
	zoneSaisie->addWidget(nasBanniere);
	zoneSaisie->addWidget(nasRecherche);

	zoneGlobale = new QVBoxLayout;
	zoneGlobale->addLayout(zoneSaisie);
	zoneGlobale->addLayout(zoneBoutons);

	setLayout(zoneGlobale);
}

void DesinscrireElecteur::connecterLesSignaux()
{
	connect(boutonAnnuler, SIGNAL(clicked()), this, SLOT(clicBoutonAnnuler()));
	connect(boutonDesinscrire, SIGNAL(clicked()), this, SLOT(accept()));
	connect(boutonDesinscrire, SIGNAL(clicked()), this, SLOT(clicBoutonDesinscrire()));
	connect(nasRecherche, SIGNAL(textEdited(const QString&)), this, SLOT(saisieModifiee()));
}

QString DesinscrireElecteur::reqNasADesinscrire()
{
	return nasSaisi;
}

void DesinscrireElecteur::clicBoutonAnnuler()
{
	rafraichir(INITIAL);
	hide();
}

void DesinscrireElecteur::clicBoutonDesinscrire()
{
	rafraichir(INITIAL);
	hide();
}

void DesinscrireElecteur::rafraichir(Mode nouveauMode)
{
	mode = nouveauMode;
	switch(mode)
	{
	case INITIAL:
		nasRecherche->clear();
		boutonAnnuler->setFocus();
		boutonDesinscrire->setEnabled(false);
		break;
	case EDITION:
		boutonDesinscrire->setEnabled(false);
		break;
	case PRET:
		nasSaisi = nasRecherche->text();
		boutonDesinscrire->setEnabled(true);
		break;
	}

	// TODO implémenter
}

void DesinscrireElecteur::saisieModifiee()
{
	QString saisie = nasRecherche->text();
	rafraichir( util::validerNas(saisie.toStdString()) ? PRET : EDITION) ;
}

DesinscrireElecteur::~DesinscrireElecteur()
{

}
