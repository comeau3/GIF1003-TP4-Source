#include "creercandidat.h"
#include "validationFormat.h"
#include "Candidat.h"


const QString TXT_PARTI_BANNIERE        = QString::fromUtf8("Parti politique:");
const QString TXT_CREER_CANDIDAT = QString::fromUtf8("Créer un candidat");

CreerCandidat::CreerCandidat(QWidget *parent) : CreerPersonne(parent)
{

	partiAccepte = elections::BLOC_QUEBECOIS;

	partiBanniere           = new QLabel(TXT_PARTI_BANNIERE);
	zoneBannieres->addWidget(partiBanniere);

	partiSaisie = new QComboBox;
	for (std::size_t numero = 0; numero < util::NB_PARTIS; numero++)
	{
		partiSaisie->addItem(QString::fromStdString(util::PARTIS_POLITIQUES_FEDERAUX[numero]));
	}
	zoneSaisies->addWidget(partiSaisie);

	connect( partiSaisie, SIGNAL( currentIndexChanged(const QString&) ), this, SLOT( formulaireModifie()));
	setWindowTitle(TXT_CREER_CANDIDAT);
}

void CreerCandidat::actualiserSaisies()
{
	// TODO Implémenter

	switch(modeCourant) {
	case EnCours:
		break;
	case Pret:
		break;
	case Initial:
		partiSaisie->setCurrentIndex(0);
		nomSaisie->clear();
		prenomSaisie->clear();
		nasSaisie->clear();
		ddnSaisie->clear();
		ddnSaisie->setDate(QDate(2000, 01, 01));
		ddnSaisie->setFocus();
		numeroCiviqueSaisie->clear();
		nomRueSaisie->clear();
		villeSaisie->clear();
		codePostalSaisie->clear();
		provinceSaisie->setCurrentIndex(0);
		break;
	default:
		return;
	}
}

void CreerCandidat::clicBoutonSoumettre()
{
	partiAccepte = static_cast<elections::PartisPolitiques>(partiSaisie->currentIndex());
	CreerPersonne::clicBoutonSoumettre();

}

elections::Personne* CreerCandidat::reqPersonne()
{
	util::Date d(jourAccepte, moisAccepte, anneeAcceptee);
	util::Adresse a(numCivicAccepte, nomRueAccepte, villeAcceptee, codePostalAccepte, provinceAcceptee);

	return new elections::Candidat(nasAccepte, nomAccepte, prenomAccepte, d, a, partiAccepte);
}

CreerCandidat::~CreerCandidat() {}






