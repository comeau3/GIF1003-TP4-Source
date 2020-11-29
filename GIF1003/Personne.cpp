/****************************************************************************//**
 * \file Personne.cpp
 *
 * \brief Définition de la classe Personne
 *
 * Créé le: 2020-10-04
 * \author Pascal Charpentier
 *
 * \version 0.2
 *
 *//***************************************************************************/

#include "Personne.h"
#include "Date.h"
#include "Adresse.h"
#include "validationFormat.h"
#include "ContratException.h"
#include <cassert>
#include <sstream>
#include <stdexcept>
#include <cstring>

/**
 * \namespace elections
 *
 * Contient la définition de la classe Personne.
 */
namespace elections
{

/****************************************************************************//**
 * Vérifie si les champs nom, prénom et numéro d'assurance sociale sont valides pour un objet Personne.
 *
 * \param[in] p_nas Le numéro d'assurance sociale (format XXX XXX XXX)
 * \param[in] p_nom Le champs nom (non-vide)
 * \param[in] p_prenom Le champs prénom. (non-vide)
 *
 * .\return true si les trois champs sont valides.
 *//****************************************************************************/

bool Personne::validerIdentitePersonne(const std::string& p_nas, const std::string& p_nom, const std::string& p_prenom)
{
	return util::validerNas(p_nas) and util::estUnNom(p_nom) and util::estUnNom(p_prenom);
}


/************************************************************************//**
 * Constructeur de base de la classe, par affectation membre à membre
 *
 * \param[in] p_nas Objet string contenant un numéro d'assurance sociale
 * \param[in] p_nom Objet string contenant un nom de famille
 * \param[in] p_prenom Objet string contenant un prénom
 * \param[in] p_date Objet Date contenant une date de naissance
 * \param[in] p_adresse Objet Adresse contenant une adresse
 *
 * \pre p_nas est un numéro d'assurance sociale valide
 * \pre p_nom est non-vide
 * \pre p_prenom est non-vide
 * \pre p_date est un objet Date valide
 * \pre p_adresse est un objet Adresse valide
 *
 * \exception PreconditionException si les paramètres d'entrées ne sont pas valides
 * \exception InvariantException si un objet Personne non-valide est créé
 *
 *//***********************************************************************/

Personne::Personne(const std::string& p_nas, const std::string& p_nom, const std::string& p_prenom,
		const util::Date& p_date, const util::Adresse& p_adresse) :
				m_nas(p_nas), m_nom(p_nom), m_prenom(p_prenom), m_dateNaissance(p_date), m_adresse(p_adresse)
{
    PRECONDITION(validerIdentitePersonne(p_nas, p_nom,p_prenom));

    INVARIANTS();

    verifiePostCondition(p_nas, p_nom, p_prenom, p_date, p_adresse);


}

/****************************************************************************//**
 * Vérifie si les attributs d'un objet Personne sont valides.
 *
 * \return true si le NAS est valide, si les noms et prénoms sont non-vides
 * et si les membres Adresse et Date sont valides.
 *
 *//****************************************************************************/

bool Personne::valider() const
{
	return validerIdentitePersonne(m_nas, m_nom, m_prenom);
}

/****************************************************************************//**
 * Fonction invoquant une macro qui valide les invariants de la classe Personne.
 *
 * \exception InvariantException si un des membres est invalide
 *//****************************************************************************/

void Personne::verifieInvariant() const
{
	INVARIANT(valider());
}

/****************************************************************************//**
 * Fonction qui vérifie les postconditions du contrat après un constructeur ou
 * une assignation ou une copie.
 *
 * \param[in] p_nas Numéro d'assurance sociale attendu
 * \param[in] p_nom Nom de famille attendu
 * \param[in] p_prenom Prénom attendu
 * \param[in] objet date contenant la date de naissance attendue
 * \param[in] objet adresse contenant l'adresse attendue
 *
 * \exception PostconditionException si une des valeurs ne correspond pas aux valeurs attendues
 *
 *//*****************************************************************************/

void Personne::verifiePostCondition(const std::string& p_nas, const std::string& p_nom, const std::string& p_prenom, const util::Date& p_ddn, const util::Adresse& p_adresse) const
{
	POSTCONDITION(p_nas == m_nas);
	POSTCONDITION(p_prenom == m_prenom);
	POSTCONDITION(p_nom == m_nom);
	POSTCONDITION(p_ddn == m_dateNaissance);
	POSTCONDITION(p_adresse == m_adresse);
}

/****************************************************************************//**
 * Accesseur du membre m_nas
 *
 * \return Le numéro d'assurance sociale
 *//****************************************************************************/

const std::string& Personne::reqNas() const
{
	return m_nas;
}

/****************************************************************************//**
 * Accesseur du membre m_nom
 *
 * \return Le nom de famille
 *//****************************************************************************/

const std::string& Personne::reqNom() const
{
	return m_nom;
}

/****************************************************************************//**
 * Accesseur du membre m_prenom
 *
 * \return Le prénom
 *//****************************************************************************/

const std::string& Personne::reqPrenom() const
{
	return m_prenom;
}

/****************************************************************************//**
 * Accesseur de la date de naissance
 *
 * \return L'objet Date contenant la date de naissance de la personne
 *//****************************************************************************/

const util::Date& Personne::reqDateNaissance() const
{
	return m_dateNaissance;
}

/****************************************************************************//**
 * Accesseur de l'adresse
 *
 * \return Objet Adresse contenant l'adresse de la personne
 *//****************************************************************************/

const util::Adresse& Personne::reqAdresse() const
{
	return m_adresse;
}

/****************************************************************************//**
 * Mutateur de l'adresse d'un objet Personne
 *
 * \param[in] p_nouvelleAdresse L'objet Adresse contenant la nouvelle adresse
 *
 * \pre La nouvelle adresse est un objet valide
 * \post La nouvelle adresse correspond à l'objet en paramètre
 *
 * \exception PreconditionException si l'objet Date passé n'est pas valide
 * \exception InvariantException si l'objet courant est corrompu
 * \exception PostconditionException si l'assignation ne s'est pas fait normalement
 *
 *//****************************************************************************/

void Personne::asgAdresse(const util::Adresse& p_nouvelleAdresse)
{
	PRECONDITION(p_nouvelleAdresse.validerAdresse());

	m_adresse = p_nouvelleAdresse;

	INVARIANTS();
	POSTCONDITION(m_adresse == p_nouvelleAdresse);
}


/****************************************************************************//**
 * Opérateur d'égalité
 *
 * \return true si tous les attributs de l'objet courant sont identiques en valeur aux attributs
 * de l'autre opérande.
 *
 *//****************************************************************************/

bool Personne::operator == (const Personne& autre) const
{
	return m_nas            == autre.m_nas and
			m_nom           == autre.m_nom and
			m_prenom        == autre.m_prenom and
			m_adresse       == autre.m_adresse and
			m_dateNaissance == autre.m_dateNaissance;
}

/****************************************************************************//**
 * Opérateur d'inégalité
 *
 * \return true si au-moins un des attributs de l'objet courant est différent de l'attribut
 * correspondant de l'autre opérande.
 *
 *//****************************************************************************/

bool Personne::operator != (const Personne& autre) const
{
	return !(*this == autre);
}

/****************************************************************************//**
 * Construit une reprsentation affichable de l'objet Personne
 *
 * \return Un objet string représentant les attributs de la Personne
 *//****************************************************************************/

std::string Personne::reqPersonneFormate() const
{
	static std::string NAS_FORMAT_STR = "NAS               : ";
	static std::string NOM_FORMAT_STR = "Nom               : ";
	static std::string PRE_FORMAT_STR = "Prénom            : ";
	static std::string DAT_FORMAT_STR = "Date de naissance : ";
	static std::string ADR_FORMAT_STR = "Adresse           : ";
    std::stringstream os;

    os << NAS_FORMAT_STR << m_nas << '\n';
    os << NOM_FORMAT_STR << m_nom << '\n';
    os << PRE_FORMAT_STR << m_prenom << '\n';
    os << DAT_FORMAT_STR << m_dateNaissance.reqDateFormatee() << '\n';
    os << ADR_FORMAT_STR << m_adresse.reqAdresseFormatee();

    return os.str();
}

/****************************************************************************//**
 * Destructeur
 *
 *//****************************************************************************/

Personne:: ~Personne() {}

} // Namespace elections


