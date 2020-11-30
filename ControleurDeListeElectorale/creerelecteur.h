#ifndef CREERELECTEUR_H
#define CREERELECTEUR_H

#include <QtGui>
#include "creerpersonne.h"
#include "Electeur.h"

class CreerElecteur : public CreerPersonne
{
public:
	CreerElecteur(QWidget *parent = 0);
	~CreerElecteur();

	elections::Personne* reqPersonne();
};


#endif
