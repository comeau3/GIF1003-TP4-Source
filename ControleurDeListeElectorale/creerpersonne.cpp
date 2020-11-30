#include "creerpersonne.h"
#include "validationFormat.h"
//#include <iostream>

const QString TXT_SOUMETTRE     = QString::fromUtf8("&Soumettre");
const QString TXT_ANNULER       = QString::fromUtf8("&Annuler");
const QString TXT_REINITIALISER = QString::fromUtf8("&Réinitialiser");

const QString TXT_NOM_BANNIERE    		= QString::fromUtf8("Nom de famille:");
const QString TXT_PRENOM_BANNIERE 		= QString::fromUtf8("Prénom:");
const QString TXT_DDN_BANNIERE   		= QString::fromUtf8("Date de naissance:");
const QString TXT_NAS_BANNIERE    		= QString::fromUtf8("Numéro d'assurance sociale:");
const QString TXT_NUMCIVIQUE_BANNIERE 	= QString::fromUtf8("Numéro civique:");
const QString TXT_NOMRUE_BANNIERE 		= QString::fromUtf8("Nom de rue:");
const QString TXT_VILLE_BANNIERE 		= QString::fromUtf8("Ville:");
const QString TXT_CODEPOSTAL_BANNIERE 	= QString::fromUtf8("Code Postal:");
const QString TXT_PROVINCE_BANNIERE 	= QString::fromUtf8("Province:");

const QString TXT_NOM_PHOLDER			= QString::fromUtf8("Nom de famille");
const QString TXT_PRENOM_PHOLDER 		= QString::fromUtf8("Prénom");
const QString TXT_NAS_PHOLDER 			= QString::fromUtf8("888 888 888");
const QString TXT_NUMCIVIQUE_PHOLDER 	= QString::fromUtf8("Numéro civique");
const QString TXT_NOMRUE_PHOLDER 		= QString::fromUtf8("Nom de rue");
const QString TXT_VILLE_PHOLDER 		= QString::fromUtf8("Ville");
const QString TXT_CODEPOSTAL_PHOLDER 	= QString::fromUtf8("A1A 1A1");

const QString TXT_VALIDE                = QString::fromUtf8("Valide");
const QString TXT_NON_VALIDE            = QString::fromUtf8("Non valide");

const QString TXT_CREER_ELECTEUR = QString::fromUtf8("Créer un nouvel électeur");

// TODO Permettre l'édition d'un électeur existant avec le même QDialog (pointeur nullptr en argument: créer, sinon modifier)
// TODO Les dates min, max et default ne devraient pas être codées en dur.  À corriger

CreerPersonne::CreerPersonne(QWidget *parent)
: QDialog(parent)
{

	initialiserBoutons();
	initialiserBannieres();
	initialiserZonesDeSaisie();
	initialiserZonesDeValidation();

	miseEnPageDuFormulaire();

	actualiser(Initial);
}

void CreerPersonne::initialiserBoutons()
{
	boutonSoumettre = new QPushButton(TXT_SOUMETTRE);
	boutonSoumettre->show();

	boutonAnnuler   = new QPushButton(TXT_ANNULER);
	boutonAnnuler->show();
	boutonAnnuler->setEnabled(true);

	boutonReInitialiser = new QPushButton(TXT_REINITIALISER);
	boutonReInitialiser->show();

	zoneBoutons = new QHBoxLayout;
	zoneBoutons->addWidget(boutonSoumettre);
	zoneBoutons->addWidget(boutonAnnuler);
	zoneBoutons->addWidget(boutonReInitialiser);

	connect( boutonReInitialiser, SIGNAL( clicked() ), this, SLOT( clicBoutonReInitialiser() ) );
	connect( boutonAnnuler, SIGNAL( clicked() ), this, SLOT( clicBoutonAnnuler() ) );
	connect( boutonSoumettre, SIGNAL( clicked() ), this, SLOT( clicBoutonSoumettre() ) );

}

