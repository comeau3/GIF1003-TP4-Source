#include "creerelecteur.h"

CreerElecteur::CreerElecteur(QWidget* parent) : CreerPersonne(parent) {}

elections::Personne* CreerElecteur::reqPersonne()
{
	util::Date d(jourAccepte, moisAccepte, anneeAcceptee);
	util::Adresse a(numCivicAccepte, nomRueAccepte, villeAcceptee, codePostalAccepte, provinceAcceptee);
	return new elections::Electeur(nasAccepte, nomAccepte, prenomAccepte, d, a);
}

CreerElecteur::~CreerElecteur() {}






