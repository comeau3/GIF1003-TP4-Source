/****************************************************************************//**
 * \file saisies.cpp
 *
 * \brief Fonctions de validation de saisies à la console
 *
 *  Created on: Oct 5, 2020
 *  \author Pascal Charpentier
 *//****************************************************************************/

#include "Adresse.h"
#include "Date.h"
#include "Personne.h"
#include "Electeur.h"
#include "Candidat.h"
#include "validationFormat.h"
#include "saisies.h"

#include <iostream>
#include <string>
#include <iomanip>

/****************************************************************************//**
 * Constantes:  messages à l'utilisateur
 *
 *//****************************************************************************/

static std::string MSG_SAISIR_NUMERO =      "Veuillez saisir un numéro civique";
static std::string MSG_SAISIR_RUE =         "Veuillez saisir un nom de rue";
static std::string MSG_SAISIR_VILLE =       "Veuillez saisir un nom de ville";
static std::string MSG_SAISIR_CODE_POSTAL = "Veuillez saisir le code postal";
static std::string MSG_SAISIR_PROVINCE =    "Veuillez saisir un nom de province canadienne";
static std::string MSG_SAISIR_NAS =         "Veuillez saisir un numéro d'assurance sociale au format XXX XXX XXX";
static std::string MSG_SAISIR_NOM =         "Veuillez saisir un nom";
static std::string MSG_SAISIR_PRENOM =      "Veuillez saisir un prénom";
static std::string MSG_SAISIR_DATE =        "Veuillez saisir une date au format JJ MM AAAA";
static std::string MSG_SAISIR_JOUR =        "Veuillez saisir une date [1-31]: ";
static std::string MSG_SAISIR_MOIS =        "Veuillez saisir un mois [1-12]:  ";
static std::string MSG_SAISIR_ANNEE =       "Veuillez saisir une année [1970-2037]: ";
static std::string MSG_SAISIR_PARTI =       "Veuillez saisir un numéro de parti politique: ";

/**
 * Taille maximale d'une saisie
 */
static size_t MAX_CHAR = 256;

/**
 * Affiche un message et saisit une ligne de MAX_CHAR caractères au plus.
 *
 * \param[in] p_invite Chaîne de caractère à afficher avant la saisie
 *
 * \return La chaîne de caractères saisie
 */

std::string saisirAvecInvite(const std::string& p_invite)
{
	std::string saisie;
	char tampon[MAX_CHAR];

	std::cout << std::left << std::setw(50) << p_invite << " : ";
	std::cin.getline(tampon, MAX_CHAR);
	saisie = tampon;

	return saisie;
}

/**
 * Affiche un message et saisit un numéro civique.  Affiche un message d'erreur et invite l'utilisateur
 * à recommencer si un nombre positif n'a pas été saisi.
 *
 * \return La valeur entière saisie
 */
unsigned int saisirNumeroCivic()
{
	bool valide = false;
	std::string saisie;
	int numero;

	while (!valide)
	{
		saisie = saisirLigneNonVideAvecInvite(MSG_SAISIR_NUMERO);
		try
		{
			numero = std::stoi(saisie);
			if (!(valide = (numero > 0)))
			{
				std::cout << "Le numéro saisi doit être non-nul et positif." << std::endl;
			}
		}
		catch(...)
		{
			std::cout << "Vous n'avez pas saisi un numéro civique valide." << std::endl;
		}
	}
	return numero;
}

/**
 * Invite l'utilisateur à saisir une ligne de texte.  Celle-ci ne peut être ni vide, ni constituée d'espaces.
 *
 * \param[in] p_invite Le message à l'utilisateur
 *
 * \return La chaîne de caractères saisies.
 */
std::string saisirLigneNonVideAvecInvite(const std::string& p_invite)
{
	bool valide = false;
	std::string saisie;

	while (!valide)
	{
		saisie = saisirAvecInvite(p_invite);
		valide = util::Adresse::validerLigneNonVide(saisie);
		if (!valide)
		{
			std::cout << "Vous avez saisi une ligne vide.  Veuillez recommencer, s'il vous plaît." << std::endl;
		}
	}
	return saisie;
}

