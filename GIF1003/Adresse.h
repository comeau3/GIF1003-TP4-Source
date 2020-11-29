/**
 * \file Adresse.h
 * \brief Déclaration de la classe Adresse
 *
 *  Created on: 2020-09-30
 *  \version 0.1
 *  \author Pascal Charpentier
 */

#ifndef ADRESSE_H_
#define ADRESSE_H_

#include "environnementTest.h"

#include <string>

namespace util
{

/**
 * \class Adresse
 * \brief Représentation d'une adresse civique au Canada
 *
 * Contient les champs habituels d'une adresse canadienne:\n
 * Le numéro de porte\n
 * Le nom de la rue\n
 * La ville\n
 * Le code postal\n
 * La province ou territoire, en français.\n
 *
 */

class Adresse
{

private:

	int          m_numeroCivic;
	std::string  m_nomRue;
	std::string  m_ville;
	std::string  m_codePostal;
	std::string  m_province;

	/* Méthodes privées de vérification du contrat */

    void verifieInvariant() const ;
    void verifiePostCondition(const int p_numero, const std::string& p_rue, const std::string& p_ville, const std::string& p_code, const std::string& p_province);


public:

    /* Validateurs statiques */

	static bool validerLigneNonVide(const std::string& p_ligne);
	static bool validerNumeroCivic(const int numero);
	static bool validerAdresse(
			const int          p_numero,
			const std::string& p_nomRue,
			const std::string& p_ville,
			const std::string& p_codePostal,
			const std::string& p_province);

	/* Constructeur */

    Adresse(const int numeroCivic,
    		const std::string& nomRue,
			const std::string& ville,
			const std::string& codePostal,
			const std::string& province);

    /* Accesseurs */

    int          reqNumeroCivic() const;
    std::string  reqNomRue() const;
    std::string  reqVille() const;
    std::string  reqCodePostal() const;
    std::string  reqProvince() const;

    /* Validateur */

    bool validerAdresse() const ;

    /* Mutateur */

    void asg(const unsigned int nouveauNumero,
				  const std::string& nouveauNomRue,
				  const std::string& nouvelleVille,
				  const std::string& nouveauCodePostal,
				  const std::string& nouvelleProvince);

    /* Opérateurs d'égalité */

    bool operator == (const Adresse& adresse) const;
    bool operator != (const Adresse& adresse) const;

    /* Sortie formattée */

    std::string reqAdresseFormatee() const;

}; // class Adresse

} // Namespace util




#endif /* ADRESSE_H_ */