void CreerPersonne::initialiserBannieres()
{
	nomBanniere    			= new QLabel(TXT_NOM_BANNIERE);
	prenomBanniere 			= new QLabel(TXT_PRENOM_BANNIERE);
	ddnBanniere    			= new QLabel(TXT_DDN_BANNIERE);
	nasBanniere    			= new QLabel(TXT_NAS_BANNIERE);
	numeroCiviqueBanniere	= new QLabel(TXT_NUMCIVIQUE_BANNIERE);
	nomRueBanniere			= new QLabel(TXT_NOMRUE_BANNIERE);
	villeBanniere			= new QLabel(TXT_VILLE_BANNIERE);
	codePostalBanniere		= new QLabel(TXT_CODEPOSTAL_BANNIERE);
	provinceBanniere		= new QLabel(TXT_PROVINCE_BANNIERE);
	zoneBannieres  			= new QVBoxLayout;

	zoneBannieres->addWidget(nomBanniere);
	zoneBannieres->addWidget(prenomBanniere);
	zoneBannieres->addWidget(nasBanniere);
    zoneBannieres->addWidget(ddnBanniere);
    zoneBannieres->addWidget(numeroCiviqueBanniere);
    zoneBannieres->addWidget(nomRueBanniere);
    zoneBannieres->addWidget(villeBanniere);
    zoneBannieres->addWidget(codePostalBanniere);
    zoneBannieres->addWidget(provinceBanniere);


}

void CreerPersonne::initialiserZonesDeSaisie()
{
    nomSaisie    		= new QLineEdit;
    nomSaisie			->setPlaceholderText(TXT_NOM_PHOLDER);

    prenomSaisie 		= new QLineEdit;
    prenomSaisie		->setPlaceholderText(TXT_PRENOM_PHOLDER);

    nasSaisie    		= new QLineEdit;
    // TODO ne marche pas bien : nasSaisie->setInputMask("999 999 999");
    nasSaisie			->setPlaceholderText(TXT_NAS_PHOLDER);

    ddnSaisie    		= new QDateEdit;
    ddnSaisie			->setMinimumDate(QDate(1970, 01, 01));
    ddnSaisie			->setMaximumDate(QDate(2037, 12, 31));
    ddnSaisie			->setDisplayFormat("dd-MM-yyyy");
    ddnSaisie			->setCalendarPopup(true);

    numeroCiviqueSaisie = new QLineEdit;
    numeroCiviqueSaisie->setPlaceholderText(TXT_NUMCIVIQUE_PHOLDER);

    nomRueSaisie 		= new QLineEdit;
    nomRueSaisie		->setPlaceholderText(TXT_NOMRUE_PHOLDER);

    villeSaisie 		= new QLineEdit;
    villeSaisie			->setPlaceholderText(TXT_VILLE_PHOLDER);

    codePostalSaisie 	= new QLineEdit;
    codePostalSaisie	->setPlaceholderText(TXT_CODEPOSTAL_PHOLDER);

    provinceSaisie		= new QComboBox;
    provinceSaisie->addItem(tr("Alberta"));
    provinceSaisie->addItem(tr("Colombie-Britannique"));
    provinceSaisie->addItem(tr("Ile du Prince Edouard"));
    provinceSaisie->addItem(tr("Manitoba"));
    provinceSaisie->addItem(tr("Nouveau-Brunswick"));
    provinceSaisie->addItem(tr("Nouvelle-Ecosse"));
    provinceSaisie->addItem(tr("Nunavut"));
    provinceSaisie->addItem(tr("Ontario"));
    provinceSaisie->addItem(tr("Quebec"));
    provinceSaisie->addItem(tr("Saskatchewan"));
    provinceSaisie->addItem(tr("Terre-Neuve"));
    provinceSaisie->addItem(tr("Territoires du Nord-Ouest"));
    provinceSaisie->addItem(tr("Yukon"));


	zoneSaisies 		= new QVBoxLayout;
	zoneSaisies			->addWidget(nomSaisie);
	zoneSaisies			->addWidget(prenomSaisie);
	zoneSaisies			->addWidget(nasSaisie);
	zoneSaisies			->addWidget(ddnSaisie);
	zoneSaisies			->addWidget(numeroCiviqueSaisie);
	zoneSaisies			->addWidget(nomRueSaisie);
	zoneSaisies			->addWidget(villeSaisie);
	zoneSaisies			->addWidget(codePostalSaisie);
	zoneSaisies			->addWidget(provinceSaisie);

	connect( nomSaisie, SIGNAL( textEdited(const QString&) ), this, SLOT( formulaireModifie() ) );
	connect( prenomSaisie, SIGNAL( textEdited(const QString&) ), this, SLOT( formulaireModifie() ) );
	connect( nasSaisie, SIGNAL( textEdited(const QString&) ), this, SLOT( formulaireModifie() ) );
	connect( ddnSaisie, SIGNAL( dateChanged(const QDate&) ), this, SLOT( formulaireModifie() ) );
	connect( numeroCiviqueSaisie, SIGNAL( textEdited(const QString&) ), this, SLOT( formulaireModifie() ) );
	connect( nomRueSaisie, SIGNAL( textEdited(const QString&) ), this, SLOT( formulaireModifie() ) );
	connect( villeSaisie, SIGNAL( textEdited(const QString&) ), this, SLOT( formulaireModifie() ) );
	connect( codePostalSaisie, SIGNAL( textEdited(const QString&) ), this, SLOT( formulaireModifie() ) );
	connect( provinceSaisie, SIGNAL( currentIndexChanged(const QString&) ), this, SLOT( formulaireModifie() ) );

}

