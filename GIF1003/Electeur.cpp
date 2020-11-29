/****************************************************************************//**
 * \file Electeur.cpp
 *
 *  Created on: 2020-10-20
 *  \author Pascal Charpentier
 *
 *  \version 0.1
 *
 *//****************************************************************************/

#include "Electeur.h"
#include "saisies.h"

namespace elections {


/****************************************************************************//**
 * Constructeur paramétrique utilisant des objets
 *
 * \p_nas Numéro d'assurance sociale
 * \p_prenom Prénom
 * \p_nom Nom de famille
 * \p_date Date de naissance sous forme d'un objet Date
 * \p_adresse Adresse postale sous forme d'un objet Adresse
 *
 * \pre p_nas est un NAS valide
 * \pre p_prenom est non-vide
 * \pre p_nom est non-vide
 * \post Chaque membre est identique au paramètre correspondant
 *
 * \exception PreconditionException si un des paramètres est non-valide
 * \exception InvariantException si un des membres est non-valide
 * \exception PostconditionException si les membres ne correspondent pas aux paramètres
 *
 *//*****************************************************************************/

Electeur::Electeur(const std::string& p_nas, const std::string& p_nom, const std::string& p_prenom, const util::Date& p_date, const util::Adresse& p_adresse) :
		Personne(p_nas, p_nom, p_prenom, p_date, p_adresse)
{

}

/****************************************************************************//**
 * Retourne une chaîne de caractères contenant les attributs d'un Electeur sous
 * une forme affichable
 *
 * \return Chaîne de caractères
 *//*****************************************************************************/

std::string Electeur::reqPersonneFormate() const
{
	static std::string ENTETE_ELECTEUR = "Électeur\n------------------------------\n";
	return ENTETE_ELECTEUR + Personne::reqPersonneFormate();
}

/****************************************************************************//**
 * Alloue un objet Electeur dynamique, copie de l'objet courant
 *
 * \return Un pointeur à cet objet
 *
 *//*****************************************************************************/

Personne* Electeur::clone() const
{
	return new Electeur(*this);
}

/****************************************************************************//**
 * Destructeur
 *//****************************************************************************/

Electeur::~Electeur() {}

} /* namespace elections */