/**
 * Invite l'utilisateur à saisir un nombre entier. Si la saisie de l'utilisateur ne peut être convertie en nombre
 * entier, émet un message d'erreur et invite l'utilisateur à recommencer.
 *
 * \param[in] p_invite le message d'invite
 *
 * \return Le nombre saisi
 */

long saisirEntierValideAvecInvite(const std::string& p_invite)
{
	bool valide = false;
	std::string saisie;
	long nombre;

	while (!valide)
	{
		saisie = saisirAvecInvite(p_invite);
		try
		{
			nombre = stol(saisie);
			valide = true;
		}
		catch(...)
		{
			std::cout << "Vous n'avez pas saisi un nombre. Veuillez recommencer s'il vous plaît." << std::endl;
		}
	}
	return nombre;
}

/**
 * Convertit les caractères minuscules d'un objet string en majuscules.  Les caractères non alphabétiques ne sont pas
 * transformés
 *
 * \param[in] p_saisie La chaîne de caractères à transformer
 *
 * \return La chaîne capitalisée.
 */

std::string mettreEnMajuscules(std::string p_saisie)
{
	std::string::size_type longueur = p_saisie.size();

	for (std::string::size_type i = 0; i < longueur; ++i)
	{
		p_saisie[i] = std::toupper(p_saisie[i]);
	}
	return p_saisie;
}

/**
 * Invite l'utilisateur à saisir un code postal au format canadien.
 * Si la chaîne de caractères saisie est vide, l'utilisateur est
 * invité à recommencer.
 *
 * \return La chaîne contenant le code postal validé.
 */

std::string saisirCodePostal()
{
	bool valide = false;
	std::string saisie;

	while (!valide)
	{
		saisie = mettreEnMajuscules(saisirLigneNonVideAvecInvite(MSG_SAISIR_CODE_POSTAL));
		valide = util::Adresse::validerLigneNonVide(saisie);
	    if (!valide)
	    {
	    	std::cout << "Le code postal saisi n'est pas valide.  Veuillez recommencer s'il vous plaît." << std::endl;
	    }
	}
	return saisie;
}

/**
 * Invite l'utilisateur à saisir les 5 champs d'une adresse résidentielle canadienne.
 * Le numéro civique doit être un entier positif.\n
 * Les nomms de rue, ville et province doivent être non-vides.\n
 * Le code postal doit être au format canadien standard LCL CLC où L=Lettre et C=Chiffre
 *
 * \return Un objet Adresse construit avec les renseignements saisis.
 */

util::Adresse saisirAdresseValide()
{
	unsigned int numero = saisirNumeroCivic();
	std::string rue = saisirLigneNonVideAvecInvite(MSG_SAISIR_RUE);
	std::string ville = saisirLigneNonVideAvecInvite(MSG_SAISIR_VILLE);
	std::string code = saisirCodePostal();
	std::string province = saisirLigneNonVideAvecInvite(MSG_SAISIR_PROVINCE);

	return util::Adresse(numero, rue, ville, code, province);
}

/**
 * Vérifie si un entier est une date valide
 *
 * \param[in] p_jour la date
 *
 * \return true si p_jour est compris entre 1 et 31 inclusivement
 */
bool estUnJourValide(long p_jour)
{
	return (p_jour <= 31) and (p_jour > 0);
}

/**
 * Vérifie si un entier est un mois valide
 *
 * \param[in] p_mois le mois
 *
 * \return true si p_mois est compris entre 1 et 12 inclusivement
 */

bool estUnMoisValide(long p_mois)
{
	return (p_mois > 0) and (p_mois <= 12);
}

/**
 * Vérifie qu'un nombre représente une année reconnue par le module Date.cpp
 *
 * \param[in] p_annee une année
 *
 * \return true si l'année est comprise entre 1970 et 2037 inclusivement
 */

bool estUneAnneeValide(long p_annee)
{
	return (p_annee >= 1970) and (p_annee <= 2037);
}

