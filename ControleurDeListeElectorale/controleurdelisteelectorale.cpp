#include "controleurdelisteelectorale.h"
#include "PersonneException.h"
#include <iostream>

const QString TXT_MENU_FICHIER = QString::fromUtf8("&Fichier");
const QString TXT_MENU_ACTIONS = QString::fromUtf8("&Opérations");
const QString TXT_NOUVEAU_ACTION = QString::fromUtf8("&Nouvelle circonscription");
const QString TXT_SAUVEGARDER_ACTION = QString::fromUtf8("&Sauvegarder");
const QString TXT_RECUPERER_ACTION = QString::fromUtf8("&Récupérer");
const QString TXT_QUITTER_ACTION = QString::fromUtf8("&Quitter");
const QString TXT_NOUVELECTEUR_ACTION = QString::fromUtf8("Nouvel &électeur");
const QString TXT_NOUVCANDIDAT_ACTION = QString::fromUtf8("Nouveau &candidat");
const QString TXT_DESINSCRIRE_ACTION = QString::fromUtf8("&Désinscrire");
const QString TXT_DESINSCRIRE_CONFIRMATION = QString::fromUtf8("Êtes-vous certain de vouloir désinscrire cet électeur? Cette action est irréversible!");
const QString TXT_ATTENTION = QString::fromUtf8("Attention!");
const QString TXT_NAS_INEXISTANT = QString::fromUtf8("Numéro inexistant!");
const QString TXT_PERSONNE_ABSENTE = QString::fromUtf8("Désolé, le numéro %1 n'est pas dans la liste électorale.");
const QString TXT_ERREUR_INSCRIPTION = QString::fromUtf8("Erreur d'inscription!");
const QString TXT_PERSONNE_PRESENTE = QString::fromUtf8("Une personne avec ce numéro existe déjà dans la liste");

ControleurDeListeElectorale::ControleurDeListeElectorale(QWidget *parent)
    : QMainWindow(parent)
{

    initialiserCirconscription();
	initialiserBarreDeMenu();
	initialiserAfficheur();
	initialiserFenetrePrincipale();


	//ui.setupUi(this);
}

void ControleurDeListeElectorale::initialiserCirconscription()
{
	circonscription = new elections::Circonscription("Matane Centre", elections::Candidat("111 111 118", "Poulin", "Paulo", util::Date(1,1,2001), util::Adresse(2020, "du Finfin", "Alma", "G8T 5R5", "Québec"), elections::LIBERAL));
	circonscription->inscrire(elections::Electeur("222 222 226", "Wick", "John", util::Date(2, 2, 2002), util::Adresse(1, "Death Alley", "New-York", "12345", "NY")));
    circonscription->inscrire(elections::Candidat("333 333 334", "Hendrix", "Jimi", util::Date(3, 3, 2003), util::Adresse(2, "Woodstock", "Woodstock", "50210", "NY"), elections::BLOC_QUEBECOIS));
}

void ControleurDeListeElectorale::initialiserBarreDeMenu()
{
	initialiserMenuFichier();
    initialiserMenuActions();
}

void ControleurDeListeElectorale::initialiserAfficheur()
{
	afficheur = new AfficheurDeListeElectorale(circonscription);

	connect(afficheur->reqBoutonCreerNouvelElecteur(), SIGNAL(clicked()), this, SLOT(creerNouvelElecteur()));
	connect(afficheur->reqBoutonCreerNouveauCandidat(), SIGNAL(clicked()), this, SLOT(creerNouveauCandidat()));
	connect(afficheur->reqBoutonDesinscrire(), SIGNAL(clicked()), this, SLOT(desinscrire()));

	setCentralWidget(afficheur);


}

void ControleurDeListeElectorale::initialiserFenetrePrincipale()
{
	desinscripteur = new DesinscrireElecteur;
	desinscripteur->hide();

	inscripteurElecteur = new CreerElecteur;
	inscripteurElecteur->hide();

	inscripteurCandidat = new CreerCandidat;
	inscripteurCandidat->hide();

	std::string titre = "Circonscription: " + circonscription->reqNomCirconscription();
	setWindowTitle(QString::fromStdString(titre));
	setMinimumSize(400, 600);

}

void ControleurDeListeElectorale::initialiserMenuActions()
{
	menuActions = menuBar()->addMenu(TXT_MENU_ACTIONS);

	actionCreerNouvelElecteur = new QAction(TXT_NOUVELECTEUR_ACTION, this);
	actionCreerNouveauCandidat = new QAction(TXT_NOUVCANDIDAT_ACTION, this);
	actionDesinscrire = new QAction(TXT_DESINSCRIRE_ACTION, this);

	menuActions->addAction(actionCreerNouvelElecteur);
	menuActions->addAction(actionCreerNouveauCandidat);
	menuActions->addAction(actionDesinscrire);

	connect(actionCreerNouvelElecteur, SIGNAL(triggered()), this, SLOT(creerNouvelElecteur()));
	connect(actionCreerNouveauCandidat, SIGNAL(triggered()), this, SLOT(creerNouveauCandidat()));
	connect(actionDesinscrire, SIGNAL(triggered()), this, SLOT(desinscrire()));

}

