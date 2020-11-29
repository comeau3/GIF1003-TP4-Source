/****************************************************************************//**
 * \file Candidat.h
 *
 *  Created on: Oct 19, 2020
 *  \author Pascal Charpentier
 *
 *  \version 0.1
 *
 *//****************************************************************************/

#ifndef CANDIDAT_H_
#define CANDIDAT_H_


#include "Personne.h"

namespace elections {

/****************************************************************************//**
 * \type PartisPolitiques
 *
 * Chaque constante représente un des principaux partis politiques fédéraux
 *
 *//****************************************************************************/

enum PartisPolitiques {BLOC_QUEBECOIS, CONSERVATEUR, INDEPENDANT, LIBERAL, NOUVEAU_PARTI_DEMOCRATIQUE};

/****************************************************************************//**
 * \class Candidat
 *
 * Classe dérivée de Personne.  Outre les informations démographiques du candidat,
 * contient aussi un attribut m_partiPolitique représentant l'affiliation politique
 * du candidat.  Contient aussi une méthode d'affichage ainsi qu'une méthode d'allocation
 * dynamique.
 *
 *//*****************************************************************************/

class Candidat: public Personne {

private:

	PartisPolitiques m_partiPolitique;

	/* Validation privée du contrat */

	void verifieInvariant() const;

public:

	/* Validateurs statiques */

	static bool validerPartiPolitique(PartisPolitiques p_parti);
	static std::string formatterPartiPolitique(PartisPolitiques p_parti);

	/* Constructeurs */

	Candidat(const std::string&, const std::string&, const std::string&, const util::Date&, const util::Adresse&, const PartisPolitiques p_parti);

	/* Accesseurs */

	PartisPolitiques reqPartiPolitique() const;

	/* Validateurs internes pour le contrat */

	bool valider() const override ;

	/* Affichage */

	std::string reqPersonneFormate() const override;

	/* Copie dynamique */

	Personne* clone() const override;

	/* Destructeur */

	virtual ~Candidat();
};

} /* namespace elections */

#endif /* CANDIDAT_H_ */
