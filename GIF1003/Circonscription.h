/****************************************************************************//**
 * \file Circonscription.h
 *
 *  Created on: 2020-10-20
 * \author Pascal Charpentier
 *
 * \version 0.1
 *
 *//*****************************************************************************/

#ifndef CIRCONSCRIPTION_H_
#define CIRCONSCRIPTION_H_

#include <vector>
#include <string>
#include "Candidat.h"
#include "Personne.h"

namespace elections {



/****************************************************************************//**
 * \class Circonscription
 *
 * Classe contenant le nom de la circonscription, les informations du député sortant
 * et la liste des électeurs.
 *
 *//*****************************************************************************/

class Circonscription {

private:


	std::string            m_nomCirconscription;
	Candidat               m_deputeElu;
	std::vector<Personne*> m_vInscrits;

	void verifieInvariant() const ;

	bool nasEstPresentDansIntervalle(const std::string& p_nas, std::vector<Personne*>::iterator p_debut);
	bool personneEstDejaPresente(const std::string& p_nas) const;

public:

	/* Swap: échange les membres de deux objets */

	friend void swap(Circonscription& lhs, Circonscription& rhs) ;

	/* Constructeurs */

	Circonscription(const std::string&, const Candidat&);
	Circonscription(const Circonscription&);

	/* Accesseurs */

	const std::string& reqNomCirconscription() const ;
	const Candidat& reqDeputeElu() const ;

	/* Validation interne */

    static bool pointeurEstNul(Personne* p) ;
	bool validerVecteurDesInscrits() const ;
	bool validerCirconscription() const ;

	/* Affichage */

	std::string reqCirconscriptionFormate() const ;

	/* Manipulations de la liste */

	void inscrire(const Personne& ) ;
	void desinscrire(const std::string& p_nas) ;

	/* Opérateurs */

	Circonscription& operator=(Circonscription) ;

	/* Destructeur */

	virtual ~Circonscription();
};

} /* namespace elections */

#endif /* CIRCONSCRIPTION_H_ */