void CreerPersonne::initialiserZonesDeValidation()
{
	nomValidation = new QLabel(TXT_NON_VALIDE);
	nomValidation->setStyleSheet("color: red");
	prenomValidation = new QLabel(TXT_NON_VALIDE);
	prenomValidation->setStyleSheet("color: red");
	nasValidation = new QLabel(TXT_NON_VALIDE);
	nasValidation->setStyleSheet("color: red");
	ddnValidation = new QLabel(TXT_VALIDE);
	ddnValidation->setStyleSheet("color: green");
	numeroCiviqueValidation = new QLabel(TXT_NON_VALIDE);
	numeroCiviqueValidation->setStyleSheet("color: red");
	nomRueValidation = new QLabel(TXT_NON_VALIDE);
	nomRueValidation->setStyleSheet("color: red");
	villeValidation = new QLabel(TXT_NON_VALIDE);
	villeValidation->setStyleSheet("color: red");
	codePostalValidation = new QLabel(TXT_NON_VALIDE);
	codePostalValidation->setStyleSheet("color: red");
	provinceValidation = new QLabel(TXT_VALIDE);
	provinceValidation->setStyleSheet("color:green");

	zoneValidations = new QVBoxLayout;
	zoneValidations->addWidget(nomValidation);
	zoneValidations->addWidget(prenomValidation);
	zoneValidations->addWidget(nasValidation);
	zoneValidations->addWidget(ddnValidation);
	zoneValidations->addWidget(numeroCiviqueValidation);
	zoneValidations->addWidget(nomRueValidation);
	zoneValidations->addWidget(villeValidation);
	zoneValidations->addWidget(codePostalValidation);
	zoneValidations->addWidget(provinceValidation);
}

void CreerPersonne::miseEnPageDuFormulaire()
{
	zoneSuperieure = new QHBoxLayout;
	zoneSuperieure->addLayout(zoneBannieres);
	zoneSuperieure->addLayout(zoneSaisies);
	zoneSuperieure->addLayout(zoneValidations);

	zoneGlobale = new QGridLayout;
	zoneGlobale->addLayout(zoneSuperieure, 0, 0);
	zoneGlobale->addLayout(zoneBoutons, 1, 0);

	setLayout(zoneGlobale);
	setWindowTitle(TXT_CREER_ELECTEUR);

}

void CreerPersonne::actualiserBoutons()
{
	switch(modeCourant) {
	case EnCours:
		boutonSoumettre->setEnabled(false);
		boutonReInitialiser->setEnabled(true);
		break;
	case Pret:
		boutonSoumettre->setEnabled(true);
		boutonReInitialiser->setEnabled(true);
		break;
	case Initial:
		boutonSoumettre->setEnabled(false);
		boutonReInitialiser->setEnabled(false);
		break;
	default:
		return;
	}
}