void ControleurDeListeElectorale::initialiserMenuFichier()
{
	menuFichier = menuBar()->addMenu(TXT_MENU_FICHIER);

	actionNouveau = new QAction(TXT_NOUVEAU_ACTION, this);
	actionNouveau->setEnabled(false);
	actionSauvegarder = new QAction(TXT_SAUVEGARDER_ACTION, this);
	actionSauvegarder->setEnabled(false);
	actionRecuperer = new QAction(TXT_RECUPERER_ACTION, this);
	actionRecuperer->setEnabled(false);
	actionQuitter = new QAction(TXT_QUITTER_ACTION, this);

	connect(actionNouveau, SIGNAL(triggered()), this, SLOT(nouveau()));
	connect(actionSauvegarder, SIGNAL(triggered()), this, SLOT(sauvegarder()));
	connect(actionRecuperer, SIGNAL(triggered()), this, SLOT(recuperer()));
	connect(actionQuitter, SIGNAL(triggered()), this, SLOT(quitter()));

	menuFichier->addAction(actionNouveau);
	menuFichier->addAction(actionSauvegarder);
	menuFichier->addAction(actionRecuperer);
	menuFichier->addAction(actionQuitter);


}

void ControleurDeListeElectorale::nouveau()
{
	// TODO implémenter
	std::cerr << "Nouveau\n";
}

void ControleurDeListeElectorale::sauvegarder()
{
	// TODO implémenter en JSON?

	static const QString message = QString::fromUtf8("Sauvegarde des données");
	static const QString typeFichier = QString::fromUtf8("Circonscription (*.circ); ; Tous (*)");
	static const QString messageErreur = QString::fromUtf8("Fichier impossible à ouvrir.");

	QString nomFichier = QFileDialog::getSaveFileName(this, message, "", typeFichier);
	if (nomFichier.isEmpty()) return;

	QFile fichier(nomFichier);
	if (!fichier.open(QIODevice::WriteOnly)) {
		QMessageBox::information(this, messageErreur, fichier.errorString());
		return;
	}

	std::cerr << "Sauvegarde pas encore implémentée\n";

}

void ControleurDeListeElectorale::recuperer()
{
	// TODO implémenter en JSON?

	static const QString message = QString::fromUtf8("Récupération des données");
	static const QString typeFichier = QString::fromUtf8("Circonscription (*.circ); ; Tous (*)");
	static const QString messageErreur = QString::fromUtf8("Fichier impossible à ouvrir.");

	QString nomFichier = QFileDialog::getOpenFileName(this, message, "", typeFichier);
	if (nomFichier.isEmpty()) return;

	QFile fichier(nomFichier);
	if (!fichier.open(QIODevice::ReadOnly)) {
		QMessageBox::information(this, messageErreur, fichier.errorString());
		return;
	}

	std::cerr << "Récupération pas encore implémentée\n";


}

void ControleurDeListeElectorale::quitter()
{
	close();
}

void ControleurDeListeElectorale::creerNouvelElecteur()
{
	inscripteurElecteur->show();
	if (inscripteurElecteur->exec() == QDialog::Accepted)
	{
		try
		{
		    circonscription->inscrire( *inscripteurElecteur->reqElecteur() );
		}
		catch(PersonneDejaPresenteException& e)
		{
			QMessageBox::information(this, TXT_ERREUR_INSCRIPTION, TXT_PERSONNE_PRESENTE);
		}
	}
	afficheur->rafraichir(circonscription);
	inscripteurElecteur->hide();
}

void ControleurDeListeElectorale::creerNouveauCandidat()
{
	inscripteurCandidat->show();
	if (inscripteurCandidat->exec() == QDialog::Accepted)
	{
		try
		{
		    circonscription->inscrire( *inscripteurCandidat->reqCandidat() );
		}
		catch(PersonneDejaPresenteException& e)
		{
			QMessageBox::information(this, TXT_ERREUR_INSCRIPTION, TXT_PERSONNE_PRESENTE);
		}
	}
	afficheur->rafraichir(circonscription);
	inscripteurCandidat->hide();

}

void ControleurDeListeElectorale::desinscrire()
{
	desinscripteur->show();
	if (desinscripteur->exec() == QDialog::Accepted)
	{
	    QString nasADesinscrire = desinscripteur->reqNasADesinscrire();
		auto confirmation = QMessageBox::question(this, TXT_ATTENTION, TXT_DESINSCRIRE_CONFIRMATION, QMessageBox::Yes | QMessageBox::No);
		if (confirmation == QMessageBox::Yes)
		{
			try
			{
			    circonscription->desinscrire(nasADesinscrire.toStdString());
			}
			catch(PersonneAbsenteException& e)
			{
				QMessageBox::information(this, TXT_NAS_INEXISTANT, TXT_PERSONNE_ABSENTE.arg(nasADesinscrire));
			    return;
			}
			afficheur->rafraichir(circonscription);
		}
	}
	desinscripteur->hide();
}


ControleurDeListeElectorale::~ControleurDeListeElectorale()
{
    delete circonscription;
}
