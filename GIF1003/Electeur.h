/***************************************************************************//**
 * \file Electeur.h
 *
 *  Created on: 2020-10-20
 * \author Pascal Charpentier
 *
 *//****************************************************************************/

#ifndef ELECTEUR_H_
#define ELECTEUR_H_

#include "Personne.h"
#include <string>

namespace elections {

/****************************************************************************//**
 * \class Electeur
 *
 * Classe dérivée de Personne.  Contient les renseignements démographiques d'un
 * électeur.  Peut aussi être affiché sous forme de chaîne de texte.  Contient
 * une méthode permettant l'allocation dynamique.
 *
 *//*****************************************************************************/

class Electeur: public Personne {

public:

	/* Constructeurs */

	Electeur(const std::string&, const std::string&, const std::string&, const util::Date&, const util::Adresse&);

	/* Affichage */

	std::string reqPersonneFormate() const override;

	/* Allocation dynamique */

	Personne* clone() const override;

	/* Destructeur */

    ~Electeur() ;
};

} /* namespace elections */

#endif /* ELECTEUR_H_ */
