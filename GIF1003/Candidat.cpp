/****************************************************************************//**
 * \file Candidat.cpp
 *
 *  Created on: Oct 19, 2020
 *
 * \author Pascal Charpentier
 *
 * \version 0.1
 *//****************************************************************************/

#include "Candidat.h"
#include "ContratException.h"
#include "validationFormat.h"

#include <sstream>

namespace elections {

/****************************************************************************//**
 * Vérifie qu'un numéro de parti est valide.
 *
 * \param[in] p_parti un numéro de parti politique
 *
 * \return false si p_parti n'est pas dans l'énumération PartisPolitiques
 *
 *//****************************************************************************/

bool Candidat::validerPartiPolitique(PartisPolitiques p_parti)
{
	return (p_parti >= BLOC_QUEBECOIS) and (p_parti <= NOUVEAU_PARTI_DEMOCRATIQUE);
}

/****************************************************************************//**
 * Convertit un numéro de parti en chaîne contenant le nom du parti.
 *
 * \param[in] p_parti le numéro de parti politique
 *
 * \return Le nom du parti politique correspondant
 *
 * \pre Le numéro de parti politique est valide
 *
 * \post La chaîne retournée est un des partis politiques fédéraux
 *
 *//****************************************************************************/

std::string Candidat::formatterPartiPolitique(PartisPolitiques p_parti)
{
	std::string texte = util::PARTIS_POLITIQUES_FEDERAUX[(std::size_t) p_parti];

	PRECONDITION(validerPartiPolitique(p_parti));
	POSTCONDITION(util::estUnPartiPolitique(texte));

	return texte;
}

/*****************************************************************************//**
 * Constructeur paramétrique. Construit un électeur partir d'un NAS d'un nom et
 * prénom ainsi que des objets Date et Adresse valides, et le parti politique.
 *
 * \param[in] p_nas Numéro d'assurance sociale
 * \param[in] p_nom Nom de famille
 * \param[in] p_prenom Prénom valide
 * \param[in] p_date Date de naissance
 * \param[in] p_adresse Adresse courante
 * \param[in] p_parti Parti politique sous lequel se présente le candidat
 *
 * \pre p_nas est un numéro d'assurance sociale valide
 * \pre p_nom est non-vide
 * \pre p_prenom est non-vide
 * \pre p_partiPolitique représente un des partis politiques fédéraux
 *
 * \post Les membres doivent être identiques aux paramètres passés
 *
 * \exception PreconditionException Si un paramètre est invalide
 * \exception InvariantException Si un membre est invalide
 * \exception PostconditionException si un membre ne correspond pas à son paramètre
 *
 *//*****************************************************************************/

Candidat::Candidat(const std::string& p_nas, const std::string& p_nom, const std::string& p_prenom, const util::Date& p_date, const util::Adresse& p_adresse, const PartisPolitiques p_parti)
                 : Personne(p_nas, p_nom,p_prenom, p_date, p_adresse), m_partiPolitique(p_parti)
{
	PRECONDITION(validerPartiPolitique(p_parti));
	INVARIANTS();
	POSTCONDITION(p_parti == m_partiPolitique);
}

/****************************************************************************//**
 * Accesseur de l'attribut parti politique.
 *
 * \return Le numéro du parti politique pour lequel se présente le candidat.
 *
 *//****************************************************************************/

PartisPolitiques Candidat::reqPartiPolitique() const
{
    return m_partiPolitique;
}

/****************************************************************************//**
 * Vérifie les invariants du candidat.
 *
 * \return true si le candidat est une Personne valide et qu'il est affilié à un
 * parti politique valide.
 *
 *//*****************************************************************************/

bool Candidat::valider() const
{
	return validerPartiPolitique(m_partiPolitique);
}

/****************************************************************************//**
 * Vérifie la validité interne de l'objet candidat.
 * La Personne de base doit être valide.
 * Le parti politique doit être valide.
 *
 * \exception InvariantException si l'objet est invalide.
 *
 *//*****************************************************************************/

void Candidat::verifieInvariant() const
{
	INVARIANT(valider());
}

/****************************************************************************//**
 * Retourne une chaine contenant les renseignements d'un candidat sous une forme
 * affichable.
 *
 * \return Chaîne de caractères
 *
 *//*****************************************************************************/

std::string Candidat::reqPersonneFormate() const
{
	static const std::string ENTETE_CANDIDAT = "Candidat\n-------------------------------\n";
	static const std::string PARTI_FORMAT_STR = "Parti             : ";
	std::stringstream os;

	os << ENTETE_CANDIDAT << Personne::reqPersonneFormate() << std::endl << PARTI_FORMAT_STR << formatterPartiPolitique(m_partiPolitique);
	return os.str();
}

/****************************************************************************//**
 * Alloue dynamiquement un espace pour un objet Candidat, et le remplis
 * avec une copie de l'objet courant
 *
 * \return Le pointeur à cet objet
 *//****************************************************************************/

Personne* Candidat::clone() const
{
	return new Candidat(*this) ;
}

/****************************************************************************//**
 * Destructeur.  Vide pour cette classe.
 *//****************************************************************************/

Candidat::~Candidat() {}

} /* namespace elections */