/**
 * Invite un utilisateur à saisir une date. Si ce n'est pas un entier valide ou
 * si le chiffre n'est pas dans l'intervalle fermé 1-31, invite l'utilisateur à
 * recommencer.
 *
 * \return la date
 */

long saisirJourValide()
{
	long jour;
	bool valide = false;

	while (!valide)
	{
		jour = saisirEntierValideAvecInvite(MSG_SAISIR_JOUR);
		valide = estUnJourValide(jour);
		if (!valide)
		{
			std::cout << "Le jour saisi est hors-limite.  La date est un entier entre 1 et 31 inclusivement.  Veuillez recommencer. " << std::endl;
		}
	}
	return jour;
}

/**
 * Invite un utilisateur à saisir un mois.  Si la saisie n'est pas un nombre entier valide ou
 * si le chiffre n'est pas dans l'intervalle fermé 1-12, invite l'utilisateur à recommencer.
 *
 * \return le mois
 */

long saisirMoisValide()
{
	long mois;
	bool valide = false;

	while (!valide)
	{
		mois = saisirEntierValideAvecInvite(MSG_SAISIR_MOIS);
		valide = estUnMoisValide(mois);
		if (!valide)
		{
			std::cout << "Le mois saisi est hors-limite.  Ce doit être un entier entre 1 et 12 inclusivement.  Veuillez recommencer. " << std::endl;
		}
	}
	return mois;
}

/**
 * Invite l'utilisateur < saisir une année.  Si la saisie n'est pas un nombre entier valide, ou
 * si le chiffre n'est pas dans l'intervalle fermé 1970-2037, invite l'utilisateur à recommencer.
 *
 * \return l'année
 */

long saisirAnneeValide()
{
	long annee;
	bool valide = false;

	while (!valide)
	{
		annee = saisirEntierValideAvecInvite(MSG_SAISIR_ANNEE);
		valide = estUneAnneeValide(annee);
		if (!valide)
		{
			std::cout << "L'année saisie est hors-limite.  Ce doit être un entier entre 1970 et 2037 inclusivement.  Veuillez recommencer. " << std::endl;
		}
	}
	return annee;
}

/**
 * Saisit une date complète en trois champs distincts.  Si les champs ne sont pas valides, ou si la date
 * saisie n'est pas valide, invite l'utilisateur à recommencer.
 *
 * \return Un objet Date valide.
 */
util::Date saisirDateValide()
{
	long jour;
	long mois;
	long annee;
	bool valide = false;

	while (!valide)
	{
		jour = saisirJourValide();
		mois = saisirMoisValide();
		annee = saisirAnneeValide();
		valide = util::Date::validerDate(jour, mois, annee);
		if (!valide)
		{
			std::cout << "Cette date est impossible.  Veuillez recommencer, s'il vous plaît." << std::endl;
		}
	}
	return util::Date(jour, mois, annee);
}

/**
 * Invite l'utilisateur à saisir les 3 champs d'une date entre le 1 janvier 1970
 * et le 31 décembre 2035.\n
 * Cette date doit être au format JJ MM AAAA ou tous les caractères sont des chiffres.
 *
 * \return Un objet Date initialisé avec les renseignements saisis.
 */
util::Date saisirDateFormatteeValide()
{
	long jour;
	long mois;
	long annee;
	std::string saisie;
	bool valide = false;

	while (!valide)
	{
		saisie = saisirLigneNonVideAvecInvite(MSG_SAISIR_DATE);

		if (util::validerLeFormatDeLaDate(saisie))
		{
			int champs[3];
			util::extraireLesChampsDeLaDate(saisie, champs);

			jour = (long int) champs[0];
			mois = (long int) champs[1];
			annee = (long int) champs[2];
			valide = util::Date::validerDate(jour, mois, annee);
			if (!valide)
			{
				std::cout << "Cette date est hors des limites acceptables ou est impossible.\nN'oubliez pas que l'année doit être entre 1970 et 2035." << std::endl;
			}
		}
		else
		{
			std::cout << "Le format des données saisies n'est pas valide.\n  Veuillez saisir une date au format JJ MM AAAA." << std::endl;
		}
	}
	return util::Date(jour, mois, annee);
}