void CreerPersonne::actualiserSaisies()
{
	// TODO Implémenter

	switch(modeCourant) {
	case EnCours:
		break;
	case Pret:
		break;
	case Initial:
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

void CreerPersonne::actualiserMessageDeValidation(QLabel* validation, bool valeur)
{
	validation->setStyleSheet(valeur ? "color: green" : "color: red");
	validation->setText(valeur ? TXT_VALIDE : TXT_NON_VALIDE);
}

void CreerPersonne::actualiserValidations()
{
	// ddn et province seront toujours considérés valides

    actualiserMessageDeValidation(nomValidation, laSaisieNomEstValide());
    actualiserMessageDeValidation(prenomValidation, laSaisiePrenomEstValide());
    actualiserMessageDeValidation(nasValidation, laSaisieNasEstValide());
    actualiserMessageDeValidation(numeroCiviqueValidation, util::estUnEntierPositif(numeroCiviqueSaisie->text().toStdString()));
    actualiserMessageDeValidation(nomRueValidation, util::estUnNom(nomRueSaisie->text().toStdString()));
    actualiserMessageDeValidation(villeValidation, util::estUnNom(villeSaisie->text().toStdString()));
    actualiserMessageDeValidation(codePostalValidation, util::validerCodePostal(codePostalSaisie->text().toStdString()));
}

void CreerPersonne::actualiserValeursAcceptees()
{
   switch(modeCourant)
   {
   case Pret:
	   break;
   case EnCours:
	   break;
   case Initial:
	   jourAccepte = ddnSaisie->date().day();
	   moisAccepte = ddnSaisie->date().month();
	   anneeAcceptee = ddnSaisie->date().year();
	   provinceAcceptee = provinceSaisie->currentText().toStdString();
   }
}

bool CreerPersonne::laSaisieNomEstValide()
{
	QString texte = nomSaisie->text();
	return util::estUnNom(texte.toStdString());
}

bool CreerPersonne::laSaisiePrenomEstValide()
{
	QString texte = prenomSaisie->text();
	return util::estUnNom(texte.toStdString());
}

bool CreerPersonne::laSaisieNasEstValide()
{
	QString texte = nasSaisie->text();
	return util::validerNas(texte.toStdString());
}

bool CreerPersonne::laSaisieDateEstValide()
{
	// Pour l'instant la date est toujours considérée valide
	return true;
}

bool  CreerPersonne::laSaisieAdresseEstValide()
{
	std::string chiffre 	= numeroCiviqueSaisie->text().toStdString();
	std::string texte1 		= nomRueSaisie->text().toStdString();
	std::string texte2 		= villeSaisie->text().toStdString();
	std::string texte3		= codePostalSaisie->text().toStdString();
	return util::estUnEntierPositif(chiffre) and util::estUnNom(texte1) and util::estUnNom(texte2)
	and util::validerCodePostal(texte3);
}

bool CreerPersonne::lesSaisiesSontToutesValides()
{
	// TODO implémenter: vérifie la validité du NAS, du nom, du prénom et de la date.

	return laSaisieNomEstValide() and laSaisiePrenomEstValide() and laSaisieNasEstValide() and laSaisieDateEstValide()
			and laSaisieAdresseEstValide();
}

void CreerPersonne::actualiser(Mode mode)
{
	modeCourant = mode;

	actualiserBoutons();
	actualiserSaisies();
	actualiserValidations();
}

void CreerPersonne::clicBoutonSoumettre()
{
	nasAccepte = nasSaisie->text().toStdString();
	nomAccepte = nomSaisie->text().toStdString();
	prenomAccepte = prenomSaisie->text().toStdString();


	QDate qdate = ddnSaisie->date();

	jourAccepte = qdate.day();
	moisAccepte = qdate.month();
	anneeAcceptee = qdate.year();

	numCivicAccepte = numeroCiviqueSaisie->text().toInt();
	nomRueAccepte = nomRueSaisie->text().toStdString();
	villeAcceptee = villeSaisie->text().toStdString();
	codePostalAccepte = codePostalSaisie->text().toStdString();
	provinceAcceptee = provinceSaisie->currentText().toStdString();

	actualiser(Initial);
	accept();

}

void CreerPersonne::clicBoutonAnnuler()
{
    // TODO implémenter: Efface la fenêtre.  Demande si l'utilisateur est certain.
    actualiser(Initial);
	close();
}

void CreerPersonne::clicBoutonReInitialiser()
{
	// TODO implémenter: ramène tous les champs à leur valeur initiale. Demande si certain.
	// TODO Remet le formulaire au mode Initial

	actualiser(Initial);
}

void CreerPersonne::formulaireModifie()
{
	actualiser( lesSaisiesSontToutesValides() ? Pret : EnCours );
}

CreerPersonne::~CreerPersonne() {}






