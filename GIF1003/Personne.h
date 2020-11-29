/****************************************************************************//**
 * \file Personne.h
 *
 * \brief Déclaration de la classe Personne.
 *
 * Créé le: 2020-10-04
 * \author Pascal Charpentier
 * \version 0.1
 *
 *//****************************************************************************/

#ifndef PERSONNE_H_
#define PERSONNE_H_

#include <string>
#include "Date.h"
#include "Adresse.h"

/**
 * \namespace elections
 *
 * Contient la déclaration et la définition de la classe Personne.
 */
namespace elections
{

/****************************************************************************//**
 * Classe abstraite permettant de manipuler les renseignements relatifs à une personne
 *
 * Contient les informations démographiques de base d'une personne ainsi que les
 * méthodes permettant de les modifier, les valider et les afficher.
 *
 *//****************************************************************************/

class Personne
{
private:
	std::string   m_nas;
	std::string   m_nom;
	std::string   m_prenom;
	util::Date    m_dateNaissance;
	util::Adresse m_adresse;

	/* Méthode d'application du contrat */

    void verifieInvariant() const;
	void verifiePostCondition(const std::string& p_nas, const std::string& p_nom, const std::string& p_prenom, const util::Date& p_ddn, const util::Adresse& p_adresse) const;

public:

	/* Validateurs statiques */

	static bool validerPrenom(const std::string& p_prenom);
	static bool validerNom(const std::string& p_nom);
	static bool validerIdentitePersonne(const std::string& p_nas, const std::string& p_nom, const std::string& p_prenom);

	/* Constructeur */

	Personne(const std::string& p_nas, const std::string& p_nom, const std::string& p_prenom, const util::Date& p_dateNaissance, const util::Adresse& p_adresse);

	/* Validateur interne */

	virtual bool valider() const;

	/* Accesseurs */

    const std::string& reqNas() const;
	const std::string& reqNom() const;
	const std::string& reqPrenom() const;
	const util::Date& reqDateNaissance() const;
	const util::Adresse& reqAdresse() const;

	/* Mutateurs */

	void asgAdresse(const util::Adresse& p_nouvelleAdresse);

	/* Opérateurs */

    bool operator== (const Personne& autre) const;
    bool operator != (const Personne& autre) const;

	/* Duplicateurs */

	virtual Personne* clone() const = 0;

	/* Représentations */

	virtual std::string reqPersonneFormate() const = 0;

	/* Destructeur */

	virtual ~Personne() ;

};

} // namespace elections

#endif /* PERSONNE_H_ */