/**
 * Invite l'utilisateur à saisir un numéro d'assurance sociale au format canadien.\n
 * Le numéro doit avoir la forme XXX XXX XXX où X est un chiffre.\n
 * Si une chaîne invalide est saisie, l'utilisateur est invité à recommencer.
 *
 * \return La chaîne contenant le NAS valide
 */

std::string saisirNasValide()
{
	std::string saisie;
	bool valide = false;

	while (!valide)
	{
		saisie = saisirLigneNonVideAvecInvite(MSG_SAISIR_NAS);
		valide = util::validerNas(saisie);
		if (!valide)
		{
			std::cout << "La valeur saisie n'est pas un numéro d'assurance sociale valide.  Veuillez recommencer s'il vous plaît." << std::endl;
		}
	}
	return saisie;
}

/**
 * Énumère les partis politiques ainsi que leur numéro à la console.
 *
 * \return Chaîne de caractères contenant les numéros et noms de parti.
 */

std::string enumererPartisPolitiques()
{
	std::string banniere;
	for (int i = elections::BLOC_QUEBECOIS; i <= elections::NOUVEAU_PARTI_DEMOCRATIQUE; ++i)
	{
		banniere += std::to_string(i) + ": " + util::PARTIS_POLITIQUES_FEDERAUX[i] + " ";
	}
	return banniere;
}

/**
 * Invite l'utilisateur à saisir un numéro valide de parti politique.
 * Si le numéro saisi n'est pas un des partis définis dans Candidat.h
 * un message d'erreur est affiché et l'utilisateur est invité à recommencer.
 *
 * \return Un numéro de parti
 */

elections::PartisPolitiques saisirPartiPolitiqueValide()
{
	elections::PartisPolitiques numeroDeParti;
	bool valide = false;

	while (!valide)
	{
		numeroDeParti = (elections::PartisPolitiques) saisirEntierValideAvecInvite(MSG_SAISIR_PARTI);
		valide = elections::Candidat::validerPartiPolitique(numeroDeParti);
		if (!valide)
		{
			std::cout << "Ce numéro de parti politique est hors-limites.  Veuillez recommencer. " << std::endl;
		}
	}
	return numeroDeParti;

}

/**
 * Construit un objet Electeur à partir de renseignements saisis par l'utilisateur.
 * Le champ NAS doit être un numéro d'assurance sociale valide.
 * Les champs nom et prénom doivent être non-vides.
 * Les champs adresse et date doivent être valides.
 *
 * \return Un objet personne initialisé avec les renseignements saisis.
 */

elections::Electeur saisirPersonneValide()
{
	util::Date date = saisirDateValide();
	util::Adresse adresse = saisirAdresseValide();

	std::string nom = saisirLigneNonVideAvecInvite(MSG_SAISIR_NOM);
	std::string prenom = saisirLigneNonVideAvecInvite(MSG_SAISIR_PRENOM);
	std::string nas = saisirNasValide();

	return elections::Electeur(nas, nom, prenom, date, adresse);
}

/**
 * Construit un objet Candidat à partir de renseignements saisis àla console par
 * l'utilisateur.
 *
 * \return un objet Candidat initialisé
 */
elections::Candidat saisirCandidatValide()
{
	std::cout << enumererPartisPolitiques() << std::endl;

	elections::PartisPolitiques parti = saisirPartiPolitiqueValide();

	util::Date date = saisirDateValide();
	util::Adresse adresse = saisirAdresseValide();

	std::string nom = saisirLigneNonVideAvecInvite(MSG_SAISIR_NOM);
	std::string prenom = saisirLigneNonVideAvecInvite(MSG_SAISIR_PRENOM);
	std::string nas = saisirNasValide();

	return elections::Candidat(nas, nom, prenom, date, adresse, parti);
}








