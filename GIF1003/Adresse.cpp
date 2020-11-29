/****************************************************************************//**
 * \file Adresse.cpp
 * \brief Définition de la classe Adresse
 *
 *  Created on: 2020-09-30
 * \version 0.1
 * \author Pascal Charpentier
 *//*****************************************************************************/

#include "Adresse.h"
#include "validationFormat.h"
#include "ContratException.h"
#include <string>
#include <cstring>
#include <sstream>

#include "environnementTest.h"

namespace util
{

/****************************************************************************//**
 * Vérifier qu'un objet string ne soit pas vide.
 *
 * \param[in] p_ligne Objet string à vérifier
 *
 * \return true si l'objet string est non-vide et contient au-moins un caractère
 * qui ne soit pas du whitespace.
 *
 *//****************************************************************************/

bool Adresse::validerLigneNonVide(const std::string& p_ligne)
{
	return (!util::estUneLigneVide(p_ligne));
}

/****************************************************************************//**
 * Vérifier si un numéro civique est nul ou négatif
 *
 * \param[in] p_numero Le numéro à vérifier
 *
 * \return true s'il est non-nul
 *
 *//****************************************************************************/

bool Adresse::validerNumeroCivic(const int p_numero)
{
	return p_numero > 0;
}

/****************************************************************************//**
 * Vérifier si les 5 champs d'une adresse sont valides.
 *
 * \param[in] p_numero Le numéro civique
 * \param[in] p_nomRue Le nom de la rue
 * \param[in] p_ville Le nom de la ville
 * \param[in] p_codePostal Le code postal
 * \param[in] p_province La province ou le territoire
 *
 * \return true si les 5 champs remplissent les critères de validité suivants:
 * p_numero est non-nul et positif,
 * p_nomRue, p_ville, p_codePostal et p_province sont non-vides
 *
 *//****************************************************************************/

bool Adresse::validerAdresse(
		const int          p_numero,
		const std::string& p_nomRue,
		const std::string& p_ville,
		const std::string& p_codePostal,
		const std::string& p_province)
{
	return validerLigneNonVide(p_codePostal) and
			validerLigneNonVide(p_province) and
			validerNumeroCivic(p_numero) and
			validerLigneNonVide(p_nomRue) and
			validerLigneNonVide(p_ville);
}

/**************************************************************************//**
 * Constructeur de base de la classe
 * \n
 * Simple constructeur par assignation membre à membre.
 *
 * \pre p_numeroCivic est positif
 * \pre p_nom est non-vide
 * \pre p_ville est non-vide
 * \pre p_codePostal est non-vide
 * \pre p_province est non-vide
 *
 * \exception PreconditionException si un des champs n'est pas valide.
 *
 *//***************************************************************************/

Adresse::Adresse(
		const int          p_numeroCivic,
		const std::string& p_nomRue,
    	const std::string& p_ville,
		const std::string& p_codePostal,
		const std::string& p_province) :
				m_numeroCivic(p_numeroCivic),
				m_nomRue(p_nomRue),
				m_ville(p_ville),
				m_codePostal(p_codePostal),
				m_province(p_province)
{
	PRECONDITION(validerAdresse(p_numeroCivic, p_nomRue, p_ville, p_codePostal, p_province));

	INVARIANTS();

	verifiePostCondition(p_numeroCivic, p_nomRue, p_ville, p_codePostal, p_province);
}

/**************************************************************************//**
 * Valide chacun des 5 champs d'un objet adresse.
 *
 * \return true si les 5 champs sont valides, false autrement.
 *
 *//**************************************************************************/

bool Adresse::validerAdresse() const
{
	return validerAdresse(m_numeroCivic, m_nomRue, m_ville, m_codePostal, m_province);
}

/****************************************************************************//**
 * Fonction vérifiant l'intégrité de l'objet Adresse pour les besoins du TP3.
 * Est appelée par la macro INVARIANTS pour garantir que les méthodes non-const
 * préservent l'intégrité de l'objet.
 *
 * \return true si le numéro civique est non-nul et positif, et si les autres
 * champs sont non-vides.
 *
 * \exception InvariantException si un des champs de l'adresse est corrompu: soit
 * le numéro civique est nul ou négatif, soit un des autres champs est vide.
 *
 *//***************************************************************************/

void Adresse::verifieInvariant() const
{
    INVARIANT(validerAdresse());
}

/*****************************************************************************//**
 * Fonction vérifiant l'ensemble des postconditions sur le constructeur et le
 * mutateur:  c'est à dire que les bonnes valeurs ont bien été assignés aux
 * membres correspondants.
 *
 * \param[in] p_numero le numéro civique
 * \param[in] p_rue    le nom de la rue
 * \param[in] p_ville  le nom de la ville
 * \param[in] p_code   le code postal
 * \param[in] p_province le nom de la province
 *
 *//*****************************************************************************/

void Adresse::verifiePostCondition(const int p_numero, const std::string& p_rue, const std::string& p_ville, const std::string& p_code, const std::string& p_province)
{
	POSTCONDITION(p_numero == m_numeroCivic);
	POSTCONDITION(p_rue == m_nomRue);
	POSTCONDITION(p_ville == m_ville);
	POSTCONDITION(p_code == m_codePostal);
	POSTCONDITION(p_province == m_province);
}

/****************************************************************************//**
 * Accesseur du membre numeroCivic
 *
 * \return Un entier sans signe représentant le numéro de porte de l'adresse.
 *
 *//****************************************************************************/

int Adresse::reqNumeroCivic() const
{
	return m_numeroCivic;
}

/****************************************************************************//**
 * Acesseur du membre nomRue
 *
 * \return Un objet string contenant le nom de la rue.
 *
 *//****************************************************************************/

std::string Adresse::reqNomRue() const
{
	return m_nomRue;
}

/****************************************************************************//**
 * Accesseur du membre nomVille
 *
 * \return Un objet string contenant le nom de la ville
 *
 *//****************************************************************************/

std::string Adresse::reqVille() const
{
	return m_ville;
}

/****************************************************************************//**
 * Accesseur du membre m_province
 *
 * \return Un objet string contenant le nom de la province
 *
 *//***************************************************************************/

std::string Adresse::reqProvince() const
{
	return m_province;
}

/****************************************************************************//**
 * Accesseur du membre m_codePostal
 *
 * \return le code postal de l'adressse.
 *
 *//****************************************************************************/

std::string Adresse::reqCodePostal() const
{
	return m_codePostal;
}


/****************************************************************************//**
 * Mutateur d'objet Adresse.  Permet de modifier les 5 champs de l'objet.
 *
 * \param[in] p_nouveauNumero Le nouveau numéro civique
 * \param[in] p_nouveauNomRue Le nouveau nom de rue
 * \param[in] p_nouvelleVille Le nouveau nom de ville
 * \param[in] p_nouveauCodePostal Le nouveau code postal
 * \param[in] p_nouvelleProvince La nouvelle province ou nouveau territoire
 *
 * \pre Le numéro civique est non-nul et positif
 * \pre Le nom de rue est non-vide
 * \pre Le nom de ville est non-vide
 * \pre Le code postal est non-vide
 * \pre Le nom de la province est non-vide
 *
 * \exception PreconditionException si un des champs est vide ou non-valide
 *
 *//****************************************************************************/

void Adresse::asg(const unsigned int p_nouveauNumero,
		const std::string& p_nouveauNomRue,
		const std::string& p_nouvelleVille,
		const std::string& p_nouveauCodePostal,
		const std::string& p_nouvelleProvince)
{
	PRECONDITION(validerAdresse(p_nouveauNumero, p_nouveauNomRue, p_nouvelleVille, p_nouveauCodePostal, p_nouvelleProvince));

	m_numeroCivic = p_nouveauNumero;
	m_ville = p_nouvelleVille;
	m_nomRue = p_nouveauNomRue;
	m_codePostal = p_nouveauCodePostal;
	m_province = p_nouvelleProvince;

    INVARIANTS();

    verifiePostCondition(p_nouveauNumero, p_nouveauNomRue, p_nouvelleVille, p_nouveauCodePostal, p_nouvelleProvince);

}

/****************************************************************************//**
 * Opérateur d'égalité, teste l'égalité des membres de l'objet Adresse avec ceux
 * d'un autre objet.
 *
 * \param[in] p_droite Opérande de droite de l'opérateur
 *
 * \return true si les membres de l'objet courant sont tous égaux à ceux de l'argument.
 *
 *//****************************************************************************/

bool Adresse::operator == (const Adresse& p_droite) const
{
	return (m_numeroCivic == p_droite.m_numeroCivic) and
			(m_nomRue     == p_droite.m_nomRue) and
			(m_ville      == p_droite.m_ville) and
			(m_province   == p_droite.m_province) and
			(m_codePostal == p_droite.m_codePostal);
}

/****************************************************************************//**
 * Teste l'inégalité de deux objets
 *
 * \param[in] p_droite L'objet avec lequel on fait la comparaison
 *
 * \return true si == retourne false.
 *
 *//****************************************************************************/

bool Adresse::operator != (const Adresse& p_droite) const
{
	return !(*this == p_droite);
}

/****************************************************************************//**
 * Bâtit un objet string à-partir d'un objet Adresse.
 * La chaîne de texte est de la forme: numéro, rue, ville, code postal, province
 *
 * \return Chaîne de texte contenant les champs de l'adresse
 *
 *//****************************************************************************/

std::string Adresse::reqAdresseFormatee() const
{
	std::stringstream adresse;
	static const std::string sep = ", ";

	adresse << m_numeroCivic << sep << m_nomRue << sep << m_ville << sep << m_codePostal << sep << m_province;

	return adresse.str();
}

} // Namespace util
